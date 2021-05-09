#include "stm32f767zi.h"
#include "FreeRTOSConfig.h"
#include <stdint.h>

/* ============================================================================================================= */
/* External References                                                                                           */
/* ============================================================================================================= */
extern int main(void);

/* ============================================================================================================= */
/* Heap Declaration                                                                                              */
/* ============================================================================================================= */
uint8_t ucHeap[configTOTAL_HEAP_SIZE] __attribute__((section(".heap")));

/* ============================================================================================================= */
/* Memory Region Symbols (Provided by Linker Script)                                                             */
/* ============================================================================================================= */
extern uint32_t __gst_start__;       //!# Start of the global section table
extern uint32_t __gst_end__;         //!# End of the global section table
extern uint32_t __etext;             //!# End of text segment
extern uint32_t __fast_text_start__; //!# Start of the fast_text segment
extern uint32_t __fast_text_end__;   //!# End of the fast_text segment
extern uint32_t __data_start__;      //!# Start of the data segment
extern uint32_t __data_end__;        //!# End of the data segment
extern uint32_t __bss_start__;       //!# Start of the BSS segment
extern uint32_t __bss_end__;         //!# End of the BSS segment
extern uint32_t __heap_base;         //!# Base of the memory region allocated for the heap
extern uint32_t __heap_limit;        //!# Limit of the memory region allocated for the heap
extern uint32_t __stack_limit;       //!# Limit of the stack
extern uint32_t __stack_top;         //!# Top of the stack
extern uint32_t __stack_base;        //!# Base of the stack

