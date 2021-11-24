#include "system_stm32f767zi.h"
#include "stm32f767zi.h"

/*! System clock frequency in hertz (core clock).
 */
uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK_FREQ;
uint32_t SystemAHBClock  = DEFAULT_AHB_CLOCK_FREQ;
uint32_t SystemAPB1Clock = DEFAULT_APB1_CLOCK_FREQ;
uint32_t SystemAPB2Clock = DEFAULT_APB2_CLOCK_FREQ;

/*! Timeout that dictates the length of the wait for things like waiting for the PLL to lock.
 */
static uint32_t const clocking_timeout = 0x5000UL;

/*! Return status codes for internal use while setting up the system clock.
 */
enum
{
	  STATUS_OK                      =  0 //!# Success
	, STATUS_GENERIC_FAILED          = -1 //!# Generic error used to initialize the status variable to a fail case
	, STATUS_OVERDRIVE_MODE_FAILED   = -2 //!# Voltage regulator failed to enable over-drive mode
	, STATUS_OVERDRIVE_SWITCH_FAILED = -3 //!# Voltage regulator failed to switch to over-drive mode
	, STATUS_PLL_LOCK_FAILED         = -4 //!# Main PLL failed to lock
	, STATUS_PLL_SYS_CLK_SRC_FAILED  = -5 //!# System failed to accept the main PLL as the system clock source
};

typedef int sys_clk_status_t;

/* ============================================================================================================= */
/* System Clock Helper Functions                                                                                 */
/* ============================================================================================================= */
/*! Sets register involved with the system initialization back to their default state.
 *
 * @brief In the case, somehow, the program ends up back in system init code, this function ensures that things
 *        operate as it would if they system had just come out of reset.
 */
static void reset_regs(void)
{
	RCC->PLLCFGR = 0x24003010;
	RCC->CFGR    = 0x00000000;
	RCC->CR      = 0x00000083;
	PWR->CR1     = 0x0000C000;
	FLASH->ACR   = 0x00000000;
}

/*! Configures the main PLL and its Voltage-controlled Oscillator to produce a 216 MHz PLLP output frequency.
 *
 * @brief The equations used for getting the 216 MHz PLLP output frequency are as follows:
 *
 *        VCO input frequency   = PLL input clock frequency / PLLM    with 2 <= PLLM <= 63
 *        VCO output frequency  = VCO input frequency * PLLN          with 50 <= PLLN <= 432
 *        PLLP output frequency = VCO output frequency / PLLP         with PLLP = 2, 4, 6 or 8
 *
 *        Where VCO is the voltage-controlled oscillator block within the main PLL block and the PLL input clock
 *        frequency is 16 MHz as the PLL is clocked by default by the HSI. Also note that the reference manual
 *        suggests making the VCO input frequency 2 MHz to limit PLL jitter.
 */
static void configure_main_PLL_VCO(void)
{
	RCC->PLLCFGR &= ~(0x1 << 22);                             //!# Set main PLL source to the HSI
	RCC->PLLCFGR  =  (RCC->PLLCFGR & ~(0x3FUL))   | 0x8UL;    //!# Set PLLM to 8 to get a VCO in freq of 2 MHz
	RCC->PLLCFGR  =  (RCC->PLLCFGR & ~(0x7FC0UL)) | 0x3600UL; //!# Set PLLN to 216 to get a VCO out freq of 432 MHz
	RCC->PLLCFGR &= ~(0x3 << 16);                             //!# Set PLLP to 2 to get a PLLP out freq of 216 MHz
}

/*! Changes the Embedded Linear Voltage Regulator's output voltage
 *
 * @brief The Embedded Linear Voltage Regulator supplies all the digital circuitries except for the backup domain
 *        and the Standby circuitry. The nominal output voltage is around 1.2V but this function increases it to
 *        support the 216 MHz system clock via changing the power scale from 3 to 1 and placing the regulator into
 *        over-drive mode (over-drive mode allows for even higher clock frequencies at a given power scale).
 *
 *        At power scale 3 (typical voltage output of 1.14V), max system clock is 144 MHz.
 *        At power scale 2 (typical voltage output of 1.26V), max system clock is 168 MHz with over-drive mode off
 *           and 180 MHz with over-drive mode on.
 *        At power scale 1 (typical voltage output of 1.32V), max system clock is 180 MHz with over-drive mode off
 *           and 216 MHz with over-drive mode on.
 *
 * @return The status indicating success or failure in configuring the voltage regulator.
 */
