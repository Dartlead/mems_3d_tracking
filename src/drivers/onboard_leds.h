#ifndef ONBOARD_LEDS_H
#define ONBOARD_LEDS_H

/*! Initializes the onboard LED(s).
 *
 */
void onboard_green_led_init(void);
void onboard_blue_led_init(void);
void onboard_red_led_init(void);

/*! Turns the onboard LED(s) on.
 *
 */
void onboard_green_led_turn_on(void);
void onboard_blue_led_turn_on(void);
void onboard_red_led_turn_on(void);

/*! Turns the onboard LED(s) off.
 *
 */
void onboard_green_led_turn_off(void);
void onboard_blue_led_turn_off(void);
void onboard_red_led_turn_off(void);

/*! Toggles the onboard LED(s).
 *
 */
void onboard_green_led_toggle(void);
void onboard_blue_led_toggle(void);
void onboard_red_led_toggle(void);

#endif /* ONBOARD_LEDS_H */

/* EOF */
