#include "stm32f767zi.h"

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"

/* STM32F767ZI includes */
#include "driver_GPIO.h"
#include "onboard_led.h"

/**
 * @brief Toggles all three onboard LEDs every 200 ms.
 */
static void __attribute__((section(".text.fast_text"))) LED_toggle_task(void * parameter) {
	TickType_t const delay_200ms    = pdMS_TO_TICKS(200UL);
	TickType_t       last_wake_time = xTaskGetTickCount();

	LED::onboard_LED red_led(LED::color::red);
	LED::onboard_LED green_led(LED::color::green);
	LED::onboard_LED blue_led(LED::color::blue);

	while (1) {
		vTaskDelayUntil(&last_wake_time, delay_200ms);

		red_led.toggle();
		green_led.toggle();
		blue_led.toggle();
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
