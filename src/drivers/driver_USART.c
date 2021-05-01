#include "driver_USART.h"

/*! FreeRTOS includes.
 */
#include "FreeRTOS.h"

/* ============================================================================================================= */
/* USART Configuration Functions                                                                                 */
/* ============================================================================================================= */
/*! Initializes a USART channel.
 *
 */
void USART_init(USART_TypeDef * const USARTx
	, USART_config_t const * const config
) {
	/* Enable the peripheral clock to the USART channel */
	if (USARTx == USART1) {
		RCC->APB2ENR |= 0x1UL << 4;
	} else if (USARTx == USART2) {
		RCC->APB1ENR |= 0x1UL << 17;
	} else if (USARTx == USART3) {
		RCC->APB1ENR |= 0x1UL << 18;
	} else if (USARTx == UART4) {
		RCC->APB1ENR |= 0x1UL << 19;
	} else if (USARTx == UART5) {
		RCC->APB1ENR |= 0x1UL << 20;
	} else if (USARTx == USART6) {
		RCC->APB2ENR |= 0x1UL << 5;
	} else if (USARTx == UART7) {
		RCC->APB1ENR |= 0x1UL << 30;
	} else if (USARTx == UART8) {
		RCC->APB1ENR |= 0x1UL << 31;
	} else {
		WTF;
	}

	USART_set_parity(USARTx, config->parity);
	USART_set_stop_bits(USARTx, config->num_stop_bits);
	USART_set_word_length(USARTx, config->word_length);
}

/*! sets the parity control of the USART channel.
 *
 */
void USART_set_parity(USART_TypeDef * const USARTx
	, USART_parity_t const parity
) {
	configASSERT(USARTx != NULL);
	configASSERT((parity >= USART_parity_none) && (parity <= USART_parity_odd));
	configASSERT(!(USARTx->CR1 & 0x1UL)); //!# Parity can only be changed if USART is disabled

	switch (parity) {
		case USART_parity_none:
			USARTx->CR1 &= ~(0x1UL << 10);
			break;
		case USART_parity_even:
			USARTx->CR1 |=   0x1UL << 10;
			USARTx->CR1 &= ~(0x1UL << 9);
			break;
		case USART_parity_odd:
			USARTx->CR1 |= 0x1UL << 10;
			USARTx->CR1 |= 0x1UL << 9;
			break;
		default:
			WTF;
			break;
	}
}

/*! Sets the number of stop bits of the USART channel.
 *
 */
void USART_set_stop_bits(USART_TypeDef * const USARTx
	, USART_stop_bits_t const num_stop_bits
) {
	configASSERT(USARTx != NULL);
	configASSERT((num_stop_bits >= USART_stop_bits_0_5) && (num_stop_bits <= USART_stop_bits_2));
	configASSERT(!(USARTx->CR1 & 0x1UL)); //!# Stop bit count can only be changed if USART is disabled

	switch (num_stop_bits) {
		case USART_stop_bits_0_5:
			USARTx->CR2 = (USARTx->CR2 & ~(0x3UL << 12)) | (0x1UL << 12);
		case USART_stop_bits_1:
			USARTx->CR2 &= ~(0x3UL << 12);
		case USART_stop_bits_1_5:
			USARTx->CR2 |= 0x3UL << 12;
		case USART_stop_bits_2:
			USARTx->CR2 = (USARTx->CR2 & ~(0x3UL << 12)) | (0x1UL << 13);
		default:
			WTF;
			break;
	}
}

/*! Sets the word length of the USART channel.
 *
 */
void USART_set_word_length(USART_TypeDef * const USARTx
	, USART_word_length_t const word_length
) {
	configASSERT(USARTx != NULL);
	configASSERT((word_length >= USART_word_length_7) && (word_length <= USART_word_length_9));
	configASSERT(!(USARTx->CR1 & 0x1UL)); //!# Word length can only be changed if USART is disabled

	switch (word_length) {
		case USART_word_length_7:
			/* M[1:0] = 0b10 */
			USARTx->CR1 |=   0x1UL << 28;  //!# M[1] = 0b1
			USARTx->CR1 &= ~(0x1UL << 12); //!# M[0] = 0b0
		case USART_word_length_8:
			/* M[1:0] = 0b00 */
			USARTx->CR1 &= ~(0x1UL << 28); //!# M[1] = 0b0
			USARTx->CR1 &= ~(0x1UL << 12); //!# M[0] = 0b0
		case USART_word_length_9:
			/* M[1:0] = 0b01 */
			USARTx->CR1 &= ~(0x1UL << 28); //!# M[1] = 0b0
			USARTx->CR1 |=   0x1UL << 12;  //!# M[0] = 0b1
		default:
			WTF;
			break;
	}
}

/* EOF */
