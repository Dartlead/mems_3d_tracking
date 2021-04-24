#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

#include "stm32f767zi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================================= */
/* GPIO Configuration Enum Options                                                                               */
/* ============================================================================================================= */
/*!
 */
typedef enum GPIO_mode {
	  GPIO_mode_alt_func_0  = 0
	, GPIO_mode_alt_func_1  = 1
	, GPIO_mode_alt_func_2  = 2
	, GPIO_mode_alt_func_3  = 3
	, GPIO_mode_alt_func_4  = 4
	, GPIO_mode_alt_func_5  = 5
	, GPIO_mode_alt_func_6  = 6
	, GPIO_mode_alt_func_7  = 7
	, GPIO_mode_alt_func_8  = 8
	, GPIO_mode_alt_func_9  = 9
	, GPIO_mode_alt_func_10 = 10
	, GPIO_mode_alt_func_11 = 11
	, GPIO_mode_alt_func_12 = 12
	, GPIO_mode_alt_func_13 = 13
	, GPIO_mode_alt_func_14 = 14
	, GPIO_mode_alt_func_15 = 15
	, GPIO_mode_input       = 16
	, GPIO_mode_output      = 17
	, GPIO_mode_analog      = 18
} GPIO_mode_t;

/*!
 */
typedef enum GPIO_output_type {
	  GPIO_output_type_push_pull  = 0
	, GPIO_output_type_open_drain = 1
} GPIO_output_type_t;

/*!
 */
typedef enum GPIO_output_speed {
	  GPIO_output_speed_low       = 0
	, GPIO_output_speed_medium    = 1
	, GPIO_output_speed_high      = 2
	, GPIO_output_speed_very_high = 3
} GPIO_output_speed_t;

/*!
 */
typedef enum GPIO_pull {
	  GPIO_pull_none = 0
	, GPIO_pull_up   = 1
	, GPIO_pull_down = 2
} GPIO_pull_t;

/* ============================================================================================================= */
/* GPIO Configuration Struct                                                                                     */
/* ============================================================================================================= */
/*!
 */
typedef struct GPIO_config {
	GPIO_mode_t         GPIO_mode;
	GPIO_output_type_t  GPIO_output_type;
	GPIO_output_speed_t GPIO_output_speed;
	GPIO_pull_t         GPIO_pull;
} GPIO_config_t;

/* ============================================================================================================= */
/* GPIO Configuration Functions                                                                                  */
/* ============================================================================================================= */
/*!
 *
 */
void GPIO_get_default_config(GPIO_config_t * const config);

/*!
 *
 */
void GPIO_init(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_config_t const * const config
);

/*!
 *
 */
void GPIO_set_mode(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_mode_t const mode
);

/*!
 *
 */
void GPIO_set_output_type(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_output_type_t const output_type
);

/*!
 *
 */
void GPIO_set_output_speed(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_output_speed_t const output_speed
);

/*!
 *
 */
void GPIO_set_pull(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_pull_t const pull
);

/* ============================================================================================================= */
/* GPIO Access Functions                                                                                         */
/* ============================================================================================================= */
/*!
 *
 */
void GPIO_toggle(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
);

//read, write, lock, is_locked

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_GPIO_H */

/* EOF */