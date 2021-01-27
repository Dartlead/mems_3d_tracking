#ifndef SYSTEM_STM32F767ZI_H
#define SYSTEM_STM32F767ZI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! Pound defines for initial clock behavior.
 */
#define DEFAULT_SYSTEM_CLOCK_FREQ 216000000UL

/*! System clock frequency in hertz (core clock).
 */
extern uint32_t SystemCoreClock;

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
