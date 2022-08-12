#include "driver_USART.h"
#include "stm32f767zi.h"
#include "dartlead_assert.h"

USART::controller::controller(USART::peripheral const periph_num) {
	switch (periph_num) {
		case USART::peripheral::USART_1:
			RCC->APB2ENR |= 0x1UL << 4;
			m_peripheral = USART::peripheral::USART_1;
			break;
		case USART::peripheral::USART_2:
			RCC->APB1ENR |= 0x1UL << 17;
			m_peripheral = USART::peripheral::USART_2;
			break;
		case USART::peripheral::USART_3:
			RCC->APB1ENR |= 0x1UL << 18;
			m_peripheral = USART::peripheral::USART_3;
			break;
		case USART::peripheral::UART_4:
			RCC->APB1ENR |= 0x1UL << 19;
			m_peripheral = USART::peripheral::UART_4;
			break;
		case USART::peripheral::UART_5:
			RCC->APB1ENR |= 0x1UL << 20;
			m_peripheral = USART::peripheral::UART_5;
			break;
		case USART::peripheral::USART_6:
			RCC->APB2ENR |= 0x1UL << 5;
			m_peripheral = USART::peripheral::USART_6;
			break;
		case USART::peripheral::UART_7:
			m_peripheral = USART::peripheral::UART_7;
			RCC->APB1ENR |= 0x1UL << 30;
			break;
		case USART::peripheral::UART_8:
			RCC->APB1ENR |= 0x1UL << 31;
			m_peripheral = USART::peripheral::UART_8;
			break;
		default:
			dartlead_WTF;
			break;
	}
}

/* EOF */
