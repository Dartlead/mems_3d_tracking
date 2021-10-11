#include "stm32f767zi.h"

/*! FreeRTOS includes.
 */
#include "FreeRTOS.h"
#include "task.h"

/*! STM32F767ZI includes.
 */
//#include "onboard_leds.h"

static void __attribute__((section(".text.fast_text"))) LED_toggle_task(void * parameter) {
	TickType_t const delay_200ms    = pdMS_TO_TICKS(200UL);
	TickType_t       last_wake_time = xTaskGetTickCount();

	while (1) {
		vTaskDelayUntil(&last_wake_time, delay_200ms);

		GPIOB->ODR ^= 0x1UL << 0;
	}
}

#include "driver_GPIO.h"

int main(void)
{
	/* Configure the green LED */
	RCC->AHB1ENR |= 0x1UL << 1;
	GPIOB->MODER = (GPIOB->MODER & ~(0x3UL << (0 * 2))) | (0x1UL << (0 * 2));
	GPIOB->OTYPER &= ~(0x1UL << 0);
	GPIOB->OSPEEDR &= ~(0x3UL << 0);
	GPIOB->PUPDR &= ~(0x3UL << 0);

	GPIO::port_t PB6_port = GPIO::port_t::port_B;
	GPIO::pin_t  PB6_pin  = GPIO::pin_t::pin_6;
	GPIO::mode_t PB6_mode = GPIO::mode_t::output;
	GPIO::output_type_t PB6_output_type = GPIO::output_type_t::output_type_push_pull;
	GPIO::output_speed_t PB6_output_speed = GPIO::output_speed_t::output_speed_low;
	GPIO::pull_t PB6_pull = GPIO::pull_t::pull_none;

	GPIO::pin(PB6_port
		, PB6_pin
		, PB6_mode
		, PB6_output_type
		, PB6_output_speed
		, PB6_pull
	);



	xTaskCreate(LED_toggle_task, "LED toggle", 500, NULL, 1, NULL);

	vTaskStartScheduler();

	while (1);
	return 0;
}

/* EOF */
