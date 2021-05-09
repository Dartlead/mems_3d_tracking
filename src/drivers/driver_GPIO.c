#include "driver_GPIO.h"

/*! FreeRTOS includes.
 */
#include "FreeRTOS.h"
#include "task.h"

#define GPIO_MAX_PIN_NUM 15U

/* ============================================================================================================= */
/* GPIO Configuration Functions                                                                                  */
/* ============================================================================================================= */
/*! Gets the default configuration for a GPIO pin.
 *
 */
void GPIO_get_default_config(GPIO_config_t * const config) {
	config->GPIO_mode         = GPIO_mode_output;
	config->GPIO_output_type  = GPIO_output_type_push_pull;
	config->GPIO_output_speed = GPIO_output_speed_low;
	config->GPIO_pull         = GPIO_pull_none;
}

/*! Initializes a GPIO pin.
 *
 */
void GPIO_init(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_config_t const * const config
) {
	/* Enable the peripheral clock to the GPIO port */
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

/*! Sets the mode of the GPIO pin.
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
			AFR_AFSEL_clear_mask = (pin <= 7) ? (0xFUL << (pin * 4)) : (0xFUL << ((pin - 8) * 4));
			AFR_AFSEL_mask       = (pin <= 7) ? (mode  << (pin * 4)) : (mode  << ((pin - 8) * 4));

			/* Mux the appropriate alternate function via AFR registers */
			if (pin <= 7) {
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

/*! Sets the output type of the GPIO pin.
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

/*! Sets the output speed of the GPIO pin.
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

/*! Sets the pin pull of the GPIO pin.
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

/*! Locks a GPIO pin's configuration.
 *
 * @note  The lock sequence is as follows (where LCKR[15:0] contains a '1' in the bit position corresponding to
 *        pin number being locked):
 *        (1) Write LCKR[16] = '1' + LCKR[15:0]
 *        (2) Write LCKR[16] = '0' + LCKR[15:0]
 *        (3) Write LCKR[16] = '1`' + LCKR[15:0]
 *        (4) Read LCKR
 *        (5) Optionally read LCKR to verify LCKR[16] == 1 (confirms that the LOCK is active)
 * @note  The lock sequence can only be performed using word access to the GPIOx_LCKR register due to the fact that
 *        GPIOx_LCKR bit 16 has to be set at the same time as the [15:0] bits.
 * @note  This function is forcibly optimized at -O0 to ensure that the correct lock sequence is respected and not
 *        optimized out.
 * @note  The lock sequence is wrapped in a FreeRTOS critical section b/c during the lock sequence the value of
 *        LCKR[15:0] must not change. Thus whichever task calls this function cannot be context swapped out of.
 */
bool __attribute__((optimize("O0"))) GPIO_lock(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
) {
	configASSERT(GPIOx != NULL);
	configASSERT(pin <= GPIO_MAX_PIN_NUM);

	bool     locked    = false;
	uint32_t LCKR_15_0 = (GPIOx->LCKR & 0xFFFFUL) | (0x1UL << pin);

	taskENTER_CRITICAL();

	/* LOCK write sequence */
	GPIOx->LCKR = 0x10000UL | LCKR_15_0;
	GPIOx->LCKR = LCKR_15_0;
	GPIOx->LCKR = 0x10000UL | LCKR_15_0;
	LCKR_15_0 = GPIOx->LCKR;
	LCKR_15_0 = GPIOx->LCKR;

	taskEXIT_CRITICAL();

	if ((LCKR_15_0 & (0x1UL << 16)) && (LCKR_15_0 & (0x1UL << pin))) {
		locked = true;
	} else {
		locked = false;
	}

	return locked;
}

/*! Checks if a GPIO pin is locked.
 *
 */
bool GPIO_is_locked(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
) {
	configASSERT(GPIOx != NULL);
	configASSERT(pin <= GPIO_MAX_PIN_NUM);

	bool locked = false;

	if ((GPIOx->LCKR & (0x1UL << 16)) && (GPIOx->LCKR & (0x1UL << pin))) {
		locked = true;
	} else {
		locked = false;
	}

	return locked;
}

/* ============================================================================================================= */
/* GPIO Access Functions                                                                                         */
/* ============================================================================================================= */
/*! Writes to a GPIO output pin.
 *
 */
void GPIO_write(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, uint32_t const val
) {
	configASSERT(GPIOx != NULL);
	configASSERT(pin <= GPIO_MAX_PIN_NUM);

	if (val) {
		GPIOx->ODR |= 0x1UL << pin;
	} else {
		GPIOx->ODR &= ~(0x1UL << pin);
	}
}

/*! Atomically writes to a GPIO output pin.
 *
 */
void GPIO_write_atomic(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, uint32_t const val
) {
	configASSERT(GPIOx != NULL);
	configASSERT(pin <= GPIO_MAX_PIN_NUM);

	uint32_t const clr_bit_offset = 16;

	if (val) {
		GPIOx->BSRR |= 0x1UL << pin;
	} else {
		GPIOx->BSRR |= 0x1UL << (pin + clr_bit_offset);
	}
}

/*! Reads from a GPIO input pin.
 *
 */
uint32_t GPIO_read(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
) {
	configASSERT(GPIOx != NULL);
	configASSERT(pin <= GPIO_MAX_PIN_NUM);

	uint32_t val = 0;

	if (GPIOx->IDR & (0x1UL << pin)) {
		val = 1;
	} else {
		val = 0;
	}

	return val;
}

/*! Toggles a GPIO output pin.
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
