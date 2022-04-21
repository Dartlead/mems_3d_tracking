#ifndef ONBOARD_LED_H
#define ONBOARD_LED_H

#include <cstdint>
#include "driver_GPIO.h"

namespace LED
{
	enum class status : uint8_t {
		  ok
		, error
	};

	enum class color : uint8_t {
		  red
		, green
		, blue
	};

	class onboard_LED {
	public:
		static GPIO::port foo(LED::color LED_color) {
			if (LED_color == LED::color::blue) {
				return GPIO::port::B;
			} else {
				return GPIO::port::A;
			}
		}
		static uint8_t foo2(LED::color LED_color) {
			if (LED_color == LED::color::blue) {
				return 7;
			} else {
				return 6;
			}
		}


		onboard_LED(LED::color LED_color) : pin(foo(LED_color), foo2(LED_color)) {
			if (LED_color == LED::color::blue) {
				pin.set_mode(GPIO::mode::output);
				pin.set_output_type(GPIO::output_type::push_pull);
				pin.set_output_speed(GPIO::output_speed::low);
				pin.set_pull(GPIO::pull::none);
			}
		}

		LED::status turn_on();
		LED::status turn_off();
		LED::status toggle();

	private:
		GPIO::pin pin;
	};
}

#endif /* ONBOARD_LED_H */

/* EOF */
