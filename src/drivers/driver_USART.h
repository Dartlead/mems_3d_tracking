#ifndef DRIVER_USART_H
#define DRIVER_USART_H

#include "stm32f767zi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================================= */
/* USART Configuration Enum Options                                                                              */
/* ============================================================================================================= */
/*! Enumeration of USART parity options.
 */
typedef enum USART_parity {
	  USART_parity_none = 0
	, USART_parity_even = 1
	, USART_parity_odd  = 2
} USART_parity_t;

/*! Enumeration of USART stop bit numbers.
 */
typedef enum USART_stop_bits {
	  USART_stop_bits_0_5 = 0
	, USART_stop_bits_1   = 1
	, USART_stop_bits_1_5 = 2
	, USART_stop_bits_2   = 3
} USART_stop_bits_t;

/*! Enumeration of USART word length options.
 */
typedef enum USART_word_length {
	  USART_word_length_7 = 0
	, USART_word_length_8 = 1
	, USART_word_length_9 = 2
} USART_word_length_t;

/*! Enumeration of USART oversampling rate options.
 *
 */
typedef enum USART_ovrsmpl_rate {
	  USART_ovrsmpl_rate_8  = 0
	, USART_ovrsmpl_rate_16 = 1
} USART_ovrsmpl_rate_t;

/* ============================================================================================================= */
/* USART Configuration Struct                                                                                    */
/* ============================================================================================================= */
/*! Structure containing USART channel configuration options.
 */
typedef struct USART_config {
	USART_parity_t       parity;
	USART_stop_bits_t    num_stop_bits;
	USART_word_length_t  word_length;
	USART_ovrsmpl_rate_t oversampling_rate;
	uint32_t             baud_rate;
} USART_config_t;

/* ============================================================================================================= */
/* USART Configuration Functions                                                                                 */
/* ============================================================================================================= */
/*! Gets the default configuration for a USART channel.
 *
 * @brief The default USART configuration is no parity bit, 1 stop bit, 8 bit word length, oversampling by 16, and
 *        a 9600 baud rate.
 */
void USART_get_default_config(USART_config_t * const config);

/*! Initializes a USART channel.
 *
 */
void USART_init(USART_TypeDef * const USARTx
	, USART_config_t const * const config
);

/*! sets the parity control of the USART channel.
 *
 */
void USART_set_parity(USART_TypeDef * const USARTx
	, USART_parity_t const parity
);

/*! Sets the number of stop bits of the USART channel.
 *
 */
void USART_set_stop_bits(USART_TypeDef * const USARTx
	, USART_stop_bits_t const num_stop_bits
);

/*! Sets the word length of the USART channel.
 *
 */
void USART_set_word_length(USART_TypeDef * const USARTx
	, USART_word_length_t const word_length
);

/*! Sets the oversampling rate of the USART channel.
 *
 */
void USART_set_oversampling_rate(USART_TypeDef * const USARTx
	, USART_ovrsmpl_rate_t const oversampling_rate
);

/*! Sets the baud rate of the USART channel.
 *
 */
void USART_set_baud_rate(USART_TypeDef * const USARTx
	, uint32_t const baud_rate
);

/* ============================================================================================================= */
/* USART Transmission/Reception Functions                                                                        */
/* ============================================================================================================= */
/*! Sends a frame of data over the TX line of the USART channel in a blocking manner.
 *
 */
void USART_send_frame_blocking(USART_TypeDef * const USARTx
	, uint32_t const data
);

/*! Sends a frame of data over the TX line of the USART channel in a non-blocking manner.
 *
 */
void USART_send_frame_nonblocking(USART_TypeDef * const USARTx
	, uint32_t const data
);

/*! Receives a frame of data from the RX line of the USART channel in a blocking manner.
 *
 */
uint32_t USART_receive_frame_blocking(USART_TypeDef * const USARTx);

/*! Receives a frame of data from the RX line of the USART channel in a non-blocking manner.
 *
 */
uint32_t USART_receive_frame_nonblocking(USART_TypeDef * const USARTx);

#ifdef __cplusplus
}
#endif

#endif  /* DRIVER_USART_H */

/* EOF */
