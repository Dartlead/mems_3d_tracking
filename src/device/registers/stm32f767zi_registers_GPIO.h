#ifndef STM32F767ZI_REGISTERS_GPIO_H
#define STM32F767ZI_REGISTERS_GPIO_H

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
 * @brief GPIO register offsets.
 */
typedef struct
{
	__IO uint32_t MODER;   /**< GPIO port mode register                | offset: 0x00      */
	__IO uint32_t OTYPER;  /**< GPIO port output type register         | offset: 0x04      */
	__IO uint32_t OSPEEDR; /**< GPIO port output speed register        | offset: 0x08      */
	__IO uint32_t PUPDR;   /**< GPIO port pull-up/pull-down register   | offset: 0x0C      */
	__IO uint32_t IDR;     /**< GPIO port input data register          | offset: 0x10      */
	__IO uint32_t ODR;     /**< GPIO port output data register         | offset: 0x14      */
	__IO uint32_t BSRR;    /**< GPIO port bit set/reset register       | offset: 0x18      */
	__IO uint32_t LCKR;    /**< GPIO port configuration lock register  | offset: 0x1C      */
	__IO uint32_t AFR[2];  /**< GPIO port alternate function registers | offset: 0x20-0x24 */
} GPIO_TypeDef;

/* GPIO address bases */
#define GPIOA_BASE 0x40020000
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800
#define GPIOD_BASE 0x40020C00
#define GPIOE_BASE 0x40021000
#define GPIOF_BASE 0x40021400
#define GPIOG_BASE 0x40021800
#define GPIOH_BASE 0x40021C00
#define GPIOI_BASE 0x40022000
#define GPIOJ_BASE 0x40022400
#define GPIOK_BASE 0x40022800

/* GPIO peripheral declarations */
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOI ((GPIO_TypeDef *) GPIOI_BASE)
#define GPIOJ ((GPIO_TypeDef *) GPIOJ_BASE)
#define GPIOK ((GPIO_TypeDef *) GPIOK_BASE)

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

#endif /* STM32F767ZI_REGISTERS_GPIO_H */

/* EOF */
