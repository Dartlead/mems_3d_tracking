#include "dartlead_printf.h"
#include "driver_USART.h"
#include "driver_GPIO.h"
#include <stdbool.h>

/* ============================================================================================================= */
/* Pound Defines                                                                                                 */
/* ============================================================================================================= */
#define DARTLEAD_PRINTF_MAX_BUF_LEN 25UL

#define DARTLEAD_PRINTF_FLAG_UPPERCASE (1UL << 0)

/* ============================================================================================================= */
/* ASCII Conversion Functions                                                                                    */
/* ============================================================================================================= */
/*!
 *
 */
static void dartlead_itoa(int32_t val
	, uint32_t const base
	, uint32_t const flags
	, bool     const negative
	, char *         buf
) {
	uint32_t buf_idx = 0;
	char     digit   = (char)(val % base);

	/* Create the ASCII string in reverse order */
	while (val && (buf_idx < DARTLEAD_PRINTF_MAX_BUF_LEN)) {
		if (digit < 10) {
			buf[buf_idx++] = '0' + digit;
		} else {
			/* The -10 is to get how many 'places' over 10 the digit is */
			buf[buf_idx++] = ((flags & DARTLEAD_PRINTF_FLAG_UPPERCASE) ? 'A' : 'a') + digit - 10;
		}
		val /= base;
	}

	if ((flags & DARTLEAD_PRINTF_FLAG_HASH) && (base == 16) && (len < DARTLEAD_PRINTF_MAX_BUF_LEN)) {
		;
	} else {
		//!# Do nothing
	}

	/* */
	if (negative && (buf_idx < DARTLEAD_PRINTF_MAX_BUF_LEN)) {
		buf[buf_idx++] = '-';
	} else {
		//!# Do nothing
	}
}

/* ============================================================================================================= */
/* Public printf Functions                                                                                       */
/* ============================================================================================================= */
/*! Initializes the necessary hardware peripherals for printf functionality.
 *
 * @note  By default the USART3 interface (PD8 for TX and PD9 for RX with no hardware flow control) is connected to
 *        the ST-Link by virtue of SB5 and SB6 being present on the EVK board.
 */
void dartlead_printf_init(void) {
	USART_config_t USART3_config = {
		  .parity            = USART_parity_none
		, .num_stop_bits     = USART_stop_bits_1
		, .word_length       = USART_word_length_8
		, .oversampling_rate = USART_ovrsmpl_rate_16
		, .baud_rate         = 9600
	};
	GPIO_config_t PD8_9_config = {
		  .GPIO_mode         = GPIO_mode_alt_func_7
		, .GPIO_output_type  = GPIO_output_type_push_pull
		, .GPIO_output_speed = GPIO_output_speed_low
		, .GPIO_pull         = GPIO_pull_none
	};

	GPIO_init(GPIOD, 8, &PD8_9_config);
	GPIO_init(GPIOD, 9, &PD8_9_config);
	USART_init(USART3, &USART3_config);
}

/*!
 *
 */
void dartlead_printf(char const * format
	, ...
) {
	va_list args;
	va_start(args, format);

	while (*format) {
		if (*format == '%') {
			format++;

			/* Evaluate format tags */
			switch (*format) {
				case 'd':
				case 'i':
					;
					break;
			}
		} else {
			USART_send_frame_blocking(USART3, *format++);
			break;
		}






		switch (*format) {
			case '%':
				++format;

				switch
				break;
			default:
				USART_send_frame_blocking(USART3, *format);
				format++;
				break;
		}
	}

	va_end(args);
}

/* EOF */
