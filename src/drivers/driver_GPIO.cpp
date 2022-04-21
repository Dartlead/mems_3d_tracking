#include "driver_GPIO.h"
#include "dartlead_assert.h"
#include <cstddef>

#define GPIO_MAX_PIN_NUM 15

/**
 * @details Initializes a GPIO pin by enabling the AHB clock to the GPIO port and updating the
 *          relevant members with their correct values.
 */
GPIO::pin::pin(port const pin_port, uint8_t const pin_number) {
	/* Enable the peripheral clock to the GPIO port and update private members */
	switch (pin_port) {
		case GPIO::port::A:
			RCC->AHB1ENR  |= 0x1UL;
			m_port_base_addr = GPIOA;
			break;
		case GPIO::port::B:
			RCC->AHB1ENR  |= 0x1UL << 1;
			m_port_base_addr = GPIOB;
			break;
		case GPIO::port::C:
			RCC->AHB1ENR  |= 0x1UL << 2;
			m_port_base_addr = GPIOC;
			break;
		case GPIO::port::D:
			RCC->AHB1ENR  |= 0x1UL << 3;
			m_port_base_addr = GPIOD;
			break;
		case GPIO::port::E:
			RCC->AHB1ENR  |= 0x1UL << 4;
			m_port_base_addr = GPIOE;
			break;
		case GPIO::port::F:
			RCC->AHB1ENR  |= 0x1UL << 5;
			m_port_base_addr = GPIOF;
			break;
		case GPIO::port::G:
			RCC->AHB1ENR  |= 0x1UL << 6;
			m_port_base_addr = GPIOG;
			break;
		case GPIO::port::H:
			RCC->AHB1ENR  |= 0x1UL << 7;
			m_port_base_addr = GPIOH;
			break;
		case GPIO::port::I:
			RCC->AHB1ENR  |= 0x1UL << 8;
			m_port_base_addr = GPIOI;
			break;
		case GPIO::port::J:
			RCC->AHB1ENR  |= 0x1UL << 9;
			m_port_base_addr = GPIOJ;
			break;
		case GPIO::port::K:
			RCC->AHB1ENR  |= 0x1UL << 10;
			m_port_base_addr = GPIOK;
			break;
		default:
			dartlead_WTF;
			break;
	}

	/* Set the rest of the private members */
	m_number       = pin_number;
	m_mode         = GPIO::mode::output;
	m_port         = pin_port;
	m_output_type  = GPIO::output_type::push_pull;
	m_output_speed = GPIO::output_speed::low;
	m_pull         = GPIO::pull::none;
	m_locked       = false;
}

/**
 * @details Deinitializes a GPIO pin by disabling the AHB clock to the GPIO port.
 */
GPIO::pin::~pin() {
	/* Disable peripheral clock to the GPIO port */
	switch (m_port) {
		case GPIO::port::A:
			RCC->AHB1ENR  &= ~0x1UL;
			break;
		case GPIO::port::B:
			RCC->AHB1ENR &= ~(0x1UL << 1);
			break;
		case GPIO::port::C:
			RCC->AHB1ENR &= ~(0x1UL << 2);
			break;
		case GPIO::port::D:
			RCC->AHB1ENR &= ~(0x1UL << 3);
			break;
		case GPIO::port::E:
			RCC->AHB1ENR &= ~(0x1UL << 4);
			break;
		case GPIO::port::F:
			RCC->AHB1ENR &= ~(0x1UL << 5);
			break;
		case GPIO::port::G:
			RCC->AHB1ENR &= ~(0x1UL << 6);
			break;
		case GPIO::port::H:
			RCC->AHB1ENR &= ~(0x1UL << 7);
			break;
		case GPIO::port::I:
			RCC->AHB1ENR &= ~(0x1UL << 8);
			break;
		case GPIO::port::J:
			RCC->AHB1ENR &= ~(0x1UL << 9);
			break;
		case GPIO::port::K:
			RCC->AHB1ENR &= ~(0x1UL << 10);
			break;
		default:
			dartlead_WTF;
			break;
	}
}

