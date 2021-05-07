#include "stm32f767zi.h"

/*! FreeRTOS includes.
 */
#include "FreeRTOS.h"
#include "task.h"

/*! STM32F767ZI includes.
 */
#include "onboard_leds.h"
#include "driver_USART.h"

static void __attribute__((section(".text.fast_text"))) LED_toggle_task(void * parameter) {
	TickType_t const delay_200ms    = pdMS_TO_TICKS(200UL);
	TickType_t       last_wake_time = xTaskGetTickCount();

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
		vTaskDelayUntil(&last_wake_time, delay_200ms);

		onboard_blue_led_turn_off();
	}
}

int main(void)
{
	onboard_green_led_init();
	onboard_blue_led_init();
	onboard_red_led_init();

	USART_config_t USART3_config = {
		  .parity            = USART_parity_none
		, .num_stop_bits     = USART_stop_bits_1
		, .word_length       = USART_word_length_8
		, .oversampling_rate = USART_ovrsmpl_rate_16
		, .baud_rate         = 9600
	};
	USART3_config.parity = USART_parity_none;
	USART3_config.num_stop_bits = USART_stop_bits_1;
	USART3_config.word_length = USART_word_length_8;
	USART3_config.oversampling_rate = USART_ovrsmpl_rate_16;
	USART3_config.baud_rate = 9600;

	USART_init(USART3, &USART3_config);

	uint32_t i = 0;
	uint8_t char1 = 'h';
	//uint8_t char2 = 'i';

	while (1) {
		USART3->TDR = char1;

		i = 0;
		while (i++ < 1000);
	}


	/* By default the USART3 interface (PD8 for TX and PD9 for RX) is connected to the ST-Link by virtue of SB5 and
	 * SB6 being present (although so are SB4 and SB7) */

	xTaskCreate(LED_toggle_task, "LED toggle", 500, NULL, 1, NULL);

	vTaskStartScheduler();

	while (1);
	return 0;
}

/* EOF */
