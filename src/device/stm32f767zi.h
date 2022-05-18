#ifndef STM32F767ZI_H
#define STM32F767ZI_H

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/* Interrupt Number Definitions                                                                   */
/* ============================================================================================== */
/**
 * @enum Enumeration of all interrupt sources in the system.
 */
typedef enum IRQn
{
	/* Cortex-M7 processor exception numbers */
	  NonMaskableInt_IRQn     = -14 /**< Non-Maskable      */
	, HardFault_IRQn          = -13 /**< SV Hard Fault     */
	, MemoryManagement_IRQn   = -12 /**< Memory Management */
	, BusFault_IRQn           = -11 /**< Bus Fault         */
	, UsageFault_IRQn         = -10 /**< Usage Fault       */
	, SVCall_IRQn             = -5  /**< SV Call           */
	, DebugMonitor_IRQn       = -4  /**< Debug Monitor     */
	, PendSV_IRQn             = -2  /**< Pend SV           */
	, SysTick_IRQn            = -1  /**< System Tick       */

	/* stm32f76xxx device specific interrupt numbers */
	, WWDG_IRQn               = 0   /**< Window watchdog interrupt                             */
	, PVD_IRQn                = 1   /**< PVD through EXTI line detection interrupt             */
	, TAMP_STAMP_IRQn         = 2   /**< Tamper and TimeStamp interrupts through the EXTI line */
	, RTC_WKUP_IRQn           = 3   /**< RTC Wakeup interrupt through the EXTI line            */
	, FLASH_IRQn              = 4   /**< Flash global interrupt                                */
	, RCC_IRQn                = 5   /**< RCC global interrupt                                  */
	, EXTI0_IRQn              = 6   /**< EXTI Line0  interrupt                                 */
	, EXTI1_IRQn              = 7   /**< EXTI Line1  interrupt                                 */
	, EXTI2_IRQn              = 8   /**< EXTI Line2  interrupt                                 */
	, EXTI3_IRQn              = 9   /**< EXTI Line3  interrupt                                 */
	, EXTI4_IRQn              = 10  /**< EXTI Line4  interrupt                                 */
	, DMA1_Stream0_IRQn       = 11  /**< DMA1 Stream0 global interrupt                         */
	, DMA1_Stream1_IRQn       = 12  /**< DMA1 Stream1 global interrupt                         */
	, DMA1_Stream2_IRQn       = 13  /**< DMA1 Stream2 global interrupt                         */
	, DMA1_Stream3_IRQn       = 14  /**< DMA1 Stream3 global interrupt                         */
	, DMA1_Stream4_IRQn       = 15  /**< DMA1 Stream4 global interrupt                         */
	, DMA1_Stream5_IRQn       = 16  /**< DMA1 Stream5 global interrupt                         */
	, DMA1_Stream6_IRQn       = 17  /**< DMA1 Stream6 global interrupt                         */
	, ADC_IRQn                = 18  /**< ADC1, ADC2, and ADC3 global interrupts                */
	, CAN1_TX_IRQn            = 19  /**< CAN1 TX interrupts                                    */
	, CAN1_RX0_IRQn           = 20  /**< CAN1 RX0 interrupts                                   */
	, CAN1_RX1_IRQn           = 21  /**< CAN1 RX1 interrupts                                   */
	, CAN1_SCE_IRQn           = 22  /**< CAN1 SCE interrupt                                    */
	, EXTI9_5_IRQn            = 23  /**< EXTI Line[9:5] interrupts                             */
	, TIM1_BRK_TIM9_IRQn      = 24  /**< TIM1 break interrupt and TIM9 global interrupt        */
	, TIM1_UP_TIM10_IRQn      = 25  /**< TIM1 update interrupt and TIM10 global interrupt      */
	, TIM1_TRG_COM_TIM11_IRQn = 26  /**< TIM1 trigger/commutation and TIM11 global interrupt   */
	, TIM1_CC_IRQn            = 27  /**< TIM1 capture compare interrupt                        */
	, TIM2_IRQn               = 28  /**< TIM2 global interrupt                                 */
	, TIM3_IRQn               = 29  /**< TIM3 global interrupt                                 */
	, TIM4_IRQn               = 30  /**< TIM4 global interrupt                                 */
	, I2C1_EV_IRQn            = 31  /**< I2C1 event interrupt                                  */
	, I2C1_ER_IRQn            = 32  /**< I2C1 error interrupt                                  */
	, I2C2_EV_IRQn            = 33  /**< I2C2 event interrupt                                  */
	, I2C2_ER_IRQn            = 34  /**< I2C2 error interrupt                                  */
	, SPI1_IRQn               = 35  /**< SPI1 global interrupt                                 */
	, SPI2_IRQn               = 36  /**< SPI2 global interrupt                                 */
	, USART1_IRQn             = 37  /**< USART1 global interrupt                               */
	, USART2_IRQn             = 38  /**< USART2 global interrupt                               */
	, USART3_IRQn             = 39  /**< USART3 global interrupt                               */
	, EXTI15_10_IRQn          = 40  /**< EXTI line[15:10] interrupts                           */
	, RTC_Alarm_IRQn          = 41  /**< RTC alarms (A and B) through EXTI line interrupt      */
	, OTG_FS_WKUP_IRQn        = 42  /**< USB On-The-Go FS wakeup through EXTI line interrupt   */
	, TIM8_BRK_TIM12_IRQn     = 43  /**< TIM8 break interrupt and TIM12 global interrupt       */
	, TIM8_UP_TIM13_IRQn      = 44  /**< TIM8 update interrupt and TIM13 global interrupt      */
	, TIM8_TRG_COM_TIM14_IRQn = 45  /**< TIM8 trigger/commutation and TIM14 global interrupts  */
	, TIM8_CC_IRQn            = 46  /**< TIM8 capture compare interrupt                        */
	, DMA1_Stream7_IRQn       = 47  /**< DMA1 Stream7 global interrupt                         */
	, FMC_IRQn                = 48  /**< FMC global interrupt                                  */
	, SDMMC1_IRQn             = 49  /**< SDMMC1 global interrupt                               */
	, TIM5_IRQn               = 50  /**< TIM5 global interrupt                                 */
	, SPI3_IRQn               = 51  /**< SPI3 global interrupt                                 */
	, UART4_IRQn              = 52  /**< UART4 global interrupt                                */
	, UART5_IRQn              = 53  /**< UART5 global interrupt                                */
	, TIM6_DAC_IRQn           = 54  /**< TIM6 global, DAC1/DAC2 underrun error interrupts      */
	, TIM7_IRQn               = 55  /**< TIM7 global interrupt                                 */
	, DMA2_Stream0_IRQn       = 56  /**< DMA2 Stream0 global interrupt                         */
	, DMA2_Stream1_IRQn       = 57  /**< DMA2 Stream1 global interrupt                         */
	, DMA2_Stream2_IRQn       = 58  /**< DMA2 Stream2 global interrupt                         */
	, DMA2_Stream3_IRQn       = 59  /**< DMA2 Stream3 global interrupt                         */
	, DMA2_Stream4_IRQn       = 60  /**< DMA2 Stream4 global interrupt                         */
	, ETH_IRQn                = 61  /**< Ethernet global interrupt                             */
	, ETH_WKUP_IRQn           = 62  /**< Ethernet wakeup through EXTI line interrupt           */
	, CAN2_TX_IRQn            = 63  /**< CAN2 TX interrupts                                    */
	, CAN2_RX0_IRQn           = 64  /**< CAN2 RX0 interrupts                                   */
	, CAN2_RX1_IRQn           = 65  /**< CAN2 RX1 interrupt                                    */
	, CAN2_SCE_IRQn           = 66  /**< CAN2 SCE interrupt                                    */
	, OTG_FS_IRQn             = 67  /**< USB On-The-Go FS global interrupt                     */
	, DMA2_Stream5_IRQn       = 68  /**< DMA2 Stream5 global interrupt                         */
	, DMA2_Stream6_IRQn       = 69  /**< DMA2 Stream6 global interrupt                         */
	, DMA2_Stream7_IRQn       = 70  /**< DMA2 Stream7 global interrupt                         */
	, USART6_IRQn             = 71  /**< USART6 global interrupt                               */
	, I2C3_EV_IRQn            = 72  /**< I2C3 event interrupt                                  */
	, I2C3_ER_IRQn            = 73  /**< I2C3 error interrupt                                  */
	, OTG_HS_EP1_OUT_IRQn     = 74  /**< USB On-The-Go HS end point 1 out global interrupt     */
	, OTG_HS_EP1_IN_IRQn      = 75  /**< USB On-The-Go HS end point 1 in global interrupt      */
	, OTG_HS_WKUP_IRQn        = 76  /**< USB On-The-Go HS wakeup through EXTI interrupt        */
	, OTG_HS_IRQn             = 77  /**< USB On-The-Go HS global interrupt                     */
	, DCMI_IRQn               = 78  /**< DCMI global interrupt                                 */
	, CRYP_IRQn               = 79  /**< CRYP crypto global interrupt                          */
	, HASH_RNG_IRQn           = 80  /**< Hash and RNG global interrupt                         */
	, FPU_IRQn                = 81  /**< FPU global interrupt                                  */
	, UART7_IRQn              = 82  /**< UART7 global interrupt                                */
	, UART8_IRQn              = 83  /**< UART8 global interrupt                                */
	, SPI4_IRQn               = 84  /**< SPI4 global interrupt                                 */
	, SPI5_IRQn               = 85  /**< SPI5 global interrupt                                 */
	, SPI6_IRQn               = 86  /**< SPI6 global interrupt                                 */
	, SAI1_IRQn               = 87  /**< SAI1 global interrupt                                 */
	, LCD_TFT_IRQn            = 88  /**< LCD-TFT global interrupt                              */
	, LCD_TFT_ER_IRQn         = 89  /**< LCD-TFT global error interrupt                        */
	, DMA2D_IRQn              = 90  /**< DMA2D global interrupt                                */
	, SAI2_IRQn               = 91  /**< SAI2 global interrupt                                 */
	, QuadSPI_IRQn            = 92  /**< QuadSPI global interrupt                              */
	, LP_Timer1_IRQn          = 93  /**< LP Timer1 global interrupt                            */
	, HDMI_CEC_IRQn           = 94  /**< HDMI-CEC global interrupt                             */
	, I2C4_EV_IRQn            = 95  /**< I2C4 event interrupt                                  */
	, I2C4_ER_IRQn            = 96  /**< I2C4 error interrupt                                  */
	, SPDIFRX_IRQn            = 97  /**< SPDIFRX global interrupt                              */
	, DSIHOST_IRQn            = 98  /**< DSI host global interrupt                             */
	, DFSDM1_FLT0_IRQn        = 99  /**< DFSDM1 filter 0 global interrupt                      */
	, DFSDM1_FLT1_IRQn        = 100 /**< DFSDM1 filter 1 global interrupt                      */
	, DFSDM1_FLT2_IRQn        = 101 /**< DFSDM1 filter 2 global interrupt                      */
	, DFSDM1_FLT3_IRQn        = 102 /**< DFSDM1 filter 3 global interrupt                      */
	, SDMMC2_IRQn             = 103 /**< SDMMC2 global interrupt                               */
	, CAN3_TX_IRQn            = 104 /**< CAN3 TX interrupt                                     */
	, CAN3_RX0_IRQn           = 105 /**< CAN3 RX0 interrupt                                    */
	, CAN3_RX1_IRQn           = 106 /**< CAN3 RX1 interrupt                                    */
	, CAN3_SCE_IRQn           = 107 /**< CAN3 SCE interrupt                                    */
	, JPEG_IRQn               = 108 /**< JPEG global interrupt                                 */
	, MDIOS_IRQn              = 109 /**< MDIO slave global interrupt                           */
} IRQn_Type;

