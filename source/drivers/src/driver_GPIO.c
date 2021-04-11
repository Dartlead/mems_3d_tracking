#include "driver_GPIO.h"

#include "FreeRTOS.h"

/* ============================================================================================================= */
/* GPIO Access Fucntions                                                                                         */
/* ============================================================================================================= */
/*!
 *
 */
void GPIO_init(GPIO_typedef * const GPIOx
	, GPIO_config_struct const * const config
) {
	return;
}

/*!
 *
 */
void GPIO_set_mode(GPIO_typedef * const GPIOx
	, uint32_t const pin
	, GPIO_mode_typedef const mode
) {
	configASSERT(pin <= 16);
	configASSERT((mode >= GPIO_mode_alt_func_0) && (mode <= GPIO_mode_alt_func_15));

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
			AFR_AFSEL_clear_mask = (pin <= 8) ? (0xFUL << ((pin - 1) * 4)) : (0xFUL << (((pin - 8) - 1) * 4));
			AFR_AFSEL_mask       = (pin <= 8) ? (mode  << ((pin - 1) * 4)) : (mode  << (((pin - 8) - 1) * 4));

			/* Mux the appropriate alternate function via AFR registers */
			if (pin <= 8) {
				GPIOx->AFR[0] = ((GPIOx->AFR[0]) & (~AFR_AFSEL_clear_mask)) | (AFR_AFSEL_mask);
			} else {
				GPIOx->AFR[1] = ((GPIOx->AFR[1]) & (~AFR_AFSEL_clear_mask)) | (AFR_AFSEL_mask);
			}

			/* Change MODE to alternate function */
			GPIOx->MODER = (GPIOx->MODER & ~(0x3UL << ((pin - 1) * 2))) | (0x2UL << ((pin - 1) * 2));

			break;
		case GPIO_mode_input:
			GPIOx->MODER &= ~(0x3UL << ((pin - 1) * 2));
			break;
		case GPIO_mode_output:
			GPIOx->MODER = (GPIOx->MODER & ~(0x3UL << ((pin - 1) * 2))) | (0x1UL << ((pin - 1) * 2));
			break;
		case GPIO_mode_analog:
			GPIOx->MODER |= 0x3UL << ((pin - 1) * 2);
			break;
		default:
			configASSERT(0);
			break;
	}
}

/* EOF */
