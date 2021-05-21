#include "driver_USART.h"

/*! FreeRTOS includes.
 */
#include "FreeRTOS.h"

/* ============================================================================================================= */
/* USART Configuration Functions                                                                                 */
/* ============================================================================================================= */
/*! Gets the default configuration for a USART channel.
 *
 */
void USART_get_default_config(USART_config_t * const config)
{
	config->parity            = USART_parity_none;
	config->num_stop_bits     = USART_stop_bits_1;
	config->word_length       = USART_word_length_8;
	config->oversampling_rate = USART_ovrsmpl_rate_16;
	config->baud_rate         = 9600;
}


/*! Initializes a USART channel.
 *
 * @note  The oversampling rate must be set before the baud rate as the function configuring the baud rate reads
 *        the CR1 register to gather what oversampling rate has been chosen to compute the USARTDIV value.
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
	USART_set_oversampling_rate(USARTx, config->oversampling_rate);
	USART_set_baud_rate(USARTx, config->baud_rate);

	USARTx->CR1 |= 0x1UL << 3; //enable TX

	USARTx->CR1 |= 0x1UL; //!# Enable the USART channel
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
			break;
		case USART_stop_bits_1:
			/* STOP[1:0] = 0b00 */
			USARTx->CR2 &= ~(0x3UL << 12);
			break;
		case USART_stop_bits_1_5:
			/* STOP[1:0] = 0b11 */
			USARTx->CR2 |= 0x3UL << 12;
			break;
		case USART_stop_bits_2:
			/* STOP[1:0] = 0b10 */
			USARTx->CR2 = (USARTx->CR2 & ~(0x3UL << 12)) | (0x1UL << 13);
			break;
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
			break;
		case USART_word_length_8:
			/* M[1:0] = 0b00 */
			USARTx->CR1 &= ~(0x1UL << 28); //!# M[1] = 0b0
			USARTx->CR1 &= ~(0x1UL << 12); //!# M[0] = 0b0
			break;
		case USART_word_length_9:
			/* M[1:0] = 0b01 */
			USARTx->CR1 &= ~(0x1UL << 28); //!# M[1] = 0b0
			USARTx->CR1 |=   0x1UL << 12;  //!# M[0] = 0b1
			break;
		default:
			WTF;
			break;
	}
}

/*! Sets the oversampling rate of the USART channel.
 *
 */
void USART_set_oversampling_rate(USART_TypeDef * const USARTx
	, USART_ovrsmpl_rate_t const oversampling_rate
) {
	configASSERT(USARTx != NULL);
	configASSERT((oversampling_rate == USART_ovrsmpl_rate_8) || (oversampling_rate == USART_ovrsmpl_rate_16));
	configASSERT(!(USARTx->CR1 & 0x1UL)); //!# Oversampling rate can only be changed if USART is disabled

	switch (oversampling_rate) {
		case USART_ovrsmpl_rate_8:
			USARTx->CR1 |=   0x1UL << 15;  //!# OVER8 = 0b1
			break;
		case USART_ovrsmpl_rate_16:
			USARTx->CR1 &= ~(0x1UL << 15); //!# OVER8 = 0b0
			break;
		default:
			WTF;
			break;
	}
}

/*! Sets the baud rate of the USART channel.
 *
 * @brief The desired baud rate is computed as follows:
 *        - When oversampling by 16, baud rate = fCK / USARTDIV         thus USARTDIV = fCK / baud rate
 *        - When oversampling by 8,  baud rate = (2 * fCK) / USARTDIV   thus USARTDIV = (2 * fCK) / baud rate
 *
 *        Note: The division of fCK or (2 * fCK) is an integer division operation and floats should not be used.
 *
 *        Where fCK is the frequency of the clock driving the USART channel (APB2 clock for USART 1/6 and APB1
 *        clock for USART 2/3/4/5/7/8) and USARTDIV is an unsigned fixed point number that is coded on the
 *        USART_BRR register. The coding for USARTDIV is as follows:
 *        - When oversampling by 16
 *             USART_BRR = USARTDIV
 *        - When oversampling by 8
 *             USART_BRR[2:0]  = USARTDIV[3:0] shifted 1 bit to the right
 *             USART_BRR[3]    = must be kept clear
 *             USART_BRR[15:4] = USARTDIV[15:4]
 */