/* ============================================================================================== */
/* Cortex-M7 Core Configuration                                                                   */
/* ============================================================================================== */
#define __CM7_REV              0x0100U // Cortex-M7 revision r1p0
#define __MPU_PRESENT          1       // stm32f767zi provides a MPU
#define __VTOR_PRESENT         1       // stm32f767zi provides vector table offset capabilities
#define __NVIC_PRIO_BITS       4       // stm32f767zi uses 4 bits for NVIC priority levels
#define __Vendor_SysTickConfig 0       // No ST-specific SysTick_Config function is included
#define __FPU_PRESENT          1       // stm32f767zi provides a FPU
#define __ICACHE_PRESENT       1       // stm32f767zi provides i$
#define __DCACHE_PRESENT       1       // stm32f767zi provides d$
#define __DTCM_PRESENT         0       // stm32f767zi does not provide dTCM

#include "core_cm7.h"
#include "system_stm32f767zi.h"

/* ============================================================================================== */
/* Device Peripheral Access Layer                                                                 */
/* ============================================================================================== */
#include "stm32f767zi_registers_FLASH.h"
#include "stm32f767zi_registers_GPIO.h"
#include "stm32f767zi_registers_PWR.h"
#include "stm32f767zi_registers_RCC.h"

#ifdef __cplusplus
}
#endif

#endif /* STM32F767ZI_H */

/* EOF */
