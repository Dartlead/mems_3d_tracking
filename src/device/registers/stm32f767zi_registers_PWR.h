#ifndef STM32F767ZI_REGISTERS_PWR_H
#define STM32F767ZI_REGISTERS_PWR_H

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

/*! PWR register offsets.
 */
typedef struct
{
	__IO uint32_t CR1;  //!# PWR control register 1        | offset: 0x00
	__IO uint32_t CSR1; //!# PWR control/status register 1 | offset: 0x04
	__IO uint32_t CR2;  //!# PWR control register 2        | offset: 0x08
	__IO uint32_t CSR2; //!# PWR control/status register 2 | offset: 0x0C
} PWR_TypeDef;

/*! PWR address base.
 */
#define PWR_BASE 0x40007000UL

/*! PWR peripheral declaration.
 */
#define PWR ((PWR_TypeDef *) PWR_BASE)

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

#endif /* STM32F767ZI_REGISTERS_PWR_H */

/* EOF */
