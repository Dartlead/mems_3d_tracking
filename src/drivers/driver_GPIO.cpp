#include "driver_GPIO.h"

GPIO::GPIO(port const port_letter
	, pin const pin_num
	, mode const pin_mode
	, output_type const pin_output_type
	, output_speed const pin_output_speed
	, pull const pin_pull
) {
	(void)port_letter;
	(void)pin_num;
	(void)pin_mode;
	(void)pin_output_type;
	(void)pin_output_speed;
	(void)pin_pull;
}

int GPIO::setupPin(int create) {
	return 0;
}

int GPIO::setDirection(int direction) {
	return 0;
}

int GPIO::readValue() {
	return 0;
}

int GPIO::writeValue(int level) {
	return 0;
}