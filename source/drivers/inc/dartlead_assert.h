#ifndef DARTLEAD_ASSERT_H
#define DARTLEAD_ASSERT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! Custom assert.
 *
 * @brief Assert that will flash the onboard RED LED and spin indefinitely.
 */
void dartlead_assert(void);

#ifdef __cplusplus
}
#endif


#endif /* DARTLEAD_ASSERT_H */

/* EOF */
