#include "driver_GPIO.h"

GPIO::GPIO(port   const port_letter_init
	, pin          const pin_num_init
	, mode         const pin_mode_init
	, output_type  const pin_output_type_init
	, output_speed const pin_output_speed_init
	, pull         const pin_pull_init
) {
	/** Enable the peripheral clock to the GPIO port */
	switch (port_letter_init) {
		case port_A:
			RCC->AHB1ENR |= 0x1UL;
			port_base_addr = GPIOA;
			break;
		case port_B:
			RCC->AHB1ENR |= 0x1UL << 1;
			port_base_addr = GPIOB;
			break;
		case port_C:
			RCC->AHB1ENR |= 0x1UL << 2;
			port_base_addr = GPIOC;
			break;
		case port_D:
			RCC->AHB1ENR |= 0x1UL << 3;
			port_base_addr = GPIOD;
			break;
		case port_E:
			RCC->AHB1ENR |= 0x1UL << 4;
			port_base_addr = GPIOE;
			break;
		case port_F:
			RCC->AHB1ENR |= 0x1UL << 5;
			port_base_addr = GPIOF;
			break;
		case port_G:
			RCC->AHB1ENR |= 0x1UL << 6;
			port_base_addr = GPIOG;
			break;
		case port_H:
			RCC->AHB1ENR |= 0x1UL << 7;
			port_base_addr = GPIOH;
			break;
		case port_I:
			RCC->AHB1ENR |= 0x1UL << 8;
			port_base_addr = GPIOI;
			break;
		case port_J:
			RCC->AHB1ENR |= 0x1UL << 9;
			port_base_addr = GPIOJ;
			break;
		case port_K:
			RCC->AHB1ENR |= 0x1UL << 10;
			port_base_addr = GPIOK;
			break;
		default:
			configASSERT(0);
			break;
	}

	//set mode
	//set output type
	//set output speed
	//set pull
}

GPIO_status GPIO::set_mode(mode_t const pin_mode) {
	mode = pin_mode;

	//Some asserts()??



	uint32_t AFR_AFSEL_clear_mask = 0; //!# Bit mask to clear a single AFRl/H AFSELy field
	uint32_t AFR_AFSEL_mask       = 0; //!# Bit mask to set the requested pin's AFRL/H AFSELy field

	switch (mode) {
		case GPIO_mode_alt_func_0:
		case GPIO_mode_alt_func_1:
		case GPIO_mode_alt_func_2:
		case GPIO_mode_alt_func_3:
		case GPIO_mode_alt_func_4:
		case GPIO_mode_alt_func_5:
		case GPIO_mode_alt_func_6:
		case GPIO_mode_alt_func_7:
		case GPIO_mode_alt_func_8:
		case GPIO_mode_alt_func_9:
		case GPIO_mode_alt_func_10:
		case GPIO_mode_alt_func_11:
		case GPIO_mode_alt_func_12:
		case GPIO_mode_alt_func_13:
		case GPIO_mode_alt_func_14:
		case GPIO_mode_alt_func_15:
			AFR_AFSEL_clear_mask = (pin <= 8) ? (0xFUL << (pin * 4)) : (0xFUL << ((pin - 8) * 4));
			AFR_AFSEL_mask       = (pin <= 8) ? (mode  << (pin * 4)) : (mode  << ((pin - 8) * 4));

			/* Mux the appropriate alternate function via AFR registers */
			if (pin <= 8) {
				GPIOx->AFR[0] = (GPIOx->AFR[0] & ~AFR_AFSEL_clear_mask) | AFR_AFSEL_mask;
			} else {
				GPIOx->AFR[1] = (GPIOx->AFR[1] & ~AFR_AFSEL_clear_mask) | AFR_AFSEL_mask;
			}

			/* Change MODE to alternate function */
			GPIOx->MODER = (GPIOx->MODER & ~(0x3UL << (pin * 2))) | (0x2UL << (pin * 2));

			break;
		case GPIO_mode_input:
			GPIOx->MODER &= ~(0x3UL << (pin * 2));
			break;
		case GPIO_mode_output:
			GPIOx->MODER = (GPIOx->MODER & ~(0x3UL << (pin * 2))) | (0x1UL << (pin * 2));
			break;
		case GPIO_mode_analog:
			GPIOx->MODER |= 0x3UL << (pin * 2);
			break;
		default:
			WTF;
			break;
	}

	return GPIO_status_ok;
}