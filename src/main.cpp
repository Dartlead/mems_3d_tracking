#include "stm32f767zi.h"

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"

/* STM32F767ZI includes */
#include "driver_GPIO.h"
#include "onboard_led.h"

static void __attribute__((section(".text.fast_text"))) LED_toggle_task(void * parameter) {
	TickType_t const delay_200ms    = pdMS_TO_TICKS(200UL);
	TickType_t       last_wake_time = xTaskGetTickCount();

	//onboard_LED blue_led(LED::Color::blue);
	//blue_led.turn_on();

	/* Init green LED */
	GPIO::pin PB0(GPIO::port::B, (uint8_t)0);
	PB0.set_mode(GPIO::mode::output);
	PB0.set_output_type(GPIO::output_type::push_pull);
	PB0.set_output_speed(GPIO::output_speed::low);
	PB0.set_pull(GPIO::pull::none);

	/* Init blue LED */
	GPIO::pin PB7(GPIO::port::B, (uint8_t)7);
	PB7.set_mode(GPIO::mode::output);
	PB7.set_output_type(GPIO::output_type::push_pull);
	PB7.set_output_speed(GPIO::output_speed::low);
	PB7.set_pull(GPIO::pull::none);

	/* Init red LED */
	GPIO::pin PB14(GPIO::port::B, (uint8_t)14);
	PB14.set_mode(GPIO::mode::output);
	PB14.set_output_type(GPIO::output_type::push_pull);
	PB14.set_output_speed(GPIO::output_speed::low);
	PB14.set_pull(GPIO::pull::none);

	while (1) {
		vTaskDelayUntil(&last_wake_time, delay_200ms);

		PB0.toggle();
		PB7.toggle();
		PB14.toggle();
	}
}

int main(void)
{
	xTaskCreate(LED_toggle_task, "LED toggle", 500, NULL, 1, NULL);

	vTaskStartScheduler();

	while (1);
	return 0;
}

/* EOF */
