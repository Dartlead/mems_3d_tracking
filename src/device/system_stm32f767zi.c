#include "system_stm32f767zi.h"
#include "stm32f767zi.h"

/* +++++++++++++++++++++++++++++++++++++++++++ Macros +++++++++++++++++++++++++++++++++++++++++++ */

/**
 * @brief Default system clock frequency (HSI at 16 MHz).
 */
#define DEFAULT_SYSTEM_CLOCK_FREQ 16000000UL

/**
 * @brief Default AHB bus frequency (with the system clock not divided).
 */
#define DEFAULT_AHB_CLOCK_FREQ    16000000UL

/**
 * @brief Default APB1 bus frequency (with the AHB bus clock not divided).
 */
#define DEFAULT_APB1_CLOCK_FREQ   16000000UL

/**
 * @brief Default APB2 bus frequency (with the AHB bus clock not divided).
 */
#define DEFAULT_APB2_CLOCK_FREQ   16000000UL

/* ----------------------------------------- End Macros ----------------------------------------- */



/* ++++++++++++++++++++++++++++++++++++++ Type Declaration ++++++++++++++++++++++++++++++++++++++ */

/**
 * @enum Status codes for internal use while setting up the system clock.
 */
typedef enum
{
	  STATUS_OK                      =  0 /**< Success                                            */
	, STATUS_GENERIC_FAILED          = -1 /**< Generic error (init state of status return)        */
	, STATUS_OVERDRIVE_MODE_FAILED   = -2 /**< Regulator failed to enable overdrive mode          */
	, STATUS_OVERDRIVE_SWITCH_FAILED = -3 /**< Regulator failed to switch to overdrive mode       */
	, STATUS_PLL_LOCK_FAILED         = -4 /**< Main PLL failed to lock                            */
	, STATUS_PLL_SYS_CLK_SRC_FAILED  = -5 /**< CPU failed to take main PLL as system clock source */
} sys_clk_status_t;

/* ------------------------------------ End Type Declaration ------------------------------------ */



/* ++++++++++++++++++++++++++++++++++++++ Global Variables ++++++++++++++++++++++++++++++++++++++ */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK_FREQ;
uint32_t SystemAHBClock  = DEFAULT_AHB_CLOCK_FREQ;
uint32_t SystemAPB1Clock = DEFAULT_APB1_CLOCK_FREQ;
uint32_t SystemAPB2Clock = DEFAULT_APB2_CLOCK_FREQ;

/* ------------------------------------ End Global Variables ------------------------------------ */



/* ++++++++++++++++++++++++++++++++++++++ Static Variables ++++++++++++++++++++++++++++++++++++++ */

/**
 * @brief Timeout that dictates the length of the wait for things like waiting for the PLL to lock.
 */
static uint32_t const clocking_timeout = 0x5000UL;

/* ------------------------------------ End Static Variables ------------------------------------ */



/* ++++++++++++++++++++++++++++++++++++++ Helper Functions ++++++++++++++++++++++++++++++++++++++ */

/**
 * @brief In the case, somehow, the program ends up back in system init code, this function ensures
 *        that things operate as it would if the system had just come out of a POR.
 */
static void reset_regs(void) {
	RCC->PLLCFGR = 0x24003010;
	RCC->CFGR    = 0x00000000;
	RCC->CR      = 0x00000083;
	PWR->CR1     = 0x0000C000;
	FLASH->ACR   = 0x00000000;
}

/**
 * @brief Sets the registers used for configuring the system's clocks to their default state as to
 *        clock the CPU with the default POR settings.
 * @note  Updates the CMSIS-style clock frequency variables.
 */
static void set_clocks_to_default(void) {
	reset_regs();
	SystemCoreClock = SystemAHBClock = SystemAPB1Clock = SystemAPB2Clock = 16000000;
}

