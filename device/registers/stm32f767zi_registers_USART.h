#ifndef STM32F767ZI_REGISTERS_USART_H
#define STM32F767ZI_REGISTERS_USART_H

#include "stm32f767zi.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! Start of section using anonymous unions.
 */
#if   defined (__CC_ARM)
	#pragma push
	#pragma anon_unions
#elif defined (__ICCARM__)
	#pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wc11-extensions"
	#pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
	//!# Anonymous unions are enabled by default
#elif defined (__TMS470__)
	//!# Anonymous unions are enabled by default
#elif defined (__TASKING__)
	#pragma warning 586
#elif defined (__CSMC__)
	//!# Anonymous unions are enabled by default
#else
	#warning Not supported compiler type
#endif

/*! UASRT register offsets.
 */
typedef struct
{
	__IO uint32_t CR1;  //!# USART control register 1                | offset: 0x00
	__IO uint32_t CR2;  //!# USART control register 2                | offset: 0x04
	__IO uint32_t CR3;  //!# USART control register 3                | offset: 0x08
	__IO uint32_t BRR;  //!# USART baud rate register                | offset: 0x0C
	__IO uint32_t GTPR; //!# USART guard time and prescaler register | offset: 0x10
	__IO uint32_t RTOR; //!# USART receiver timeout register         | offset: 0x14
	__O  uint32_t RQR;  //!# USART request register                  | offset: 0x18
	__I  uint32_t ISR;  //!# USART interrupt and status register     | offset: 0x1C
	__IO uint32_t ICR;  //!# USART interrupt flag clear register     | offset: 0x20
	__I  uint32_t RDR;  //!# USART receive data register             | offset: 0x24
	__IO uint32_t TDR;  //!# USART transmit data register            | offset: 0x28
} USART_TypeDef;

/*! USART channel address bases.
 */
#define USART1_BASE 0x40011000
#define USART2_BASE 0x40004400
#define USART3_BASE 0x40004800
#define UART4_BASE  0x40004C00
#define UART5_BASE  0x40005000
#define USART6_BASE 0x40011400
#define UART7_BASE  0x40007800
#define UART8_BASE  0x40007C00

/*! USART peripheral declarations.
 */
#define USART1 ((USART_TypeDef *) USART1_BASE)
#define USART2 ((USART_TypeDef *) USART2_BASE)
#define USART3 ((USART_TypeDef *) USART3_BASE)
#define UART4  ((USART_TypeDef *) UART4_BASE )
#define UART5  ((USART_TypeDef *) UART5_BASE )
#define USART6 ((USART_TypeDef *) USART6_BASE)
#define UART7  ((USART_TypeDef *) UART7_BASE )
#define UART8  ((USART_TypeDef *) UART8_BASE )

/*! End of section using anonymous unions.
 */
#if   defined (__CC_ARM)
	#pragma pop
#elif defined (__ICCARM__)
	//!# Leave anonymous unions enabled
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
	#pragma clang diagnostic pop
#elif defined (__GNUC__)
	//!# Anonymous unions are enabled by default
#elif defined (__TMS470__)
	//!# Anonymous unions are enabled by default
#elif defined (__TASKING__)
	#pragma warning restore
#elif defined (__CSMC__)
	//!# Anonymous unions are enabled by default
#else
	#warning Not supported compiler type
#endif

#ifdef __cplusplus
}
#endif

#endif /* STM32F767ZI_REGISTERS_USART_H */

/* EOF */
