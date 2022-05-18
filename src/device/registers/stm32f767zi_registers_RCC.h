#ifndef STM32F767ZI_REGISTERS_RCC_H
#define STM32F767ZI_REGISTERS_RCC_H

#include "stm32f767zi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Start of section using anonymous unions */
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
	// Anonymous unions are enabled by default
#elif defined (__TMS470__)
	// Anonymous unions are enabled by default
#elif defined (__TASKING__)
	#pragma warning 586
#elif defined (__CSMC__)
	// Anonymous unions are enabled by default
#else
	#warning Not supported compiler type
#endif

/**
 * @brief RCC register offsets.
 */
typedef struct
{
	__IO uint32_t CR;           /**< Clock control reg                        | offset: 0x00      */
	__IO uint32_t PLLCFGR;      /**< PLL configuration reg                    | offset: 0x04      */
	__IO uint32_t CFGR;         /**< Clock configuration reg                  | offset: 0x08      */
	__IO uint32_t CIR;          /**< Clock interrupt reg                      | offset: 0x0C      */
	__IO uint32_t AHB1RSTR;     /**< AHB1 periph reset reg                    | offset: 0x10      */
	__IO uint32_t AHB2RSTR;     /**< AHB2 periph reset reg                    | offset: 0x14      */
	__IO uint32_t AHB3RSTR;     /**< AHB3 periph reset reg                    | offset: 0x18      */
		 uint32_t RESERVED0;    /**< Reserved                                 | offset: 0x1C      */
	__IO uint32_t APB1RSTR;     /**< APB1 periph reset reg                    | offset: 0x20      */
	__IO uint32_t APB2RSTR;     /**< APB2 periph reset reg                    | offset: 0x24      */
		 uint32_t RESERVED1[2]; /**< Reserved                                 | offset: 0x28-0x2C */
	__IO uint32_t AHB1ENR;      /**< AHB1 periph clk reg                      | offset: 0x30      */
	__IO uint32_t AHB2ENR;      /**< AHB2 periph clk reg                      | offset: 0x34      */
	__IO uint32_t AHB3ENR;      /**< AHB3 periph clk reg                      | offset: 0x38      */
		 uint32_t RESERVED2;    /**< Reserved                                 | offset: 0x3C      */
	__IO uint32_t APB1ENR;      /**< APB1 periph clk enable reg               | offset: 0x40      */
	__IO uint32_t APB2ENR;      /**< APB2 periph clk enable reg               | offset: 0x44      */
		 uint32_t RESERVED3[2]; /**< Reserved                                 | offset: 0x48-0x4C */
	__IO uint32_t AHB1LPENR;    /**< AHB1 periph clk enable low pow mode reg  | offset: 0x50      */
	__IO uint32_t AHB2LPENR;    /**< AHB2 periph clk enable low pow mode reg  | offset: 0x54      */
	__IO uint32_t AHB3LPENR;    /**< AHB3 periph clk enable low pow mode reg  | offset: 0x58      */
		 uint32_t RESERVED4;    /**< Reserved                                 | offset: 0x5C      */
	__IO uint32_t APB1LPENR;    /**< APB1 periph clk enable low pow mode reg  | offset: 0x60      */
	__IO uint32_t APB2LPENR;    /**< APB2 periph clk enable low pow mode reg  | offset: 0x64      */
		 uint32_t RESERVED5[2]; /**< Reserved                                 | offset: 0x68-0x6C */
	__IO uint32_t BDCR;         /**< Backup domain control reg                | offset: 0x70      */
	__IO uint32_t CSR;          /**< Clock control & status reg               | offset: 0x74      */
		 uint32_t RESERVED6[2]; /**< Reserved                                 | offset: 0x78-0x7C */
	__IO uint32_t SSCGR;        /**< spread spectrum clock generation reg     | offset: 0x80      */
	__IO uint32_t PLLI2SCFGR;   /**< PLLI2S configuration reg                 | offset: 0x84      */
	__IO uint32_t PLLSAICFGR;   /**< PLLSAI configuration reg                 | offset: 0x88      */
	__IO uint32_t DCKCFGR1;     /**< Dedicated clocks configuration reg 1     | offset: 0x8C      */
	__IO uint32_t DCKCFGR2;     /**< Dedicated clocks configuration reg 2     | offset: 0x90      */
} RCC_TypeDef;

/* RCC address base */
#define RCC_BASE 0x40023800UL

/* RCC peripheral declaration */
#define RCC ((RCC_TypeDef *) RCC_BASE)

/* End of section using anonymous unions */
#if   defined (__CC_ARM)
	#pragma pop
#elif defined (__ICCARM__)
	// Leave anonymous unions enabled
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
	#pragma clang diagnostic pop
#elif defined (__GNUC__)
	// Anonymous unions are enabled by default
#elif defined (__TMS470__)
	// Anonymous unions are enabled by default
#elif defined (__TASKING__)
	#pragma warning restore
#elif defined (__CSMC__)
	// Anonymous unions are enabled by default
#else
	#warning Not supported compiler type
#endif

#ifdef __cplusplus
}
#endif

#endif /* STM32F767ZI_REGISTERS_RCC_H */

/* EOF */
