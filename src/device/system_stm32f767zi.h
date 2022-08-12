#ifndef SYSTEM_STM32F767ZI_H
#define SYSTEM_STM32F767ZI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ++++++++++++++++++++++++++++++++++++++ Global Variables ++++++++++++++++++++++++++++++++++++++ */

/**
 * @brief System core clock frequency.
 * @note  This global variable is not prefixed because it is a CMSIS-style variable.
 */
extern uint32_t SystemCoreClock;

/**
 * @brief AHB bus clock frequency.
 * @note  AHB domain clock is shared by both AHB buses.
 * @note  This global variable is not prefixed because it is a CMSIS-style variable.
 */
extern uint32_t SystemAHBClock;

/**
 * @brief APB1 bus clock frequency.
 * @note  This global variable is not prefixed because it is a CMSIS-style variable.
 */
extern uint32_t SystemAPB1Clock;

/**
 * @brief APB2 bus clock frequency.
 * @note  This global variable is not prefixed because it is a CMSIS-style variable.
 */
extern uint32_t SystemAPB2Clock;

/* ------------------------------------ End Global Variables ------------------------------------ */



/* ++++++++++++++++++++++++++++++++++++++ Public Functions ++++++++++++++++++++++++++++++++++++++ */

/**
 * @brief   Initializes the CPU's system, AHB, APB1 and APB2 clocks.
 * @details Attempts to set the:
 *             sysclk   -> 216 MHz via the main PLL's PLLP output
 *             AHB clk  -> 216 MHz
 *             APB1 clk -> 27 MHz
 *             APB2 clk -> 54 MHz
 *
 *          Should these frequencies be unobtainable (for whateve reason), the clock frequencies are
 *          set to their default values of:
 *             sysclk   -> 16 MHz via the HSI oscillator
 *             AHB clk  -> 16 MHz
 *             APB1 clk -> 16 MHz
 *             APB2 clk -> 16 MHz
 * @note    This function also sets the CMSIS-style global clock frequency variables.
 */
void SystemInit(void);

/**
 * @brief Updates the SystemCoreClock with the current core clock retrieved from cpu registers.
 * @note  Currently not implemented.
 */
void SystemCoreClockUpdate(void);

/* ------------------------------------ End Public Functions ------------------------------------ */

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_STM32F767ZI_H */

/* EOF */
