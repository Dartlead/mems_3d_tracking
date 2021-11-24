#ifndef DARTLEAD_ASSERT_H
#define DARTLEAD_ASSERT_H

#include <stdint.h>
#include "FreeRTOS.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief FreeRTOS portable macro for assert that disables all interrupts before entering the custom assert
 *        function.
 */
#define dartlead_assert(EXPR) \
	do { \
		if (!(EXPR)) { \
			portDISABLE_INTERRUPTS(); \
			__dartlead_assert(); \
		} \
	} while (0)
#define dartlead_WTF dartlead_assert(0)

/**
 * @brief Custom assert that will flash the onboard RED LED and spin the core indefinitely.
 */
void __dartlead_assert(void);

#ifdef __cplusplus
}
#endif


#endif /* DARTLEAD_ASSERT_H */

/* EOF */
