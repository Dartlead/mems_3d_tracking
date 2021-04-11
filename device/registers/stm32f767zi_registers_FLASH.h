#ifndef STM32F767ZI_REGISTERS_FLASH_H
#define STM32F767ZI_REGISTERS_FLASH_H

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

/*! FLASH register offsets.
 */
typedef struct
{
	__IO uint32_t ACR;     //!# FLASH access control register | offset: 0x00
	__O  uint32_t KEYR;    //!# FLASH key register            | offset: 0x04
	__O  uint32_t OPTKEYR; //!# FLASH option key register     | offset: 0x08
	__IO uint32_t SR;      //!# FLASH status register         | offset: 0x0C
	__IO uint32_t CR;      //!# FLASH control register        | offset: 0x10
	__IO uint32_t OPTCR;   //!# FLASH option control register | offset: 0x14
	__IO uint32_t OPTCR1;  //!# FLASH option control register | offset: 0x018
} FLASH_typedef;

/*! FLASH address base.
 */
#define FLASH_BASE 0x40023C00UL

/*! FLASH peripheral declaration.
 */
#define FLASH ((FLASH_typedef *) FLASH_BASE)

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

#endif /* STM32F767ZI_REGISTERS_FLASH_H */

/* EOF */
