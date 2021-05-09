#ifndef DARTLEAD_PRINTF_H
#define DARTLEAD_PRINTF_H

#ifdef __cplusplus
extern "C" {
#endif

/*! Initializes the necessary hardware peripherals for printf functionality.
 *
 * @brief In intializes USART3 (by default connected to the ST-Link which commuicates with the host PC over USB) as
 *        the USART channel used for a serial communication with the following parameters:
 *
 *        Baud Rate:           9600
 *        Parity Control:      None
 *        Number of Stop Bits: 1
 *        Word Length:         8 bits
 */
void dartlead_printf_init(void);

#ifdef __cplusplus
}
#endif

#endif /* DARTLEAD_PRINTF_H */

/* EOF */