static sys_clk_status_t configure_voltage_regulator(void)
{
	uint32_t timeout_count = 0;

	RCC->APB1ENR |= (0x1UL << 28);                 //!# Enable the peripheral clock to the PWR peripheral
	PWR->CR1     |= (0x3UL << 14) | (0x1UL << 16); //!# Place the VR into scale mode 1 and enable over-drive mode

	//!# Wait for over-drive mode to be ready */
	while (!(PWR->CSR1 & (0x1UL << 16))) {
		if (timeout_count++ >= clocking_timeout) {
			//!# Failed to enable over-drive mode so undo voltage regulator changes (by resetting PWR_CR1)
			PWR->CR1 = 0x0000C000;
			return STATUS_OVERDRIVE_MODE_FAILED;
		}
	}

	PWR->CR1 |= (0x1UL << 17); //!# Place the system into over-drive mode
	timeout_count = 0;

	//!# Wait for over-drive switching to be ready
	while (!(PWR->CSR1 & (0x1UL << 17))) {
		if (timeout_count++ >= clocking_timeout) {
			//!# Failed to switch into over-drive mode so undo voltage regulator changes (by resetting PWR_CR1)
			PWR->CR1 = 0x0000C000;
			return STATUS_OVERDRIVE_SWITCH_FAILED;
		}
	}

	return STATUS_OK;
}

/*! Configures the embedded flash controller's read latency and acceleration through the ART and prefetching.
 *
 * @brief As the system clock speed increases, the number of wait states (i.e. the latency) must be correctly set
 *        in the embedded flash controller's access registers otherwise the core will be unable to read from said
 *        flash. Moreover this function enables the ART accelerator and enables instruction prefetching.
 */
static void configure_flash_latency(void)
{
	FLASH->ACR |= (0x1UL << 9) | (0x1UL << 8) | 0x7UL;
}

/* ============================================================================================================= */
/* Peripheral Bus Clock Helper Functions                                                                         */
/* ============================================================================================================= */
/*! Sets the APB low-speed (APB1) prescaler.
 *
 * @brief The max frequency of the APB1 bus is 45 MHz and the APB1 prescaler divides down the AHB clock. The AHB
 *        clock should never be divided down and should be 216 MHz. Thus, given the limited choice of prescaler
 *        values, the AHB frequency should be divided by 8 to get 27 MHz for the APB1 bus frequency.
 */
static void configure_APB1_clock(void)
{
	RCC->CFGR |= 0x6UL << 10;
}

/*! Sets the APB high-speed (APB2) prescaler.
 *
 * @brief The max frequency of the APB2 bus is 90 MHz and the APB2 prescaler divides down the AHB clock. The AHB
 *        clock should never be divided down and should be 216 MHz. Thus, given the limited choice of prescaler
 *        values, the AHB frequency should be divided by 4 to get 54 MHz for the APB2 bus frequency.
 */
static void configure_APB2_clock(void)
{
	RCC->CFGR |= 0x5UL << 13;
}

/* ============================================================================================================= */
/* Public Functions                                                                                              */
/* ============================================================================================================= */
/*! Setup the microcontroller system.
 *
 * @brief Sets up the system, AHB and APB1/2 clocks.
 */
void SystemInit()
{
	sys_clk_status_t status        = STATUS_GENERIC_FAILED;
	uint32_t         timeout_count = 0;

	reset_regs();
	configure_main_PLL_VCO();

	if (STATUS_OK == (status = configure_voltage_regulator())) {
		RCC->CR |=  (0x1 << 24); //!# Turn on the main PLL
		configure_flash_latency();

		//!# Wait for the main PLL to lock
		while (!(RCC->CR & (0x1 << 25))) {
			if (timeout_count++ >= clocking_timeout) {
				//!# Main PLL failed to lock so undo all changes and use default frequencies
				reset_regs();
				SystemCoreClock = SystemAHBClock = SystemAPB1Clock = SystemAPB2Clock = 16000000;
				return;
			}
		}

		configure_APB1_clock();
		configure_APB2_clock();

		RCC->CFGR = (RCC->CFGR & ~(0x3UL)) | 0x2UL; //!# Set the main PLL as the system clock source

		//!# Wait for main PLL to be accepted as sys clk src
		timeout_count = 0;
		while ((RCC->CFGR & 0xCUL) != 0x8UL) {
			if (timeout_count++ >= clocking_timeout) {
				//!# System failed to accept main PLL as clock source so undo all changes and use default frequencies
				reset_regs();
				SystemCoreClock = SystemAHBClock = SystemAPB1Clock = SystemAPB2Clock = 16000000;
				return;
			}
		}

		//!# Everything has succeeded so set the appropriate frequencies
		SystemCoreClock = 216000000;
		SystemAHBClock  = 216000000;
		SystemAPB1Clock =  27000000;
		SystemAPB2Clock =  54000000;
	} else {
		//!# Failed to enter over-drive (216 MHz sys clk can't be reached) so use default frequencies
		reset_regs();
		SystemCoreClock = SystemAHBClock = SystemAPB1Clock = SystemAPB2Clock = 16000000;
	}
}

/*! Updates the SystemCoreClock variable.
 *
 */
void SystemCoreClockUpdate()
{
	return;
}