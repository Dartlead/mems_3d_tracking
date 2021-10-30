#include "stm32f767zi.h"

/*! FreeRTOS includes.
 */
#include "FreeRTOS.h"
#include "task.h"

/*! STM32F767ZI includes.
 */
//#include "onboard_leds.h"
#include "driver_GPIO.h"

static void __attribute__((section(".text.fast_text"))) LED_toggle_task(void * parameter) {
	TickType_t const delay_200ms    = pdMS_TO_TICKS(200UL);
	TickType_t       last_wake_time = xTaskGetTickCount();

	GPIO::pin PB0(GPIO::port::B
		, (uint8_t)0
		, GPIO::mode::output
		, GPIO::output_type::push_pull
		, GPIO::output_speed::low
		, GPIO::pull::none
	);

	while (1) {
		vTaskDelayUntil(&last_wake_time, delay_200ms);

		//GPIOB->ODR ^= 0x1UL << 0;
		//int foo;
		//foo++;
		PB0.toggle();
	}
}

int main(void)
{
	/* Configure the green LED (PB0) */
	//RCC->AHB1ENR |= 0x1UL << 1;
	//GPIOB->MODER = (GPIOB->MODER & ~(0x3UL << (0 * 2))) | (0x1UL << (0 * 2));
	//GPIOB->OTYPER &= ~(0x1UL << 0);
	//GPIOB->OSPEEDR &= ~(0x3UL << 0);
	//GPIOB->PUPDR &= ~(0x3UL << 0);
	//GPIOB->ODR ^= 0x1UL << 0;

	//GPIO::pin PB6(GPIO::port::B
	//	, (uint8_t)6
	//	, GPIO::mode::output
	//	, GPIO::output_type::push_pull
	//	, GPIO::output_speed::low
	//	, GPIO::pull::none
	//);
	//PB6.write(1);

	xTaskCreate(LED_toggle_task, "LED toggle", 500, NULL, 1, NULL);

	vTaskStartScheduler();

	while (1);
	return 0;
}

/* EOF */
