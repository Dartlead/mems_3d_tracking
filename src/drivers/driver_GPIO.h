#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

#include <cstdint>
#include "stm32f767zi.h"

namespace GPIO {
	/**
	 * @enum Enumeration of all available GPIO ports.
	 */
	enum class port : uint8_t {
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
	enum class mode : uint8_t {
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
	enum class output_type : uint8_t {
		  push_pull  /**< Push-Pull  */
		, open_drain /**< Open-Drain */
	};

	/**
	 * @enum Enumeration of maximum toggling frequencies for pins.
	 * @details View Table 67. I/O AC characteristics in the datasheet (DS11532 Rev 7).
	 */
	enum class output_speed : uint8_t {
		  low       /**< Maximum toggling speed of 8 MHz (depending on V_DD and C_L)   */
		, medium    /**< Maximum toggling speed of 50 MHz (depending on V_DD and C_L)  */
		, high      /**< Maximum toggling speed of 100 MHz (depending on V_DD and C_L) */
		, very_high /**< Maximum toggling speed of 180 MHz (depending on V_DD and C_L) */
	};

	/**
	 * @enum Enumeration of internal weak pull resistors options for pins.
	 * @details View Table 65. I/O static characteristics in the datasheet (DS11532 Rev 7).
	 */
	enum class pull : uint8_t {
		  none /**< No internal pull-up or pull-down resistor   */
		, up   /**< 50/14 kohm weak internal pull-up resistor   */
		, down /**< 50/14 kohm weak internal pull-down resistor */
	};

	/**
	 * @enum Enumeration of status return values for all pin methods.
	 */
	enum class status : uint8_t {
		  ok                       /**< No issues, method operated successfully */
		, invalid_pin_mode         /**< Invalid pin mode                        */
		, invalid_pin_output_type  /**< Invalid pin output type                 */
		, invalid_pin_output_speed /**< Invalid pin output speed                */
		, invalid_pin_pull         /**< Invalid pin pull                        */
		, lock_failed              /**< Failed to lock the pin's configuration  */
	};

	class pin {
	private:
		port           m_port;           /**< GPIO port of the pin                      */
		GPIO_TypeDef * m_port_base_addr; /**< Base address of the GPIO port             */
		uint8_t        m_number;         /**< Pin number                                */
		mode           m_mode;           /**< Mode of the pin                           */
		output_type    m_output_type;    /**< Output type of the pin                    */
		output_speed   m_output_speed;   /**< Output speed of the pin                   */
		pull           m_pull;           /**< Pull of the pin                           */
		bool           m_locked;         /**< Whether the pin's configuration is locked */

	public:
		/**
		 * @brief GPIO pin constructor.
		 * @param [in] pin_port
		 *    The port associated with the pin.
		 * @param [in] pin_number
		 *    The number of the pin being constructed.
		 */
		pin(port const pin_port, uint8_t const pin_number);

		/**
		 * @brief GPIO pin destructor.
		 */
		~pin();

		/**
		 * @brief Sets the mode of the GPIO pin.
		 * @param [in] pin_mode
		 *    The requested mode of the pin.
		 * @return GPIO pin status.
		 */
		status set_mode(mode const pin_mode);

		/**
		 * @brief Sets the output type of the GPIO pin.
		 * @param [in] pin_output_type
		 *    The output type of the pin.
		 * @return GPIO pin status.
		 */
		status set_output_type(output_type const pin_output_type);

		/**
		 * @brief Sets the output speed of the GPIO pin.
		 * @param [in] pin_output_speed
		 *    The output speed of the pin.
		 * @return GPIO pin status.
		 */
		status set_output_speed(output_speed const pin_output_speed);

		/**
		 * @brief Sets the pull of the GPIO pin.
		 * @param [in] pin_pull
		 *    The pull of the pin.
		 * @return GPIO pin status.
		 */
		status set_pull(pull const pin_pull);

		/**
		 * @brief Locks the GPIO pin configuration.
		 * @return GPIO pin status.
		 */
		status lock_config();

		/**
		 * @brief Checks if the GPIO pin's configuration is locked.
		 * @param [inout] pin_locked
		 *    Whether the pin's configuration is locked or not.
		 * @return GPIO pin status.
		 */
		status is_locked(bool &pin_locked);

		/**
		 * @brief Writes a value to the GPIO pin.
		 * @param [in] val
		 *    The value to write to the GPIO pin.
		 * @return GPIO pin status.
		 */
		status write(uint32_t const val);

		/**
		 * @brief Writes a value to the GPIO pin atomically.
		 * @param [in] val
		 *    The value to write to the GPIO pin.
		 * @return GPIO pin status.
		 */
		status write_atomic(uint32_t const val);

		/**
		 * @brief Writes a value to the GPIO pin atomically.
		 * @brief Reads the current state of the GPIO pin.
		 * @param [inout] val
		 *    The current state of the GPIO pin.
		 * @return GPIO pin status.
		 */
		status read(uint32_t &val);

		/**
		 * @brief Toggles the GPIO pin.
		 * @return GPIO pin status.
		 */
		status toggle();
	};
}

#endif /* DRIVER_GPIO_H */

/* EOF */
