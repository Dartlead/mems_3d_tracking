#include "onboard_led.h"
#include "driver_GPIO.h"
#include <cstddef>

static GPIO::pin * const PB0  = NULL;
static GPIO::pin * const PB7  = NULL;
static GPIO::pin * const PB14 = NULL;

/**
 * @note Green LED is connected to PB0.
 * @note Blue LED is connected to PB7.
 * @note Red LED is connected to PB14.
 */
onboard_LED::onboard_LED(LED::color const color) {
	switch (color)
	{
		case LED::color::green:
			break;
		case LED::color::blue:
			break;
		case LED::color::red:
			break;
		default:
			break;
	}
}

LED::status onboard_LED::turn_on() {
	return LED::status::ok;
}

LED::status onboard_LED::turn_off() {
	return LED::status::ok;
}

LED::status onboard_LED::toggle() {
	return LED::status::ok;
}

/* EOF */