/**
 * @details Updates the private member and the GPIO pin's port's MODER register with the requested
 *          mode.
 */
GPIO::status GPIO::pin::set_mode(mode const pin_mode) {
	dartlead_assert(m_port_base_addr != NULL);
	dartlead_assert(m_number <= GPIO_MAX_PIN_NUM);
	dartlead_assert((pin_mode >= GPIO::mode::alt_func_0) && (pin_mode <= GPIO::mode::analog));

	uint32_t AFR_AFSEL_clear_mask = 0; //Bit mask to clear a single AFRL/H AFSELy field
	uint32_t AFR_AFSEL_mask       = 0; //Bit mask to set the requested pin's AFRL/H AFSELy field

	GPIO::status ret = GPIO::status::invalid_pin_mode;

	switch (pin_mode) {
		case GPIO::mode::alt_func_0:
		case GPIO::mode::alt_func_1:
		case GPIO::mode::alt_func_2:
		case GPIO::mode::alt_func_3:
		case GPIO::mode::alt_func_4:
		case GPIO::mode::alt_func_5:
		case GPIO::mode::alt_func_6:
		case GPIO::mode::alt_func_7:
		case GPIO::mode::alt_func_8:
		case GPIO::mode::alt_func_9:
		case GPIO::mode::alt_func_10:
		case GPIO::mode::alt_func_11:
		case GPIO::mode::alt_func_12:
		case GPIO::mode::alt_func_13:
		case GPIO::mode::alt_func_14:
		case GPIO::mode::alt_func_15:
			/* Mux the appropriate alternate function via AFR registers */
			if (m_number <= 8) {
				AFR_AFSEL_clear_mask     = 0xFUL << (m_number * 4);
				AFR_AFSEL_mask           = (uint32_t)pin_mode << (m_number * 4);
				m_port_base_addr->AFR[0] =
					(m_port_base_addr->AFR[0] & ~AFR_AFSEL_clear_mask) | AFR_AFSEL_mask;
			} else {
				AFR_AFSEL_clear_mask     = 0xFUL << ((m_number - 8) * 4);
				AFR_AFSEL_mask           = (uint32_t)pin_mode << ((m_number - 8) * 4);
				m_port_base_addr->AFR[1] =
					(m_port_base_addr->AFR[1] & ~AFR_AFSEL_clear_mask) | AFR_AFSEL_mask;
			}

			/* Change MODE to alternate function */
			m_port_base_addr->MODER =
				(m_port_base_addr->MODER & ~(0x3UL << (m_number * 2))) | (0x2UL << (m_number * 2));

			ret = GPIO::status::ok;
			break;
		case GPIO::mode::input:
			m_port_base_addr->MODER &= ~(0x3UL << (m_number * 2));
			ret = GPIO::status::ok;
			break;
		case GPIO::mode::output:
			m_port_base_addr->MODER =
				(m_port_base_addr->MODER & ~(0x3UL << (m_number * 2))) | (0x1UL << (m_number * 2));
			ret = GPIO::status::ok;
			break;
		case GPIO::mode::analog:
			m_port_base_addr->MODER |= 0x3UL << (m_number * 2);
			ret = GPIO::status::ok;
			break;
		default:
			ret = GPIO::status::invalid_pin_mode;
			dartlead_WTF;
			break;
	}

	/* Update mode private member */
	m_mode = pin_mode;

	return ret;
}

/**
 * @details Updates the private member and the GPIO pin's port's OTYPER register with the requested
 *          output type.
 */
