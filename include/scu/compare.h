#ifndef SCU_COMPARE_H
#define SCU_COMPARE_H

#include <stdint.h>

/**
 * @brief Compares two specified elements.
 *
 * @param[in] a A pointer to the first element.
 * @param[in] b A pointer to the second element.
 * @return A negative value if `a` is less than `b`, zero if they are equal, or
 * a positive value if `a` is greater than `b`.
 */
typedef int32_t SCUCompareFunc(const void* a, const void* b);

#endif