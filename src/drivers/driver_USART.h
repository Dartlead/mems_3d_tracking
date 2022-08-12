#ifndef DRIVER_USART_H
#define DRIVER_USART_H

#include <cstdint>
//#include "driver_GPIO.h"

namespace USART {
	/**
	 * @enum Enumeration of all USART peripherals on the chip.
	 */
	enum class peripheral : uint8_t {
		  USART_1 /**< USART1 */
		, USART_2 /**< USART2 */
		, USART_3 /**< USART3 */
		, UART_4  /**< UART4  */
		, UART_5  /**< UART5  */
		, USART_6 /**< USART6 */
		, UART_7  /**< UART7  */
		, UART_8  /**< UART8  */
	};

	/**
	 * @enum Enumeration of USART parity options.
	 */
	enum class parity : uint8_t {
		  none /**< No parity bit */
		, even /**< Even parity   */
		, odd  /**< Odd parity    */
	};

	/**
	 * @enum Enumeration of USART stop bit options.
	 */
	enum class stop_bit : uint8_t {
		  zero_five_bits /**< 0.5 stop bits */
		, one_bit        /**< 1 stop bit    */
		, one_five_bits  /**< 1.5 stop bits */
		, two_bits       /**< 2 stop bits   */
	};

	/**
	 * @enum Enumeration of USART word length options.
	 */
	enum class word_len : uint8_t {
		  seven_bits /**< One USART data word is 7 bits long */
		, eight_bits /**< One USART data word is 8 bits long */
		, nine_bits  /**< One USART data word is 9 bits long */
	};

	/**
	 * @enum Enumeration of USART oversampling rate options.
	 */
	enum class oversample_rate : uint8_t {
		  eight_times   /**< Oversample by x8  */
		, sixteen_times /**< Oversample by x16 */
	};

	class controller {
	private:
		peripheral      m_peripheral;      /**< f */
		//GPIO::pin       m_TX_pin;          /**< f */
		//GPIO::pin       m_RX_pin;          /**< f */
		parity          m_parity;          /**< Parity selection for the USART controller    */
		stop_bit        m_stop_bit;        /**< Number of stop bits for the USART controller */
		word_len        m_word_len;        /**< Data word length of the USART controller     */
		oversample_rate m_oversample_rate; /**< Oversampling rate of the USART controller    */
		uint32_t        m_baud_rate;       /**< Baud rate of the USART controller            */

	public:
		controller(peripheral const periph_num);
	};
}

#endif /* DRIVER_USART_H */

/* EOF */
