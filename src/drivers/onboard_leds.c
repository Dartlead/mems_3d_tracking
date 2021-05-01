#include "onboard_leds.h"
#include "driver_GPIO.h"

/*! Initializes the onboard LED(s).
 *
 * @note  Green LED is connected to PB0.
 * @note  Blue LED is connected to PB7.
 * @note  Red LED is connected to PB14.
 */
void onboard_green_led_init(void) {
	GPIO_config_t PB0_config = {
		  .GPIO_mode         = GPIO_mode_output
		, .GPIO_output_type  = GPIO_output_type_push_pull
		, .GPIO_output_speed = GPIO_output_speed_low
		, .GPIO_output_speed = GPIO_pull_none
	};
	GPIO_init(GPIOB, 0, &PB0_config);
}

void onboard_blue_led_init(void) {
	GPIO_config_t PB7_config = {
		  .GPIO_mode         = GPIO_mode_output
		, .GPIO_output_type  = GPIO_output_type_push_pull
		, .GPIO_output_speed = GPIO_output_speed_low
		, .GPIO_output_speed = GPIO_pull_none
	};
	GPIO_init(GPIOB, 7, &PB7_config);
}

void onboard_red_led_init(void) {
	GPIO_config_t PB14_config = {
		  .GPIO_mode         = GPIO_mode_output
		, .GPIO_output_type  = GPIO_output_type_push_pull
		, .GPIO_output_speed = GPIO_output_speed_low
		, .GPIO_output_speed = GPIO_pull_none
	};
	GPIO_init(GPIOB, 14, &PB14_config);
}

/*! Turns the onboard LED(s) on.
 *
 * @note  Green LED is connected to PB0.
 * @note  Blue LED is connected to PB7.
 * @note  Red LED is connected to PB14.
 */
void onboard_green_led_turn_on(void) {
	GPIO_write(GPIOB, 0, 1);
}

void onboard_blue_led_turn_on(void) {
	GPIO_write(GPIOB, 7, 1);
}

void onboard_red_led_turn_on(void) {
	GPIO_write(GPIOB, 14, 1);
}

/*! Turns the onboard LED(s) off.
 *
 * @note  Green LED is connected to PB0.
 * @note  Blue LED is connected to PB7.
 * @note  Red LED is connected to PB14.
 */
void onboard_green_led_turn_off(void) {
	GPIO_write(GPIOB, 0, 0);
}

void onboard_blue_led_turn_off(void) {
	GPIO_write(GPIOB, 7, 0);
}

void onboard_red_led_turn_off(void) {
	GPIO_write(GPIOB, 14, 0);
}

/*! Toggles the onboard LED(s).
 *
 * @note  Green LED is connected to PB0.
 * @note  Blue LED is connected to PB7.
 * @note  Red LED is connected to PB14.
 */
void onboard_green_led_toggle(void) {
	GPIO_toggle(GPIOB, 0);
}

void onboard_blue_led_toggle(void) {
	GPIO_toggle(GPIOB, 7);
}

void onboard_red_led_toggle(void) {
	GPIO_toggle(GPIOB, 14);
}

/* EOF */
