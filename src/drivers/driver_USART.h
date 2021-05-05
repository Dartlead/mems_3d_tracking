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

/* ============================================================================================================= */
/* USART Configuration Struct                                                                                    */
/* ============================================================================================================= */
/*! Structure containing USART channel configuration options.
 */
typedef struct USART_config {
	USART_parity_t      parity;
	USART_stop_bits_t   num_stop_bits;
	USART_word_length_t word_length;
	uint32_t            baud_rate;
} USART_config_t;

/* ============================================================================================================= */
/* USART Configuration Functions                                                                                 */
/* ============================================================================================================= */
/*! Gets the default configuration for a USART channel.
 *
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

/*! Sets the baud rate of the USART channel.
 *
 */
void USART_set_baud_rate(USART_TypeDef * const USARTx
	, uint32_t const baud_rate
);

/* ============================================================================================================= */
/* USART Transmission Functions                                                                                  */
/* ============================================================================================================= */

#ifdef __cplusplus
}
#endif

#endif  /* DRIVER_USART_H */

/* EOF */
