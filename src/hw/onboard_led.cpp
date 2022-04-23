#include "onboard_led.h"
#include "driver_GPIO.h"
#include "dartlead_assert.h"
#include <cstddef>

/**
 * @note Red LED is connected to PB14.
 * @note Green LED is connected to PB0.
 * @note Blue LED is connected to PB7.
 */
uint8_t LED::onboard_LED::get_pin(LED::color const LED_color) {
	dartlead_assert((LED_color >= LED::color::red) && (LED_color <= LED::color::blue));

	uint8_t pin = 0;

	switch (LED_color) {
		case LED::color::red:
			pin = 14;
			break;
		case LED::color::green:
			pin = 0;
			break;
		case LED::color::blue:
			pin = 7;
			break;
		default:
			dartlead_WTF;
			break;
	}

	return pin;
}

LED::onboard_LED::onboard_LED(LED::color LED_color) : m_pin(GPIO::port::B, get_pin(LED_color)) {
	switch (LED_color) {
		case LED::color::red:
			m_color = LED::color::red;
			m_pin.set_mode(GPIO::mode::output);
			m_pin.set_output_type(GPIO::output_type::push_pull);
			m_pin.set_output_speed(GPIO::output_speed::low);
			m_pin.set_pull(GPIO::pull::none);
			break;
		case LED::color::green:
			m_color = LED::color::green;
			m_pin.set_mode(GPIO::mode::output);
			m_pin.set_output_type(GPIO::output_type::push_pull);
			m_pin.set_output_speed(GPIO::output_speed::low);
			m_pin.set_pull(GPIO::pull::none);
			break;
		case LED::color::blue:
			m_color = LED::color::blue;
			m_pin.set_mode(GPIO::mode::output);
			m_pin.set_output_type(GPIO::output_type::push_pull);
			m_pin.set_output_speed(GPIO::output_speed::low);
			m_pin.set_pull(GPIO::pull::none);
			break;
		default:
			dartlead_WTF;
			break;
	}
}

LED::onboard_LED::~onboard_LED() {
	m_pin.~pin();
}

LED::status LED::onboard_LED::turn_on() {
	m_pin.write(1);
	return LED::status::ok;
}

LED::status LED::onboard_LED::turn_off() {
	m_pin.write(0);
	return LED::status::ok;
}

LED::status LED::onboard_LED::toggle() {
	m_pin.toggle();
	return LED::status::ok;
}

/* EOF */
