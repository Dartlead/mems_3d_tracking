#include "stm32f767zi.h"

void __attribute__((section(".text.fast_text"), optimize("O0"))) delay(void)
{
	uint32_t i = 0;
	while (i < 1000000) {
		i++;
	}
}

void __attribute__((section(".text.fast_text"))) toggle_LED(void)
{
	while (1) {
		GPIOB->ODR ^= (0x1UL << 7);
		delay();
	}
}

int main(void)
{
	/* Blue user LED is connected to PB7 */
	RCC->AHB1ENR |= 0x1UL <<  1UL; //!# Enable clock to GPIO port B
	GPIOB->MODER |= 0x1UL << 14UL; //!# Set PB7 to general purpose output mode

	toggle_LED();
	return 0;
}

/* EOF */
