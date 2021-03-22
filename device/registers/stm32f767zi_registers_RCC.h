#ifndef STM32F767ZI_REGISTERS_RCC_H
#define STM32F767ZI_REGISTERS_RCC_H

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

/*! RCC register offsets.
 */
typedef struct
{
	__IO uint32_t CR;           //!# RCC clock control register                                  | offset: 0x00
	__IO uint32_t PLLCFGR;      //!# RCC PLL configuration register                              | offset: 0x04
	__IO uint32_t CFGR;         //!# RCC clock configuration register                            | offset: 0x08
	__IO uint32_t CIR;          //!# RCC clock interrupt register                                | offset: 0x0C
	__IO uint32_t AHB1RSTR;     //!# RCC AHB1 peripheral reset register                          | offset: 0x10
	__IO uint32_t AHB2RSTR;     //!# RCC AHB2 peripheral reset register                          | offset: 0x14
	__IO uint32_t AHB3RSTR;     //!# RCC AHB3 peripheral reset register                          | offset: 0x18
		  uint32_t RESERVED0;    //!# Reserved                                                    | offset: 0x1C
	__IO uint32_t APB1RSTR;     //!# RCC APB1 peripheral reset register                          | offset: 0x20
	__IO uint32_t APB2RSTR;     //!# RCC APB2 peripheral reset register                          | offset: 0x24
		  uint32_t RESERVED1[2]; //!# Reserved                                                    | offset: 0x28-0x2C
	__IO uint32_t AHB1ENR;      //!# RCC AHB1 peripheral clock register                          | offset: 0x30
	__IO uint32_t AHB2ENR;      //!# RCC AHB2 peripheral clock register                          | offset: 0x34
	__IO uint32_t AHB3ENR;      //!# RCC AHB3 peripheral clock register                          | offset: 0x38
		  uint32_t RESERVED2;    //!# Reserved                                                    | offset: 0x3C
	__IO uint32_t APB1ENR;      //!# RCC APB1 peripheral clock enable register                   | offset: 0x40
	__IO uint32_t APB2ENR;      //!# RCC APB2 peripheral clock enable register                   | offset: 0x44
		  uint32_t RESERVED3[2]; //!# Reserved                                                    | offset: 0x48-0x4C
	__IO uint32_t AHB1LPENR;    //!# RCC AHB1 peripheral clock enable in low power mode register | offset: 0x50
	__IO uint32_t AHB2LPENR;    //!# RCC AHB2 peripheral clock enable in low power mode register | offset: 0x54
	__IO uint32_t AHB3LPENR;    //!# RCC AHB3 peripheral clock enable in low power mode register | offset: 0x58
		  uint32_t RESERVED4;    //!# Reserved                                                    | offset: 0x5C
	__IO uint32_t APB1LPENR;    //!# RCC APB1 peripheral clock enable in low power mode register | offset: 0x60
	__IO uint32_t APB2LPENR;    //!# RCC APB2 peripheral clock enable in low power mode register | offset: 0x64
		  uint32_t RESERVED5[2]; //!# Reserved                                                    | offset: 0x68-0x6C
	__IO uint32_t BDCR;         //!# RCC Backup domain control register                          | offset: 0x70
	__IO uint32_t CSR;          //!# RCC clock control & status register                         | offset: 0x74
		  uint32_t RESERVED6[2]; //!# Reserved                                                    | offset: 0x78-0x7C
	__IO uint32_t SSCGR;        //!# RCC spread spectrum clock generation register               | offset: 0x80
	__IO uint32_t PLLI2SCFGR;   //!# RCC PLLI2S configuration register                           | offset: 0x84
	__IO uint32_t PLLSAICFGR;   //!# RCC PLLSAI configuration register                           | offset: 0x88
	__IO uint32_t DCKCFGR1;     //!# RCC Dedicated Clocks configuration register 1               | offset: 0x8C
	__IO uint32_t DCKCFGR2;     //!# RCC Dedicated Clocks configuration register 2               | offset: 0x90
} RCC_TypeDef;

/*! RCC address base.
 */
#define RCC_BASE 0x40023800UL

/*! RCC peripheral declaration.
 */
#define RCC ((RCC_TypeDef *) RCC_BASE)

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

#endif /* STM32F767ZI_REGISTERS_RCC_H */

/* EOF */
