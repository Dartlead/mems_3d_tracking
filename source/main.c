#include "stm32f767zi.h"

/*! FreeRTOS includes.
 */
#include "FreeRTOS.h"
#include "task.h"

/*! STM32F767ZI includes.
 */
#include "driver_GPIO.h"

static void __attribute__((section(".text.fast_text"))) LED_toggle_task(void * parameter) {
	TickType_t const delay_500ms    = pdMS_TO_TICKS(500UL);
	TickType_t       last_wake_time = xTaskGetTickCount();

	while (1) {
		vTaskDelayUntil(&last_wake_time, delay_500ms);

		GPIOB->ODR ^= (0x1UL << 7);
	}
}

int main(void)
{
	/* Blue user LED is connected to PB7 */
	RCC->AHB1ENR |= 0x1UL <<  1UL; //!# Enable clock to GPIO port B
	GPIOB->MODER |= 0x1UL << 14UL; //!# Set PB7 to general purpose output mode

	xTaskCreate(LED_toggle_task, "LED toggle", 500, NULL, 1, NULL);

	vTaskStartScheduler();

	while (1);
	return 0;
}

/* EOF */
