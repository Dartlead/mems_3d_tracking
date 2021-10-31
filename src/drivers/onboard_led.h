#ifndef ONBOARD_LED_H
#define ONBOARD_LED_H

#include <cstdint>

namespace LED
{
	enum class color : uint8_t {
		  green /**< Onboard green LED */
		, blue  /**< Onboard blue LED  */
		, red   /**< Onboard red LED   */
	};

	enum class status : uint8_t {
		  ok
		, error
	};
}

class onboard_LED {
	private:
		LED::color color_member;

	public:
		onboard_LED(LED::color const color);
		~onboard_LED();

		LED::status turn_on();
		LED::status turn_off();
		LED::status toggle();
};

#endif /* ONBOARD_LED_H */

/* EOF */
