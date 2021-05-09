#include "stm32f767zi.h"

/*! FreeRTOS includes.
 */
#include "FreeRTOS.h"
#include "task.h"

/*! STM32F767ZI includes.
 */
#include "dartlead_printf.h"
#include "onboard_leds.h"

static void __attribute__((section(".text.fast_text"))) LED_toggle_task(void * parameter) {
	TickType_t const delay_200ms    = pdMS_TO_TICKS(200UL);
	TickType_t       last_wake_time = xTaskGetTickCount();

	uint32_t i = 0;
	uint8_t char1 = 'h';
	uint8_t char2 = 'i';
	uint8_t char3 = '\r';
	uint8_t char4 = '\n';

	while (1) {
		onboard_green_led_turn_on();
		vTaskDelayUntil(&last_wake_time, delay_200ms);

		onboard_green_led_turn_off();
		onboard_blue_led_turn_on();
		vTaskDelayUntil(&last_wake_time, delay_200ms);

		onboard_blue_led_turn_off();
		onboard_red_led_turn_on();
		vTaskDelayUntil(&last_wake_time, delay_200ms);

		onboard_red_led_turn_off();
		onboard_blue_led_turn_on();
		USART3->TDR = char1;
		i = 0;
		while (i++ < 1000);

		USART3->TDR = char2;
		i = 0;
		while (i++ < 1000);

		USART3->TDR = char3;
		i = 0;
		while (i++ < 1000);

		USART3->TDR = char4;
		i = 0;
		while (i++ < 1000);
		vTaskDelayUntil(&last_wake_time, delay_200ms);

		onboard_blue_led_turn_off();
	}
}

int main(void)
{
	onboard_green_led_init();
	onboard_blue_led_init();
	onboard_red_led_init();

	dartlead_printf_init();

	xTaskCreate(LED_toggle_task, "LED toggle", 500, NULL, 1, NULL);

	vTaskStartScheduler();

	while (1);
	return 0;
}

/* EOF */
