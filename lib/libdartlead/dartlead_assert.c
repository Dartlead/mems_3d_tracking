#include "dartlead_assert.h"
#include "stm32f767zi.h"

/**
 * @details The red LED is connected to PB14. Thus PB14 needs to be configured as a barebones
 *          output pin and afterwards repeatedly blink the LED. This function is forcefully
 *          optimized at -O0 to prevent the optimizer from taking out the dumb for-loop.
 */
void __attribute__((optimize("O0"))) __dartlead_assert(void) {
	RCC->AHB1ENR   |=   0x1UL <<  1;  //Enable clock to GPIO port B
	GPIOB->MODER   |=   0x1UL << 28;  //Set PB14 to output mode
	GPIOB->OTYPER  &= ~(0x1UL << 14); //Set PB14 to push-pull
	GPIOB->OSPEEDR &= ~(0x3UL << 28); //Set PB14 to low-speed
	GPIOB->PUPDR   &= ~(0x3UL << 28); //Set PB14 to no pull

	uint32_t delay_tick = 0;

	while (1) {
		GPIOB->ODR ^= 0x1UL << 14; // Toggle the red LED

		delay_tick = 0;
		while (delay_tick++ < 10000000);
	}
}

/* EOF */