GPIO::status GPIO::pin::set_output_type(output_type const pin_output_type) {
	dartlead_assert(m_port_base_addr != NULL);
	dartlead_assert(m_number <= GPIO_MAX_PIN_NUM);
	dartlead_assert(
		(pin_output_type >= GPIO::output_type::push_pull ) &&
		(pin_output_type <= GPIO::output_type::open_drain)
	);

	GPIO::status ret = GPIO::status::invalid_pin_output_type;

	switch (pin_output_type) {
		case GPIO::output_type::push_pull:
			m_port_base_addr->OTYPER &= ~(0x1UL << m_number);
			ret = GPIO::status::ok;
			break;
		case GPIO::output_type::open_drain:
			m_port_base_addr->OTYPER |= 0x1UL << m_number;
			ret = GPIO::status::ok;
			break;
		default:
			dartlead_WTF;
			break;
	}

	/* Update output type private member */
	m_output_type = pin_output_type;

	return ret;
}

/**
 * @details Updates the private member and the GPIO pin's port's OSPEEDR register with the
 *          requested output speed.
 */
GPIO::status GPIO::pin::set_output_speed(output_speed const pin_output_speed) {
	dartlead_assert(m_port_base_addr != NULL);
	dartlead_assert(m_number <= GPIO_MAX_PIN_NUM);
	dartlead_assert(
		(pin_output_speed >= GPIO::output_speed::low) &&
		(pin_output_speed <= GPIO::output_speed::very_high)
	);

	GPIO::status ret = GPIO::status::invalid_pin_output_speed;

	switch (pin_output_speed) {
		case GPIO::output_speed::low:
			m_port_base_addr->OSPEEDR &= ~(0x3UL << (m_number * 2));
			ret = GPIO::status::ok;
			break;
		case GPIO::output_speed::medium:
			m_port_base_addr->OSPEEDR =
				(m_port_base_addr->OSPEEDR & ~(0x3UL << (m_number * 2))) |
				(0x1UL << (m_number * 2));
			ret = GPIO::status::ok;
			break;
		case GPIO::output_speed::high:
			m_port_base_addr->OSPEEDR =
				(m_port_base_addr->OSPEEDR & ~(0x3UL << (m_number * 2))) |
				(0x2UL << (m_number * 2));
			ret = GPIO::status::ok;
			break;
		case GPIO::output_speed::very_high:
			m_port_base_addr->OSPEEDR |= 0x3UL << (m_number * 2);
			ret = GPIO::status::ok;
			break;
		default:
			dartlead_WTF;
			break;
	}

	/* Update output speed private member */
	m_output_speed = pin_output_speed;

	return ret;
}

/**
 * @details Updates the private member and the GPIO pin's port's PUPDR register with the requested
 *          pull.
 */
GPIO::status GPIO::pin::set_pull(pull const pin_pull) {
	dartlead_assert(m_port_base_addr != NULL);
	dartlead_assert(m_number <= GPIO_MAX_PIN_NUM);
	dartlead_assert((pin_pull >= GPIO::pull::none) && (pin_pull <= GPIO::pull::down));

	GPIO::status ret = GPIO::status::invalid_pin_pull;

	switch (pin_pull) {
		case GPIO::pull::none:
			m_port_base_addr->PUPDR &= ~(0x3UL << (m_number * 2));
			break;
		case GPIO::pull::up:
			m_port_base_addr->PUPDR =
				(m_port_base_addr->PUPDR & ~(0x3UL << (m_number * 2))) | (0x1UL << (m_number * 2));
			break;
		case GPIO::pull::down:
			m_port_base_addr->PUPDR =
				(m_port_base_addr->PUPDR & ~(0x3UL << (m_number * 2))) | (0x2UL << (m_number * 2));
			break;
		default:
			dartlead_WTF;
			break;
	}

	/* Update pull private member */
	m_pull = pin_pull;

	return ret;
}

