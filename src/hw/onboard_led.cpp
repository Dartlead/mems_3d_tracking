#include "onboard_led.h"
#include "driver_GPIO.h"
#include "dartlead_assert.h"
#include <cstddef>

/**
 * @note Green LED is connected to PB0.
 * @note Blue LED is connected to PB7.
 * @note Red LED is connected to PB14.
 */
//onboard_LED::onboard_LED(LED::color const color) {
	//switch (color) {
	//	case LED::color::green:
	//		if (PB0 != NULL) {
	//			PB0 = new GPIO::pin(GPIO::port::B, 0);
	//			color_member = LED::color::green;
	//		}
	//		else {
	//			//Do nothing
	//		}
	//		break;
	//	case LED::color::blue:
	//		if (PB7 != NULL) {
	//			PB7 = new GPIO::pin(GPIO::port::B, 7);
	//			color_member = LED::color::blue;
	//		} else {
	//			//Do nothing
	//		}
	//		break;
	//	case LED::color::red:
	//		if (PB14 != NULL) {
	//			PB14 = new GPIO::pin(GPIO::port::B, 14);
	//			color_member = LED::color::red;
	//		} else {
	//			//Do nothing
	//		}
	//		break;
	//	default:
	//		dartlead_WTF;
	//		break;
	//}
	//return;
//}

//onboard_LED::~onboard_LED() {
	//switch (color_member) {
	//	case LED::color::green:
	//		delete PB0;
	//		break;
	//	case LED::color::blue:
	//		delete PB7;
	//		break;
	//	case LED::color::red:
	//		delete PB14;
	//		break;
	//	default:
	//		dartlead_WTF;
	//		break;
	//}
	//return;
//}

LED::status LED::onboard_LED::turn_on() {
	//switch (color_member) {
	//	case LED::color::green:
	//		PB0->write(1);
	//		break;
	//	case LED::color::blue:
	//		PB7->write(1);
	//		break;
	//	case LED::color::red:
	//		PB14->write(1);
	//		break;
	//	default:
	//		dartlead_WTF;
	//		break;
	//}
	return LED::status::ok;
}

LED::status LED::onboard_LED::turn_off() {
	//switch (color_member) {
	//	case LED::color::green:
	//		PB0->write(0);
	//		break;
	//	case LED::color::blue:
	//		PB7->write(0);
	//		break;
	//	case LED::color::red:
	//		PB14->write(0);
	//		break;
	//	default:
	//		dartlead_WTF;
	//		break;
	//}
	return LED::status::ok;
}

LED::status LED::onboard_LED::toggle() {
	//switch (color_member) {
	//	case LED::color::green:
	//		PB0->toggle();
	//		break;
	//	case LED::color::blue:
	//		PB7->toggle();
	//		break;
	//	case LED::color::red:
	//		PB14->toggle();
	//		break;
	//	default:
	//		dartlead_WTF;
	//		break;
	//}
	return LED::status::ok;
}

/* EOF */