void USART_set_baud_rate(USART_TypeDef * const USARTx
	, uint32_t const baud_rate
) {
	configASSERT(USARTx != NULL);
	configASSERT(!(USARTx->CR1 & 0x1UL)); //!# BRR can only be changed if USART is disabled

	uint32_t USARTDIV = 0, fCK = 0, temp = 0;

	/* Determine which clock is driving the USART channel */
	if ((USARTx == USART1) || (USARTx == USART6)) {
		fCK = SystemAPB2Clock;
	} else if (    (USARTx == USART2)
				|| (USARTx == USART3)
				|| (USARTx == UART4 )
				|| (USARTx == UART5 )
				|| (USARTx == UART7 )
				|| (USARTx == UART8 )
	) {
		fCK = SystemAPB1Clock;
	} else {
		WTF;
	}

	/* Translate the desired baud to a BRR register compatible USARTDIV value */
	if (USARTx->CR1 & (0x1UL << 15)) {
		configASSERT(baud_rate * 8 <= fCK);      //!# Receiver can't sample at freq > clk clocking USART channel

		/* Oversampling by 8 */
		USARTDIV = (2 * fCK) / baud_rate;
		temp     = (USARTDIV & 0xFUL) >> 1;      //!# BRR[2:0] is USARTDIV[3:0] shifted 1 bit to the right
		USARTDIV = (USARTDIV & ~(0xFUL)) | temp; //!# Concatenate USARTDIV[15:4] and temp (USARTDIV[3:1])
	} else {
		configASSERT(baud_rate * 16 <= fCK);     //!# Receiver can't sample at freq > clk clocking USART channel

		/* Oversampling by 16 */
		USARTDIV = fCK / baud_rate;
	}

	USARTx->BRR = USARTDIV & 0xFFFFUL;
}

/* ============================================================================================================= */
/* USART Transmission Functions                                                                                  */
/* ============================================================================================================= */
/*! Sends a frame of data over the TX line of the USART channel in a blocking manner.
 *
 * @note  We can safely ignore word length for the write into the transmit data register.
 */
void USART_send_frame_blocking(USART_TypeDef * const USARTx
	, uint32_t const data
) {
	configASSERT(USARTx != NULL);

	while (!(USARTx->ISR & (0x1UL << 7))); //!# Wait while transmit data register empty is false

	USARTx->TDR = data;
}

/*! Sends a frame of data over the TX line of the USART channel in a non-blocking manner.
 *
 * @note  We can safely ignore word length for the write into the transmit data register.
 */
void USART_send_frame_nonblocking(USART_TypeDef * const USARTx
	, uint32_t const data
) {
	configASSERT(USARTx != NULL);

	USARTx->TDR = data;
}

/*! Receives a frame of data from the RX line of the USART channel in a blocking manner.
 *
 * @note  We can safely ignore word length for the read from the receive data register.
 */
uint32_t USART_receive_frame_blocking(USART_TypeDef * const USARTx) {
	configASSERT(USARTx != NULL);

	while (!(USARTx->ISR & (0x1UL << 5))); //!# Wait while read data register not empty is false

	return USARTx->RDR;
}

/*! Receives a frame of data from the RX line of the USART channel in a non-blocking manner.
 *
 * @note  We can safely ignore word length for the read from the receive data register.
 */
uint32_t USART_receive_frame_nonblocking(USART_TypeDef * const USARTx) {
	configASSERT(USARTx != NULL);

	return USARTx->RDR;
}

/* EOF */
