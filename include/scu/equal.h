#ifndef SCU_EQUAL_H
#define SCU_EQUAL_H

/**
 * @brief Determines whether two specified elements are equal.
 *
 * @param[in] a A pointer to the first element.
 * @param[in] b A pointer to the second element.
 * @return `true` if `a` and `b` are equal, otherwise `false`.
 */
typedef bool SCUEqualFunc(const void* a, const void* b);

#endif