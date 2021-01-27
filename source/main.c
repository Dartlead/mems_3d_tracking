//!# Green user LED is connected to STM32 I/O PB0 (SB120 ON and SB119 OFF) or PA5 (SB119 ON and SB120 OFF)
//!#     corresponding to the ST Zio D13
//!# Blue user LED is connected to PB7
//!# Red user LED is connected to PB14
//!# These user LEDs are on when the I/O is high, and are off when the I/O is low

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
	RCC->AHB1ENR |= 0x1UL << 1UL;    //!# Enable clock to GPIO port B
	GPIOB->MODER |= (0x1UL << 14UL); //!# Set PB7 to general purpose output mode

	toggle_LED();
	return 0;
}

/* EOF */
