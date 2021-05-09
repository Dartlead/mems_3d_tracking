#include "dartlead_printf.h"
#include "driver_USART.h"
#include "driver_GPIO.h"

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

/* EOF */
