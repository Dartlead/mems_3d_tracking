#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

#include <cstdint>
#include "stm32f767zi.h"

namespace GPIO
{
	/**
	 * @enum Enumeration of all available GPIO ports.
	 */
	enum class port_t : uint8_t {
		  A /**< GPIO Port A */
		, B /**< GPIO Port B */
		, C /**< GPIO Port C */
		, D /**< GPIO Port D */
		, E /**< GPIO Port E */
		, F /**< GPIO Port F */
		, G /**< GPIO Port G */
		, H /**< GPIO Port H */
		, I /**< GPIO Port I */
		, J /**< GPIO Port J */
		, K /**< GPIO Port K */
	};

	/**
	 * @enum Enumeration of all possible GPIO pin modes.
	 */
	enum class mode_t : uint8_t {
		  alt_func_0  /**< Alternate Function Mode 0        */
		, alt_func_1  /**< Alternate Function Mode 1        */
		, alt_func_2  /**< Alternate Function Mode 2        */
		, alt_func_3  /**< Alternate Function Mode 3        */
		, alt_func_4  /**< Alternate Function Mode 4        */
		, alt_func_5  /**< Alternate Function Mode 5        */
		, alt_func_6  /**< Alternate Function Mode 6        */
		, alt_func_7  /**< Alternate Function Mode 7        */
		, alt_func_8  /**< Alternate Function Mode 8        */
		, alt_func_9  /**< Alternate Function Mode 9        */
		, alt_func_10 /**< Alternate Function Mode 10       */
		, alt_func_11 /**< Alternate Function Mode 11       */
		, alt_func_12 /**< Alternate Function Mode 12       */
		, alt_func_13 /**< Alternate Function Mode 13       */
		, alt_func_14 /**< Alternate Function Mode 14       */
		, alt_func_15 /**< Alternate Function Mode 15       */
		, input       /**< Input Mode                       */
		, output      /**< Output Mode                      */
		, analog      /**< High-impedance Analog-Input Mode */
	};

	/**
	 * @enum Enumeration of different output buffer modes when pin is in Output Mode.
	 */
	enum class output_type_t : uint8_t {
		  push_pull  /**< Push-Pull  */
		, open_drain /**< Open-Drain */
	};

	/**
	 * @enum Enumeration of maximum toggling frequencies for pins.
	 * @details View Table 67. I/O AC characteristics in the datasheet (DS11532 Rev 7).
	 */
	enum class output_speed_t : uint8_t {
		  low       /**< Maximum toggling speed of 8 MHz (depending on V_DD and C_L)   */
		, medium    /**< Maximum toggling speed of 50 MHz (depending on V_DD and C_L)  */
		, high      /**< Maximum toggling speed of 100 MHz (depending on V_DD and C_L) */
		, very_high /**< Maximum toggling speed of 180 MHz (depending on V_DD and C_L) */
	};

	/**
	 * @enum Enumeration of internal weak pull resistors options for pins.
	 * @details View Table 65. I/O static characteristics in the datasheet (DS11532 Rev 7).
	 */
	enum class pull_t : uint8_t {
		  none /**< No internal pull-up or pull-down resistor   */
		, up   /**< 50/14 kohm weak internal pull-up resistor   */
		, down /**< 50/14 kohm weak internal pull-down resistor */
	};

	/**
	 * @enum Enumeration of status return values for all pin methods.
	 */
	enum class status_t : uint8_t {
		  ok                      /**< No issues, method operated successfully */
		, invalid_pin_mode        /**< Invalid pin mode                        */
		, invalid_pin_output_type /**< Invalid pin output type                 */
	};

	class pin {
	private:
		port_t         port;
		GPIO_TypeDef * port_base_addr;
		uint8_t        number;
		mode_t         mode;
		output_type_t  output_type;
		output_speed_t output_speed;
		pull_t         pull;
		bool           locked;

	public:
		pin( port_t         const pin_port
			, uint8_t        const pin_number
			, mode_t         const pin_mode
			, output_type_t  const pin_output_type
			, output_speed_t const pin_output_speed
			, pull_t         const pin_pull
		);

		status_t set_mode(mode_t const pin_mode);
		status_t set_output_type(output_type_t const pin_output_type);
		status_t set_output_speed(output_speed_t const pin_output_speed);
		status_t set_pull(pull_t const pin_pull);

		status_t lock_config(void);
		status_t is_locked(bool &locked);

		status_t write(uint32_t const val);
		status_t write_atomic(uint32_t const val);
		status_t read(uint32_t &val);
		status_t toggle(void);
	};
}

#endif /* DRIVER_GPIO_H */

/* EOF */
