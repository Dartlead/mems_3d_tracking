#ifndef SYSTEM_STM32F767ZI_H
#define SYSTEM_STM32F767ZI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! Pound defines for initial clock behavior.
 */
#define DEFAULT_SYSTEM_CLOCK_FREQ 16000000UL //!# (HSI at 16 MHz)
#define DEFAULT_AHB_CLOCK_FREQ    16000000UL //!# System clock not divided
#define DEFAULT_APB1_CLOCK_FREQ   16000000UL //!# AHB clock not divided
#define DEFAULT_APB2_CLOCK_FREQ   16000000UL //!# AHB clock not divided

/*! System's clock frequencies in hertz.
 */
extern uint32_t SystemCoreClock;
extern uint32_t SystemAHBClock;  //!# AHB domain clock is shared by both AHB buses
extern uint32_t SystemAPB1Clock;
extern uint32_t SystemAPB2Clock;

/*! Setup the microcontroller system.
 *
 * @brief Initializes the system and updates the SystemCoreClock variable.
 */
void SystemInit(void);

/*! Updates the SystemCoreClock variable.
 *
 * @brief Updates the SystemCoreClock with the current core clock retrieved from cpu registers.
 */
void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_STM32F767ZI_H */

/* EOF */