/**
 * @brief   Configures the main PLL and its voltage-controlled oscillator to produce a 216 MHz PLLP
 *          output frequency.
 * @details The equations used for getting the 216 MHz PLLP output frequency are as follows:
 *
 *          VCO input frequency   = PLL input clock frequency / PLLM    with 2 <= PLLM <= 63
 *          VCO output frequency  = VCO input frequency * PLLN          with 50 <= PLLN <= 432
 *          PLLP output frequency = VCO output frequency / PLLP         with PLLP = 2, 4, 6 or 8
 *
 *          Where VCO is the voltage-controlled oscillator block within the main PLL block and the
 *          PLL input clock frequency is 16 MHz as the PLL is clocked by default by the HSI. Also
 *          note that the reference manual suggests making the VCO input frequency 2 MHz to limit
 *          PLL jitter.
 */
static void configure_main_PLL_VCO(void)
{
	/* Set the main PLL source to the HSI */
	RCC->PLLCFGR &= ~(0x1 << 22);

	/* Set PLLM to 8 to get a VCO input frequency of 2 MHz */
	RCC->PLLCFGR  =  (RCC->PLLCFGR & ~(0x3FUL))   | 0x8UL;

	/* Set PLLN to 216 to get a VCO output frequency of 432 MHz */
	RCC->PLLCFGR  =  (RCC->PLLCFGR & ~(0x7FC0UL)) | 0x3600UL;

	/* Set PLLP to 2 to get a PLLP output frequency of 216 MHz */
	RCC->PLLCFGR &= ~(0x3 << 16);
}

/**
 * @brief   Changes the embedded linear voltage regulator's output voltage.
 * @details The Embedded Linear Voltage Regulator supplies all the digital circuitries except for
 *          the backup domain and the standby circuitry. The nominal output voltage is around 1.2V 
 *          but this function increases it to support the 216 MHz system clock via changing the
 *          power scale from 3 to 1 and placing the regulator into over-drive mode (over-drive mode
 *          allows for even higher clock frequencies at a given power scale).
 *
 *          At power scale 3 (typical voltage output of 1.14V), max system clock is 144 MHz.
 *          At power scale 2 (typical voltage output of 1.26V), max system clock is 168 MHz with
 *             over-drive mode off and 180 MHz with over-drive mode on.
 *          At power scale 1 (typical voltage output of 1.32V), max system clock is 180 MHz with
 *             over-drive mode off and 216 MHz with over-drive mode on.
 *
 * @return The status indicating success or failure in configuring the voltage regulator.
 */
static sys_clk_status_t configure_voltage_regulator(void)
{
	uint32_t timeout_count = 0;

	/* Enable the peripheral clock to the PWR peripheral then place the voltage regulator into
	 * scale mode 1 and enable overdrive mode */
	RCC->APB1ENR |= (0x1UL << 28);
	PWR->CR1     |= (0x3UL << 14) | (0x1UL << 16);

	/* Wait for over-drive mode to be ready */
	while (!(PWR->CSR1 & (0x1UL << 16))) {
		if (timeout_count++ >= clocking_timeout) {
			/* Failed to enable overdrive mode so undo changes (by resetting PWR_CR1) */
			PWR->CR1 = 0x0000C000;
			return STATUS_OVERDRIVE_MODE_FAILED;
		}
	}

	PWR->CR1 |= (0x1UL << 17); //Place the system into overdrive mode
	timeout_count = 0;

	/* Wait for overdrive switching to be ready */
	while (!(PWR->CSR1 & (0x1UL << 17))) {
		if (timeout_count++ >= clocking_timeout) {
			/* Failed to switch into overdrive mode so undo changes (by resetting PWR_CR1) */
			PWR->CR1 = 0x0000C000;
			return STATUS_OVERDRIVE_SWITCH_FAILED;
		}
	}

	return STATUS_OK;
}

