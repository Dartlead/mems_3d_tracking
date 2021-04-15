#include "driver_GPIO.h"

#include "FreeRTOS.h"

#define GPIO_MAX_PIN_NUM 15

/* ============================================================================================================= */
/* GPIO Configuration Functions                                                                                  */
/* ============================================================================================================= */
/*!
 *
 */
void GPIO_get_default_config(GPIO_config_t * const config) {
	config->GPIO_mode         = GPIO_mode_output;
	config->GPIO_output_type  = GPIO_output_type_push_pull;
	config->GPIO_output_speed = GPIO_output_speed_low;
	config->GPIO_pull         = GPIO_pull_none;
}

/*!
 *
 */
void GPIO_init(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_config_t const * const config
) {
	/* Enable the clock to the GPIO port */
	if (GPIOx == GPIOA) {
		RCC->AHB1ENR |= 0x1UL;
	} else if (GPIOx == GPIOB) {
		RCC->AHB1ENR |= 0x1UL << 1;
	} else if (GPIOx == GPIOC) {
		RCC->AHB1ENR |= 0x1UL << 2;
	} else if (GPIOx == GPIOD) {
		RCC->AHB1ENR |= 0x1UL << 3;
	} else if (GPIOx == GPIOE) {
		RCC->AHB1ENR |= 0x1UL << 4;
	} else if (GPIOx == GPIOF) {
		RCC->AHB1ENR |= 0x1UL << 5;
	} else if (GPIOx == GPIOG) {
		RCC->AHB1ENR |= 0x1UL << 6;
	} else if (GPIOx == GPIOH) {
		RCC->AHB1ENR |= 0x1UL << 7;
	} else if (GPIOx == GPIOI) {
		RCC->AHB1ENR |= 0x1UL << 8;
	} else if (GPIOx == GPIOJ) {
		RCC->AHB1ENR |= 0x1UL << 9;
	} else if (GPIOx == GPIOK) {
		RCC->AHB1ENR |= 0x1UL << 10;
	} else {
		WTF;
	}

	GPIO_set_mode(GPIOx, pin, config->GPIO_mode);
	GPIO_set_output_type(GPIOx, pin, config->GPIO_output_type);
	GPIO_set_output_speed(GPIOx, pin, config->GPIO_output_speed);
	GPIO_set_pull(GPIOx, pin, config->GPIO_pull);
}

/*!
 *
 * @note  The alternate function (AFRL/H) MUST be set before the mode (MODER) otherwise there will be glitches on
 *        output line.
 */
void GPIO_set_mode(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_mode_t const mode
) {
	configASSERT(GPIOx != NULL);
	configASSERT(pin <= GPIO_MAX_PIN_NUM);
	configASSERT((mode >= GPIO_mode_alt_func_0) && (mode <= GPIO_mode_analog));

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
}

/*!
 *
 */
void GPIO_set_output_type(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_output_type_t const output_type
) {
	configASSERT(GPIOx != NULL);
	configASSERT(pin <= GPIO_MAX_PIN_NUM);
	configASSERT((output_type >= GPIO_output_type_push_pull) && (output_type <= GPIO_output_type_open_drain));

	switch (output_type) {
		case GPIO_output_type_push_pull:
			GPIOx->OTYPER &= ~(0x1UL << pin);
			break;
		case GPIO_output_type_open_drain:
			GPIOx->OTYPER |= 0x1UL << pin;
			break;
		default:
			WTF;
			break;
	}
}

/*!
 *
 */
void GPIO_set_output_speed(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_output_speed_t const output_speed
) {
	configASSERT(GPIOx != NULL);
	configASSERT(pin <= GPIO_MAX_PIN_NUM);
	configASSERT((output_speed >= GPIO_output_speed_low) && (output_speed <= GPIO_output_speed_very_high));

	switch (output_speed) {
		case GPIO_output_speed_low:
			GPIOx->OSPEEDR &= ~(0x3UL << (pin * 2));
			break;
		case GPIO_output_speed_medium:
			GPIOx->OSPEEDR = (GPIOx->OSPEEDR & ~(0x3UL << (pin * 2))) | (0x1UL << (pin * 2));
			break;
		case GPIO_output_speed_high:
			GPIOx->OSPEEDR = (GPIOx->OSPEEDR & ~(0x3UL << (pin * 2))) | (0x2UL << (pin * 2));
			break;
		case GPIO_output_speed_very_high:
			GPIOx->OSPEEDR |= 0x3UL << (pin * 2);
			break;
		default:
			WTF;
			break;
	}
}

/*!
 *
 */
void GPIO_set_pull(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_pull_t const pull
) {
	configASSERT(GPIOx != NULL);
	configASSERT(pin <= GPIO_MAX_PIN_NUM);
	configASSERT((pull >= GPIO_pull_none) && (pull <= GPIO_pull_down));

	switch (pull) {
		case GPIO_pull_none:
			GPIOx->PUPDR &= ~(0x3UL << (pin * 2));
			break;
		case GPIO_pull_up:
			GPIOx->PUPDR = (GPIOx->PUPDR & ~(0x3UL << (pin * 2))) | (0x1UL << (pin * 2));
			break;
		case GPIO_pull_down:
			GPIOx->PUPDR = (GPIOx->PUPDR & ~(0x3UL << (pin * 2))) | (0x2UL << (pin * 2));
			break;
		default:
			WTF;
			break;
	}
}

/* ============================================================================================================= */
/* GPIO Access Functions                                                                                         */
/* ============================================================================================================= */
/*!
 *
 */
void GPIO_toggle(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
) {
	configASSERT(GPIOx != NULL);
	configASSERT(pin <= GPIO_MAX_PIN_NUM);

	GPIOx->ODR ^= 0x1UL << pin;
}

/* EOF */