/* ============================================================================================================= */
/* Cortex-M7 Processor Exception Handlers                                                                        */
/* ============================================================================================================= */
void Default_Handler           (void);
void Reset_Handler             (void);
void NMI_Handler               (void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler         (void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler         (void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler        (void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler               (void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler            (void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler           (void) __attribute__((weak, alias("Default_Handler")));

/* ============================================================================================================= */
/* External Interrupt Handlers                                                                                   */
/* ============================================================================================================= */
void WWDG_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void PVD_Handler               (void) __attribute__((weak, alias("Default_Handler")));
void TAMP_STAMP_Handler        (void) __attribute__((weak, alias("Default_Handler")));
void RTC_WKUP_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void FLASH_Handler             (void) __attribute__((weak, alias("Default_Handler")));
void RCC_Handler               (void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_Handler             (void) __attribute__((weak, alias("Default_Handler")));
void EXTI1_Handler             (void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_Handler             (void) __attribute__((weak, alias("Default_Handler")));
void EXTI3_Handler             (void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_Handler             (void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream0_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream1_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream2_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream3_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream4_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream5_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream6_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void ADC_Handler               (void) __attribute__((weak, alias("Default_Handler")));
void CAN1_TX_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void CAN1_RX0_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void CAN1_RX1_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void CAN1_SCE_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_Handler     (void) __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_Handler     (void) __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void TIM2_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void TIM3_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void TIM4_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void SPI1_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void SPI2_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void USART1_Handler            (void) __attribute__((weak, alias("Default_Handler")));
void USART2_Handler            (void) __attribute__((weak, alias("Default_Handler")));
void USART3_Handler            (void) __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_Handler         (void) __attribute__((weak, alias("Default_Handler")));
void RTC_Alarm_Handler         (void) __attribute__((weak, alias("Default_Handler")));
void OTG_FS_WKUP_Handler       (void) __attribute__((weak, alias("Default_Handler")));
void TIM8_BRK_TIM12_Handler    (void) __attribute__((weak, alias("Default_Handler")));
void TIM8_UP_TIM13_Handler     (void) __attribute__((weak, alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_CC_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream7_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void FMC_Handler               (void) __attribute__((weak, alias("Default_Handler")));
void SDMMC1_Handler            (void) __attribute__((weak, alias("Default_Handler")));
void TIM5_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void SPI3_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void UART4_Handler             (void) __attribute__((weak, alias("Default_Handler")));
void UART5_Handler             (void) __attribute__((weak, alias("Default_Handler")));
void TIM6_DAC_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void TIM7_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream0_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream1_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream2_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream3_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream4_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void ETH_Handler               (void) __attribute__((weak, alias("Default_Handler")));
void ETH_WKUP_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void CAN2_TX_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void CAN2_RX0_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void CAN2_RX1_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void CAN2_SCE_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void OTG_FS_Handler            (void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream5_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream6_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream7_Handler      (void) __attribute__((weak, alias("Default_Handler")));
void USART6_Handler            (void) __attribute__((weak, alias("Default_Handler")));
void I2C3_EV_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void I2C3_ER_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_Handler    (void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_Handler     (void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_WKUP_Handler       (void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_Handler            (void) __attribute__((weak, alias("Default_Handler")));
void DCMI_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void CRYP_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void HASH_RNG_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void FPU_Handler               (void) __attribute__((weak, alias("Default_Handler")));
void UART7_Handler             (void) __attribute__((weak, alias("Default_Handler")));
void UART8_Handler             (void) __attribute__((weak, alias("Default_Handler")));
void SPI4_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void SPI5_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void SPI6_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void SAI1_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void LCD_TFT_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void LCD_TFT_ER_Handler        (void) __attribute__((weak, alias("Default_Handler")));
void DMA2D_Handler             (void) __attribute__((weak, alias("Default_Handler")));
void SAI2_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void QuadSPI_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void LP_Timer1_Handler         (void) __attribute__((weak, alias("Default_Handler")));
void HDMI_CEC_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void I2C4_EV_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void I2C4_ER_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void SPDIFRX_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void DSIHOST_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void DFSDM1_FLT0_Handler       (void) __attribute__((weak, alias("Default_Handler")));
void DFSDM1_FLT1_Handler       (void) __attribute__((weak, alias("Default_Handler")));
void DFSDM1_FLT2_Handler       (void) __attribute__((weak, alias("Default_Handler")));
void DFSDM1_FLT3_Handler       (void) __attribute__((weak, alias("Default_Handler")));
void SDMMC2_Handler            (void) __attribute__((weak, alias("Default_Handler")));
void CAN3_TX_Handler           (void) __attribute__((weak, alias("Default_Handler")));
void CAN3_RX0_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void CAN3_RX1_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void CAN3_SCE_Handler          (void) __attribute__((weak, alias("Default_Handler")));
void JPEG_Handler              (void) __attribute__((weak, alias("Default_Handler")));
void MDIOS_Handler             (void) __attribute__((weak, alias("Default_Handler")));

/* ============================================================================================================= */
/* Interrupt Vector Table                                                                                        */
/* ============================================================================================================= */
#if defined (__GNUC__)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpedantic"
#endif

__VECTOR_TABLE_ATTRIBUTE void (* const vector_table[])(void) = {
	  (void (*)(void))(&__stack_top)
	
	/* Processor exceptions         Description                                    Priority          Address     */
	, Reset_Handler              /* Reset                                          -3   (fixed)      0x0000 0004 */
	, NMI_Handler                /* Non-maskable interrupt                         -2   (fixed)      0x0000 0008 */
	, HardFault_Handler          /* All class of faults                            -1   (fixed)      0x0000 000C */
	, MemManage_Handler          /* Memory management fault                         0   (settable)   0x0000 0010 */
	, BusFault_Handler           /* Pre-fetch fault, memory access fault            1   (settable)   0x0000 0014 */
	, UsageFault_Handler         /* Undefined instruction or illegal state          2   (settable)   0x0000 0018 */
	, 0                          /* Reserved                                       N/A               0x0000 001C */
	, 0                          /* Reserved                                       N/A               0x0000 0020 */
	, 0                          /* Reserved                                       N/A               0x0000 0024 */
	, 0                          /* Reserved                                       N/A               0x0000 0028 */
	, SVC_Handler                /* System service call via SWI instruction         3   (settable)   0x0000 002C */
	, DebugMon_Handler           /* Debug Monitor                                   4   (settable)   0x0000 0030 */
	, 0                          /* Reserved                                       N/A               0x0000 0034 */
	, PendSV_Handler             /* Pendable request for system service             5   (settable)   0x0000 0038 */
	, SysTick_Handler            /* System tick timer                               6   (settable)   0x0000 003C */

	/* External interrupts          Description                                    Priority          Address     */
	, WWDG_Handler               /* Window Watchdog                                0-15 (settable)   0x0000 0040 */
	, PVD_Handler                /* PVD through EXTI line detection                0-15 (settable)   0x0000 0044 */
	, TAMP_STAMP_Handler         /* Tamper and TimeStamp through EXTI line         0-15 (settable)   0x0000 0048 */
	, RTC_WKUP_Handler           /* RTC Wakeup through the EXTI line               0-15 (settable)   0x0000 004C */
	, FLASH_Handler              /* Flash global                                   0-15 (settable)   0x0000 0050 */
	, RCC_Handler                /* RCC global                                     0-15 (settable)   0x0000 0054 */
	, EXTI0_Handler              /* EXTI Line0                                     0-15 (settable)   0x0000 0058 */
	, EXTI1_Handler              /* EXTI Line1                                     0-15 (settable)   0x0000 005C */
	, EXTI2_Handler              /* EXTI Line2                                     0-15 (settable)   0x0000 0060 */
	, EXTI3_Handler              /* EXTI Line3                                     0-15 (settable)   0x0000 0064 */
	, EXTI4_Handler              /* EXTI Line4                                     0-15 (settable)   0x0000 0068 */
	, DMA1_Stream0_Handler       /* DMA1 Stream0 global                            0-15 (settable)   0x0000 006C */
	, DMA1_Stream1_Handler       /* DMA1 Stream1 global                            0-15 (settable)   0x0000 0070 */
	, DMA1_Stream2_Handler       /* DMA1 Stream2 global                            0-15 (settable)   0x0000 0074 */
	, DMA1_Stream3_Handler       /* DMA1 Stream3 global                            0-15 (settable)   0x0000 0078 */
	, DMA1_Stream4_Handler       /* DMA1 Stream4 global                            0-15 (settable)   0x0000 007C */
	, DMA1_Stream5_Handler       /* DMA1 Stream5 global                            0-15 (settable)   0x0000 0080 */
	, DMA1_Stream6_Handler       /* DMA1 Stream6 global                            0-15 (settable)   0x0000 0084 */
	, ADC_Handler                /* ADC1, ADC2, and ADC3 global                    0-15 (settable)   0x0000 0088 */
	, CAN1_TX_Handler            /* CAN1 TX                                        0-15 (settable)   0x0000 008C */
	, CAN1_RX0_Handler           /* CAN1 RX0                                       0-15 (settable)   0x0000 0090 */
	, CAN1_RX1_Handler           /* CAN1 RX1                                       0-15 (settable)   0x0000 0094 */
	, CAN1_SCE_Handler           /* CAN1 SCE                                       0-15 (settable)   0x0000 0098 */
	, EXTI9_5_Handler            /* EXTI Line[9:5]                                 0-15 (settable)   0x0000 009C */
	, TIM1_BRK_TIM9_Handler      /* TIM1 Break and TIM9 global                     0-15 (settable)   0x0000 00A0 */
	, TIM1_UP_TIM10_Handler      /* TIM1 Update and TIM10 global                   0-15 (settable)   0x0000 00A4 */
	, TIM1_TRG_COM_TIM11_Handler /* TIM1 Trigger and Commutation and TIM11 global  0-15 (settable)   0x0000 00A8 */
	, TIM1_CC_Handler            /* TIM1 Capture Compare                           0-15 (settable)   0x0000 00AC */
	, TIM2_Handler               /* TIM2 global                                    0-15 (settable)   0x0000 00B0 */
	, TIM3_Handler               /* TIM3 global                                    0-15 (settable)   0x0000 00B4 */
	, TIM4_Handler               /* TIM4 global                                    0-15 (settable)   0x0000 00B8 */
	, I2C1_EV_Handler            /* I2C1 event                                     0-15 (settable)   0x0000 00BC */
	, I2C1_ER_Handler            /* I2C1 error                                     0-15 (settable)   0x0000 00C0 */
	, I2C2_EV_Handler            /* I2C2 event                                     0-15 (settable)   0x0000 00C4 */
	, I2C2_ER_Handler            /* I2C2 error                                     0-15 (settable)   0x0000 00C8 */
	, SPI1_Handler               /* SPI1 global                                    0-15 (settable)   0x0000 00CC */
	, SPI2_Handler               /* SPI2 global                                    0-15 (settable)   0x0000 00D0 */
	, USART1_Handler             /* USART1 global                                  0-15 (settable)   0x0000 00D4 */
	, USART2_Handler             /* USART2 global                                  0-15 (settable)   0x0000 00D8 */
	, USART3_Handler             /* USART3 global                                  0-15 (settable)   0x0000 00DC */
	, EXTI15_10_Handler          /* EXTI Line[15:10]                               0-15 (settable)   0x0000 00E0 */
	, RTC_Alarm_Handler          /* RTC Alarms (A and B) through EXTI line         0-15 (settable)   0x0000 00E4 */
	, OTG_FS_WKUP_Handler        /* USB On-The-Go FS Wakeup through EXTI line      0-15 (settable)   0x0000 00E8 */
	, TIM8_BRK_TIM12_Handler     /* TIM8 Break and TIM12 global                    0-15 (settable)   0x0000 00EC */
	, TIM8_UP_TIM13_Handler      /* TIM8 Update and TIM13 global                   0-15 (settable)   0x0000 00F0 */
	, TIM8_TRG_COM_TIM14_Handler /* TIM8 Trigger and Commutation and TIM14 global  0-15 (settable)   0x0000 00F4 */
	, TIM8_CC_Handler            /* TIM8 Capture Compare                           0-15 (settable)   0x0000 00F8 */
	, DMA1_Stream7_Handler       /* DMA1 Stream7 global                            0-15 (settable)   0x0000 00FC */
	, FMC_Handler                /* FMC global                                     0-15 (settable)   0x0000 0100 */
	, SDMMC1_Handler             /* SDMMC1 global                                  0-15 (settable)   0x0000 0104 */
	, TIM5_Handler               /* TIM5 global                                    0-15 (settable)   0x0000 0108 */
	, SPI3_Handler               /* SPI3 global                                    0-15 (settable)   0x0000 010C */
	, UART4_Handler              /* UART4 global                                   0-15 (settable)   0x0000 0110 */
	, UART5_Handler              /* UART5 global                                   0-15 (settable)   0x0000 0114 */
	, TIM6_DAC_Handler           /* TIM6 global, DAC1 and DAC2 underrun error      0-15 (settable)   0x0000 0118 */
	, TIM7_Handler               /* TIM7 global                                    0-15 (settable)   0x0000 011C */
	, DMA2_Stream0_Handler       /* DMA2 Stream0 global                            0-15 (settable)   0x0000 0120 */
	, DMA2_Stream1_Handler       /* DMA2 Stream1 global                            0-15 (settable)   0x0000 0124 */
	, DMA2_Stream2_Handler       /* DMA2 Stream2 global                            0-15 (settable)   0x0000 0128 */
	, DMA2_Stream3_Handler       /* DMA2 Stream3 global                            0-15 (settable)   0x0000 012C */
	, DMA2_Stream4_Handler       /* DMA2 Stream4 global                            0-15 (settable)   0x0000 0130 */
	, ETH_Handler                /* Ethernet global                                0-15 (settable)   0x0000 0134 */
	, ETH_WKUP_Handler           /* Ethernet Wakeup through EXTI line              0-15 (settable)   0x0000 0138 */
	, CAN2_TX_Handler            /* CAN2 TX                                        0-15 (settable)   0x0000 013C */
	, CAN2_RX0_Handler           /* CAN2 RX0                                       0-15 (settable)   0x0000 0140 */
	, CAN2_RX1_Handler           /* CAN2 RX1                                       0-15 (settable)   0x0000 0144 */
	, CAN2_SCE_Handler           /* CAN2 SCE                                       0-15 (settable)   0x0000 0148 */
	, OTG_FS_Handler             /* USB On-The-Go FS global                        0-15 (settable)   0x0000 014C */
	, DMA2_Stream5_Handler       /* DMA2 Stream5 global                            0-15 (settable)   0x0000 0150 */
	, DMA2_Stream6_Handler       /* DMA2 Stream6 global                            0-15 (settable)   0x0000 0154 */
	, DMA2_Stream7_Handler       /* DMA2 Stream7 global                            0-15 (settable)   0x0000 0158 */
	, USART6_Handler             /* USART6 global                                  0-15 (settable)   0x0000 015C */
	, I2C3_EV_Handler            /* I2C3 event                                     0-15 (settable)   0x0000 0160 */
	, I2C3_ER_Handler            /* I2C3 error                                     0-15 (settable)   0x0000 0164 */
	, OTG_HS_EP1_OUT_Handler     /* USB On-The-Go HS End Point 1 Out global        0-15 (settable)   0x0000 0168 */
	, OTG_HS_EP1_IN_Handler      /* USB On-The-Go HS End Point 1 In global         0-15 (settable)   0x0000 016C */
	, OTG_HS_WKUP_Handler        /* USB On-The-Go HS Wakeup through EXTI           0-15 (settable)   0x0000 0170 */
	, OTG_HS_Handler             /* USB On-The-Go HS global                        0-15 (settable)   0x0000 0174 */
	, DCMI_Handler               /* DCMI global                                    0-15 (settable)   0x0000 0178 */
	, CRYP_Handler               /* CRYP crypto global                             0-15 (settable)   0x0000 017C */
	, HASH_RNG_Handler           /* Hash and Rng global                            0-15 (settable)   0x0000 0180 */
	, FPU_Handler                /* FPU global                                     0-15 (settable)   0x0000 0184 */
	, UART7_Handler              /* UART7 global                                   0-15 (settable)   0x0000 0188 */
	, UART8_Handler              /* UART8 global                                   0-15 (settable)   0x0000 018C */
	, SPI4_Handler               /* SPI4 global                                    0-15 (settable)   0x0000 0190 */
	, SPI5_Handler               /* SPI5 global                                    0-15 (settable)   0x0000 0194 */
	, SPI6_Handler               /* SPI6 global                                    0-15 (settable)   0x0000 0198 */
	, SAI1_Handler               /* SAI1 global                                    0-15 (settable)   0x0000 019C */
	, LCD_TFT_Handler            /* LCD-TFT global                                 0-15 (settable)   0x0000 01A0 */
	, LCD_TFT_ER_Handler         /* LCD-TFT global Error                           0-15 (settable)   0x0000 01A4 */
	, DMA2D_Handler              /* DMA2D global                                   0-15 (settable)   0x0000 01A8 */
	, SAI2_Handler               /* SAI2 global                                    0-15 (settable)   0x0000 01AC */
	, QuadSPI_Handler            /* QuadSPI global                                 0-15 (settable)   0x0000 01B0 */
	, LP_Timer1_Handler          /* LP Timer1 global                               0-15 (settable)   0x0000 01B4 */
	, HDMI_CEC_Handler           /* HDMI-CEC global                                0-15 (settable)   0x0000 01B8 */
	, I2C4_EV_Handler            /* I2C4 event                                     0-15 (settable)   0x0000 01BC */
	, I2C4_ER_Handler            /* I2C4 Error                                     0-15 (settable)   0x0000 01C0 */
	, SPDIFRX_Handler            /* SPDIFRX global                                 0-15 (settable)   0x0000 01C4 */
	, DSIHOST_Handler            /* DSI host global                                0-15 (settable)   0x0000 01C8 */
	, DFSDM1_FLT0_Handler        /* DFSDM1 Filter 0 global                         0-15 (settable)   0x0000 01CC */
	, DFSDM1_FLT1_Handler        /* DFSDM1 Filter 1 global                         0-15 (settable)   0x0000 01D0 */
	, DFSDM1_FLT2_Handler        /* DFSDM1 Filter 2 global                         0-15 (settable)   0x0000 01D4 */
	, DFSDM1_FLT3_Handler        /* DFSDM1 Filter 3 global                         0-15 (settable)   0x0000 01D8 */
	, SDMMC2_Handler             /* SDMMC2 global                                  0-15 (settable)   0x0000 01DC */
	, CAN3_TX_Handler            /* CAN3 TX                                        0-15 (settable)   0x0000 01E0 */
	, CAN3_RX0_Handler           /* CAN3 RX0                                       0-15 (settable)   0x0000 01E4 */
	, CAN3_RX1_Handler           /* CAN3 RX1                                       0-15 (settable)   0x0000 01E8 */
	, CAN3_SCE_Handler           /* CAN3 SCE                                       0-15 (settable)   0x0000 01EC */
	, JPEG_Handler               /* JPEG global                                    0-15 (settable)   0x0000 01F0 */
	, MDIOS_Handler              /* MDIO slave global                              0-15 (settable)   0x0000 01F4 */
};

#if defined ( __GNUC__ )
	#pragma GCC diagnostic pop
#endif

/* ============================================================================================================= */
/* Reset Handler                                                                                                 */
/* ============================================================================================================= */
/*! The code to be run on processor POR.
 *
 * @brief The reset handler is run on processor POR and copies any .text.fast_text instructions stored in flash
 *        into instruction TCM, any .data stored in flash in data TCM, and zeroes-out the .bss section, then
 *        performs the SystemInit() call before entering main.
 *
 *        The gst or global section table contains (in this exact order for an arbitrary linker output section):
 *        4 bytes representing said section's LMA, 4 bytes representing said section's VMA, and 4 bytes
 *        representing the length of said section in bytes. There can be as many of these triplets of values as
 *        there are linker output sections that need to be moved to their VMA from their LMA.
 *
 *        Thus to move, for example, the .text.fast_text from flash to instruction TCM, we get the address of the
 *        start of the gst (which is equivalent to the first entry in the table i.e. the .text.fast_text's LMA) and
 *        the next 4 bytes after that which contains the .text.fast_text section's VMA. The next 4 bytes after
 *        that contain the .text.fast_text section's length, then it is simply a for-loop to transfer the data
 *        from the VMA to the LMA.
 *
 * @note  The gst_addr pointer is marked volatile b/c if it is not, the optimizer will (at level -O2 and greater),
 *        treat the pointer as an array of length 1 and thus all of the pointer arithmetic done will result in
 *        array out-of-boundary errors.
 */
__NO_RETURN void Reset_Handler(void)
{
	uint32_t            i           = 0;
	uint32_t            section_len = 0;
	uint32_t *          LMA_addr    = 0;
	uint32_t *          VMA_addr    = 0;
	uint32_t * volatile gst_addr    = (uint32_t *)(&__gst_start__);

	//!# Copy the .text.fast_text section from flash to ITCM
	LMA_addr    = (uint32_t *)(*gst_addr);
	VMA_addr    = (uint32_t *)(*++gst_addr);
	section_len = *++gst_addr;
	for (i = 0; i < section_len; i += 4) {
		*VMA_addr++ = *LMA_addr++;
	}

	//!# Copy the .data section from flash to main SRAM
	LMA_addr    = (uint32_t *)(*++gst_addr);
	VMA_addr    = (uint32_t *)(*++gst_addr);
	section_len = *++gst_addr;
	for (i = 0; i < section_len; i += 4) {
		*VMA_addr++ = *LMA_addr++;
	}

	//!# Zero-out the .bss section
	for (VMA_addr = &__bss_start__; VMA_addr < &__bss_end__;) {
		*VMA_addr++ = 0UL;
	}

	SystemInit();

	int main_ret = main();

	(void)main_ret;
	while (1);
}

/* ============================================================================================================= */
/* Default Handler for Exceptions/Interrupts                                                                     */
/* ============================================================================================================= */
void Default_Handler(void)
{
	while (1);
}

/* EOF */