/**
 *
 * @brief   Configures the embedded flash controller's ready latency and acceleration through the
 *          ART and prefetching.
 * @details As the system clock speed increases, the number of wait states (i.e. the latency) must
 *          be correctly set in the embedded flash controller's access registers otherwise the core
 *          will be unable to read from said flash. Moreover this function enables the ART
 *          accelerator and enables instruction prefetching.
 */
static void configure_flash_latency(void)
{
	FLASH->ACR |= (0x1UL << 9) | (0x1UL << 8) | 0x7UL;
}

/**
 * @brief   Sets the APB low-speed (APB1) prescaler.
 * @details The max frequency of the APB1 bus is 45 MHz and the APB1 prescaler divides down the AHB
 *          clock. The AHB clock should never be divided down and should be 216 MHz. Thus, given
 *          the limited choice of prescaler values, the AHB frequency should be divided by 8 to get
 *          27 MHz for the APB1 bus frequency.
 */
static void configure_APB1_clock(void)
{
	RCC->CFGR |= 0x6UL << 10;
}

/**
 * @brief   Sets the APB high-speed (APB2) prescaler.
 * @details The max frequency of the APB2 bus is 90 MHz and the APB2 prescaler divides down the AHB
 *          clock. The AHB clock should never be divided down and should be 216 MHz. Thus, given
 *          the limited choice of prescaler values, the AHB frequency should be divided by 4 to get
 *          54 MHz for the APB2 bus frequency.
 */
static void configure_APB2_clock(void)
{
	RCC->CFGR |= 0x5UL << 13;
}

/* ------------------------------------ End Helper Functions ------------------------------------ */



/* ++++++++++++++++++++++++++++++++++++++ Public Functions ++++++++++++++++++++++++++++++++++++++ */

void SystemInit()
{
	sys_clk_status_t status        = STATUS_GENERIC_FAILED;
	uint32_t         timeout_count = 0;

	reset_regs(); //Reset the registers used to configure clocks to their default state

	//
	// (1) Configure the PLL to output the 216 MHz clock that will become the system clock
	//
	configure_main_PLL_VCO();

	//
	// (2) Configure the voltage regulator to support the 216 MHz system clock via the PLL
	//
	if (STATUS_OK != (status = configure_voltage_regulator())) {
		set_clocks_to_default(); //Failed to enter overdrive so use default frequencies
		return;
	}

	//
	// (3) Turn on the main PLL that we configured in (1) and set the flash wait states
	//
	RCC->CR |=  (0x1 << 24); // Turn on the main PLL
	configure_flash_latency();

	//
	// (4) Wait for the main PLL to lock and if it doens't error out by defaulting the clocks
	//
	while (!(RCC->CR & (0x1 << 25))) {
		if (timeout_count++ >= clocking_timeout) {
			set_clocks_to_default(); //Main PLL didn't lock so use default frequencies
			return;
		}
	}

	//
	// (5) Set the dividers to set the APB1 and APB2 clocks
	//
	configure_APB1_clock();
	configure_APB2_clock();

	//
	// (6) Set the main PLL as the system clock source
	//
	RCC->CFGR = (RCC->CFGR & ~(0x3UL)) | 0x2UL;

	//
	// (7) Wait for the CPU to accept the main PLL as the system clock source
	//
	timeout_count = 0;
	while ((RCC->CFGR & 0xCUL) != 0x8UL) {
		if (timeout_count++ >= clocking_timeout) {
			set_clocks_to_default(); //CPU didn't accept main PLL so use default frequencies
			return;
		}
	}

	//
	// (8) Everything has succeeded so set the CMSIS variables accordingly
	//
	SystemCoreClock = 216000000;
	SystemAHBClock  = 216000000;
	SystemAPB1Clock =  27000000;
	SystemAPB2Clock =  54000000;
}

void SystemCoreClockUpdate()
{
	return;
}

/* ------------------------------------ End Public Functions ------------------------------------ */

/* EOF */
