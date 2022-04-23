#ifndef ONBOARD_LED_H
#define ONBOARD_LED_H

#include <cstdint>
#include "driver_GPIO.h"

namespace LED
{
	/**
	 * @enum Enumeration of status return values for all onboard_LED methods.
	 */
	enum class status : uint8_t {
		  ok    /**< No issues, method operated successfully */
		, error /**< Generalized error                       */
	};

	/**
	 * @enum Enumeration of different onboard LED colors.
	 */
	enum class color : uint8_t {
		  red   /**< Onboard red LED   */
		, green /**< Onboard green LED */
		, blue  /**< Onboard blue LED  */
	};

	class onboard_LED {
	private:
		GPIO::pin m_pin;   /**< The GPIO pin object tied to the particular onboard LED */
		color     m_color; /**< The color of the onboard LED                           */

		/**
		 * @brief Gets the pin number for the GPIO of the onboard LED.
		 * @param [in] LED_color
		 *    The onboard LED whose pin number is being requested.
		 * @return The pin number.
		 */
		static uint8_t get_pin(LED::color LED_color);

	public:
		onboard_LED(LED::color const LED_color);
		~onboard_LED();

		LED::status turn_on();
		LED::status turn_off();
		LED::status toggle();
	};
}

#endif /* ONBOARD_LED_H */

/* EOF */
