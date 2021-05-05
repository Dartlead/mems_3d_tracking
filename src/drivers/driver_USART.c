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

	USARTx->CR1 |= 0x1UL; //!# Enable the USART channel


//1. Program the M bits in USART_CR1 to define the word length. DONE
//2. Select the desired baud rate using the USART_BRR register.
//3. Program the number of stop bits in USART_CR2. DONE
//4. Enable the USART by writing the UE bit in USART_CR1 register to 1.
//5. Select DMA enable (DMAT) in USART_CR3 if multibuffer communication is to take
//place. Configure the DMA register as explained in multibuffer communication.
//6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
//7. Write the data to send in the USART_TDR register (this clears the TXE bit). Repeat this for each data to be
//		transmitted in case of single buffer.
//8. After writing the last data into the USART_TDR register, wait until TC=1. This indicates
//	that the transmission of the last frame is complete. This is required for instance when
//	the USART is disabled or enters the Halt mode to avoid corrupting the last
//	transmission.	
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
			USARTx->CR1 &= ~(0x1UL << 10); //!# PCE = 0b0
			break;
		case USART_parity_even:
			USARTx->CR1 |=   0x1UL << 10;  //!# PCE = 0b1
			USARTx->CR1 &= ~(0x1UL << 9);  //!# PS  = 0b0
			break;
		case USART_parity_odd:
			USARTx->CR1 |= 0x1UL << 10;    //!# PCE = 0b1
			USARTx->CR1 |= 0x1UL << 9;     //!# PS  = 0b1
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
			/* STOP[1:0] = 0b01 */
			USARTx->CR2 = (USARTx->CR2 & ~(0x3UL << 12)) | (0x1UL << 12);
		case USART_stop_bits_1:
			/* STOP[1:0] = 0b00 */
			USARTx->CR2 &= ~(0x3UL << 12);
		case USART_stop_bits_1_5:
			/* STOP[1:0] = 0b11 */
			USARTx->CR2 |= 0x3UL << 12;
		case USART_stop_bits_2:
			/* STOP[1:0] = 0b10 */
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
