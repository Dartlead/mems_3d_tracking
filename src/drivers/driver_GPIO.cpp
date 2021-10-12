#include "driver_GPIO.h"

GPIO::pin::pin(port_t const pin_port
	, uint8_t         const pin_number
	, mode_t          const pin_mode
	, output_type_t   const pin_output_type
	, output_speed_t  const pin_output_speed
	, pull_t          const pin_pull
) {
	/** Enable the peripheral clock to the GPIO port and update private members */
	//This can fail if the user provides an incorrect port
	switch (pin_port) {
		case GPIO::port_t::port_A:
			RCC->AHB1ENR  |= 0x1UL;
			port           = GPIO::port_t::port_A;
			port_base_addr = GPIOA;
			break;
		case GPIO::port_t::port_B:
			RCC->AHB1ENR |= 0x1UL << 1;
			port           = GPIO::port_t::port_B;
			port_base_addr = GPIOB;
			break;
		case GPIO::port_t::port_C:
			RCC->AHB1ENR |= 0x1UL << 2;
			port           = GPIO::port_t::port_C;
			port_base_addr = GPIOC;
			break;
		case GPIO::port_t::port_D:
			RCC->AHB1ENR |= 0x1UL << 3;
			port           = GPIO::port_t::port_D;
			port_base_addr = GPIOD;
			break;
		case GPIO::port_t::port_E:
			RCC->AHB1ENR |= 0x1UL << 4;
			port           = GPIO::port_t::port_E;
			port_base_addr = GPIOE;
			break;
		case GPIO::port_t::port_F:
			RCC->AHB1ENR |= 0x1UL << 5;
			port           = GPIO::port_t::port_F;
			port_base_addr = GPIOF;
			break;
		case GPIO::port_t::port_G:
			RCC->AHB1ENR |= 0x1UL << 6;
			port           = GPIO::port_t::port_G;
			port_base_addr = GPIOG;
			break;
		case GPIO::port_t::port_H:
			RCC->AHB1ENR |= 0x1UL << 7;
			port           = GPIO::port_t::port_H;
			port_base_addr = GPIOH;
			break;
		case GPIO::port_t::port_I:
			RCC->AHB1ENR |= 0x1UL << 8;
			port           = GPIO::port_t::port_I;
			port_base_addr = GPIOI;
			break;
		case GPIO::port_t::port_J:
			RCC->AHB1ENR |= 0x1UL << 9;
			port           = GPIO::port_t::port_J;
			port_base_addr = GPIOJ;
			break;
		case GPIO::port_t::port_K:
			RCC->AHB1ENR |= 0x1UL << 10;
			port           = GPIO::port_t::port_K;
			port_base_addr = GPIOK;
			break;
		default:
			break;
	}

	/** Set the rest of the private members */
	number       = pin_number;
	mode         = pin_mode;
	output_type  = pin_output_type;
	output_speed = pin_output_speed;
	pull         = pin_pull;
	locked       = false;
}

GPIO::status_t GPIO::pin::set_mode(mode_t const pin_mode) {
	//configASSERT(GPIOx != NULL);
	//configASSERT(pin <= GPIO_MAX_PIN_NUM);
	//configASSERT((mode >= GPIO_mode_alt_func_0) && (mode <= GPIO_mode_analog));

	uint32_t AFR_AFSEL_clear_mask = 0; //!# Bit mask to clear a single AFRL/H AFSELy field
	uint32_t AFR_AFSEL_mask       = 0; //!# Bit mask to set the requested pin's AFRL/H AFSELy field

	GPIO::status_t ret = GPIO::status_t::invalid_pin_mode;

	switch (pin_mode) {
		case GPIO::mode_t::alt_func_0:
		case GPIO::mode_t::alt_func_1:
		case GPIO::mode_t::alt_func_2:
		case GPIO::mode_t::alt_func_3:
		case GPIO::mode_t::alt_func_4:
		case GPIO::mode_t::alt_func_5:
		case GPIO::mode_t::alt_func_6:
		case GPIO::mode_t::alt_func_7:
		case GPIO::mode_t::alt_func_8:
		case GPIO::mode_t::alt_func_9:
		case GPIO::mode_t::alt_func_10:
		case GPIO::mode_t::alt_func_11:
		case GPIO::mode_t::alt_func_12:
		case GPIO::mode_t::alt_func_13:
		case GPIO::mode_t::alt_func_14:
		case GPIO::mode_t::alt_func_15:
			AFR_AFSEL_clear_mask = (number <= 8) ? (0xFUL << (number * 4)) : (0xFUL << ((number - 8) * 4));
			AFR_AFSEL_mask       =
				(number <= 8) ? ((uint32_t)pin_mode << (number * 4)) : ((uint32_t)pin_mode << ((number - 8) * 4));

			/** Mux the appropriate alternate function via AFR registers */
			if (number <= 8) {
				port_base_addr->AFR[0] = (port_base_addr->AFR[0] & ~AFR_AFSEL_clear_mask) | AFR_AFSEL_mask;
			} else {
				port_base_addr->AFR[1] = (port_base_addr->AFR[1] & ~AFR_AFSEL_clear_mask) | AFR_AFSEL_mask;
			}

			/** Change MODE to alternate function */
			port_base_addr->MODER = (port_base_addr->MODER & ~(0x3UL << (number * 2))) | (0x2UL << (number * 2));

			ret = GPIO::status_t::ok;
			break;
		case GPIO::mode_t::input:
			port_base_addr->MODER &= ~(0x3UL << (number * 2));
			ret = GPIO::status_t::ok;
			break;
		case GPIO::mode_t::output:
			port_base_addr->MODER =
				(port_base_addr->MODER & ~(0x3UL << (number * 2))) | (0x1UL << (number * 2));
			ret = GPIO::status_t::ok;
			break;
		case GPIO::mode_t::analog:
			port_base_addr->MODER |= 0x3UL << (number * 2);
			ret = GPIO::status_t::ok;
			break;
		default:
			ret = GPIO::status_t::invalid_pin_mode;
			break;
	}

	/** Update mode private member */
	mode = pin_mode;

	return ret;
}

GPIO::status_t GPIO::pin::set_output_type(output_type_t const pin_output_type) {
	//configASSERT(GPIOx != NULL);
	//configASSERT(pin <= GPIO_MAX_PIN_NUM);
	//configASSERT((output_type >= GPIO_output_type_push_pull) && (output_type <= GPIO_output_type_open_drain));

	GPIO::status_t ret = GPIO::status_t::invalid_pin_output_type;

	switch (pin_output_type) {
		case GPIO::output_type_t::push_pull:
			GPIOx->OTYPER &= ~(0x1UL << number);
			ret = GPIO::status_t::ok;
			break;
		case GPIO::output_type_t::open_drain:
			GPIOx->OTYPER |= 0x1UL << number;
			ret = GPIO::status_t::ok;
			break;
		default:
			ret = GPIO::status_t::invalid_pin_output_type;
			break;
	}

	/** Update output type private member */
	output_type = pin_output_type;

	return ret;
}