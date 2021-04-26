#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

#include <stdbool.h>
#include "stm32f767zi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================================= */
/* GPIO Configuration Enum Options                                                                               */
/* ============================================================================================================= */
/*! Enumeration of GPIO pin modes.
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

/*! Enumeration of GPIO pin output types.
 */
typedef enum GPIO_output_type {
	  GPIO_output_type_push_pull  = 0
	, GPIO_output_type_open_drain = 1
} GPIO_output_type_t;

/*! Enumeration of GPIO pin output speeds.
 */
typedef enum GPIO_output_speed {
	  GPIO_output_speed_low       = 0
	, GPIO_output_speed_medium    = 1
	, GPIO_output_speed_high      = 2
	, GPIO_output_speed_very_high = 3
} GPIO_output_speed_t;

/*! Enumeration of GPIO pin pulls.
 */
typedef enum GPIO_pull {
	  GPIO_pull_none = 0
	, GPIO_pull_up   = 1
	, GPIO_pull_down = 2
} GPIO_pull_t;

/* ============================================================================================================= */
/* GPIO Configuration Struct                                                                                     */
/* ============================================================================================================= */
/*! Structure containing GPIO pin configuration options.
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
/*! Gets the default configuration for a GPIO pin.
 *
 * @brief Default GPIO pin configuration is an output, push-pull pin with no pull-up/pull-down resistors at low
 *        switching speed.
 *
 * @param config
 *    (input/output) The default configuration for a GPIO pin.
 */
void GPIO_get_default_config(GPIO_config_t * const config);

/*! Initializes a GPIO pin.
 *
 * @param GPIOx
 *    (input) The GPIO port. See device/registers/stm32f767zi_registers_GPIO.h for options.
 * @param pin
 *    (input) The pin number to configure (must be between 0 and 15, inclusive).
 * @param config
 *    (input) The configuration for the pin being configured.
 */
void GPIO_init(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_config_t const * const config
);

/*! Sets the mode of the GPIO pin.
 *
 * @param GPIOx
 *    (input) The GPIO port. See device/registers/stm32f767zi_registers_GPIO.h for options.
 * @param pin
 *    (input) The pin number to configure (must be between 0 and 15, inclusive).
 * @param mode
 *    (input) The desired mode for the GPIO pin.
 */
void GPIO_set_mode(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_mode_t const mode
);

/*! Sets the output type of the GPIO pin.
 *
 * @param GPIOx
 *    (input) The GPIO port. See device/registers/stm32f767zi_registers_GPIO.h for options.
 * @param pin
 *    (input) The pin number to configure (must be between 0 and 15, inclusive).
 * @param output_type
 *    (input) The desired output type for the GPIO pin.
 */
void GPIO_set_output_type(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_output_type_t const output_type
);

/*! Sets the output speed of the GPIO pin.
 *
 * @param GPIOx
 *    (input) The GPIO port. See device/registers/stm32f767zi_registers_GPIO.h for options.
 * @param pin
 *    (input) The pin number to configure (must be between 0 and 15, inclusive).
 * @param output_speed
 *    (input) The desired output speed for the GPIO pin.
 */
void GPIO_set_output_speed(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_output_speed_t const output_speed
);

/*! Sets the pin pull of the GPIO pin.
 *
 * @param GPIOx
 *    (input) The GPIO port. See device/registers/stm32f767zi_registers_GPIO.h for options.
 * @param pin
 *    (input) The pin number to configure (must be between 0 and 15, inclusive).
 * @param pull
 *    (input) The presence (if any) of pull-up/pull-down resistors for the pin.
 */
void GPIO_set_pull(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, GPIO_pull_t const pull
);

/*! Locks a GPIO pin's configuration.
 *
 * @brief Locks the configuration of the pin until the next MCU reset or peripheral reset.
 *
 * @param GPIOx
 *    (input) The GPIO port. See device/registers/stm32f767zi_registers_GPIO.h for options.
 * @param pin
 *    (input) The pin number to lock (must be between 0 and 15, inclusive).
 * @return 'true' if the lock operation was successful, 'false' otherwise.
 */
bool GPIO_lock(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
);

/*! Checks if a GPIO pin is locked.
 *
 * @param GPIOx
 *    (input) The GPIO port. See device/registers/stm32f767zi_registers_GPIO.h for options.
 * @param pin
 *    (input) The pin number to lock (must be between 0 and 15, inclusive).
 */
bool GPIO_is_locked(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
);

/* ============================================================================================================= */
/* GPIO Access Functions                                                                                         */
/* ============================================================================================================= */
/*! Writes to a GPIO output pin.
 *
 * @param GPIOx
 *    (input) The GPIO port. See device/registers/stm32f767zi_registers_GPIO.h for options.
 * @param pin
 *    (input) The pin number to write to (must be between 0 and 15, inclusive).
 * @param val
 *    (input) The value to write to the pin (must be 0 or 1).
 */
void GPIO_write(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, uint32_t const val
);

/*! Atomically writes to a GPIO output pin.
 *
 * @param GPIOx
 *    (input) The GPIO port. See device/registers/stm32f767zi_registers_GPIO.h for options.
 * @param pin
 *    (input) The pin number to write to (must be between 0 and 15, inclusive).
 * @param val
 *    (input) The value to write to the pin (must be 0 or 1).
 */
void GPIO_write_atomic(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
	, uint32_t const val
);

/*! Reads from a GPIO input pin.
 *
 * @param GPIOx
 *    (input) The GPIO port. See device/registers/stm32f767zi_registers_GPIO.h for options.
 * @param pin
 *    (input) The pin number to read from (must be between 0 and 15, inclusive).
 */
uint32_t GPIO_read(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
);

/*! Toggles a GPIO output pin.
 *
 * @param GPIOx
 *    (input) The GPIO port. See device/registers/stm32f767zi_registers_GPIO.h for options.
 * @param pin
 *    (input) The pin number to toggle (must be between 0 and 15, inclusive).
 */
void GPIO_toggle(GPIO_TypeDef * const GPIOx
	, uint32_t const pin
);

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_GPIO_H */

/* EOF */