/**
 * @details Locks the pin's configuration by applying the correct lock sequence to the LCKR
 *          register and updates the private member.
 * @note    The lock sequence is as follows (where LCKR[15:0] contains a '1' in the bit position
 *          corresponding to pin number being locked):
 *          (1) Write LCKR[16] = '1' + LCKR[15:0]
 *          (2) Write LCKR[16] = '0' + LCKR[15:0]
 *          (3) Write LCKR[16] = '1`' + LCKR[15:0]
 *          (4) Read LCKR
 *          (5) Optionally read LCKR to verify LCKR[16] == 1 (confirms that the LOCK is active)
 * @note    The lock sequence can only be performed using word access to the GPIOx_LCKR register
 *          due to the fact that GPIOx_LCKR bit 16 has to be set at the same time as the [15:0]
 *          bits.
 * @note    This function is forcibly optimized at -O0 to ensure that the correct lock sequence is
 *          respected and not optimized out.
 */
GPIO::status __attribute__((optimize("O0"))) GPIO::pin::lock_config() {
	dartlead_assert(m_port_base_addr != NULL);
	dartlead_assert(m_number <= GPIO_MAX_PIN_NUM);

	uint32_t     LCKR_15_0 = (m_port_base_addr->LCKR & 0xFFFFUL) | (0x1UL << m_number);
	GPIO::status ret       = GPIO::status::lock_failed;

	/* LOCK write sequence */
	m_port_base_addr->LCKR = 0x10000UL | LCKR_15_0;
	m_port_base_addr->LCKR = LCKR_15_0;
	m_port_base_addr->LCKR = 0x10000UL | LCKR_15_0;
	LCKR_15_0              = m_port_base_addr->LCKR;
	LCKR_15_0              = m_port_base_addr->LCKR;

	if ((LCKR_15_0 & (0x1UL << 16)) && (LCKR_15_0 & (0x1UL << m_number))) {
		m_locked = true; //Lock was successful
		ret      = GPIO::status::ok;
	} else {
		m_locked = false; //Lock was unsuccessful
	}

	return ret;
}

/**
 * @details Checks whether the pin is locked by reading from the private member.
 */
GPIO::status GPIO::pin::is_locked(bool &pin_locked)
{
	pin_locked = m_locked;
	return GPIO::status::ok;
}

/**
 * @details Writes a value to the pin via the ODR register.
 */
GPIO::status GPIO::pin::write(uint32_t const val) {
	dartlead_assert(m_port_base_addr != NULL);
	dartlead_assert(m_number <= GPIO_MAX_PIN_NUM);

	if (val) {
		m_port_base_addr->ODR |=   0x1UL << m_number;
	} else {
		m_port_base_addr->ODR &= ~(0x1UL << m_number);
	}

	return GPIO::status::ok;
}

/**
 * @details The atomic nature of the write comes by writing to the BSRR register.
 */
GPIO::status GPIO::pin::write_atomic(uint32_t const val) {
	dartlead_assert(m_port_base_addr != NULL);
	dartlead_assert(m_number <= GPIO_MAX_PIN_NUM);

	uint8_t const clr_bit_offset = 16;

	if (val) {
		m_port_base_addr->BSRR |= 0x1UL << m_number;
	} else {
		m_port_base_addr->BSRR |= 0x1UL << (m_number + clr_bit_offset);
	}

	return GPIO::status::ok;
}

/**
 * @details Reads the value from the pin via the IDR register.
 */
GPIO::status GPIO::pin::read(uint32_t &val) {
	dartlead_assert(m_port_base_addr != NULL);
	dartlead_assert(m_number <= GPIO_MAX_PIN_NUM);

	if (m_port_base_addr->IDR & (0x1UL << m_number)) {
		val = 1;
	} else {
		val = 0;
	}

	return GPIO::status::ok;
}

/**
 * @details Toggles the value of the pin via the ODR register.
 */
GPIO::status GPIO::pin::toggle() {
	dartlead_assert(m_port_base_addr != NULL);
	dartlead_assert(m_number <= GPIO_MAX_PIN_NUM);

	m_port_base_addr->ODR ^= 0x1UL << m_number;

	return GPIO::status::ok;
}

/* EOF */
