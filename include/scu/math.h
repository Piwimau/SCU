#ifndef SCU_MATH_H
#define SCU_MATH_H

/**
 * @brief Returns the minimum of two values.
 *
 * @param[in] a The first value.
 * @param[in] b The second value.
 * @return The minimum of `a` and `b`.
 */
#define SCU_MIN(a, b) (((a) < (b)) ? (a) : (b))

/**
 * @brief Returns the maximum of two values.
 *
 * @param[in] a The first value.
 * @param[in] b The second value.
 * @return The maximum of `a` and `b`.
 */
#define SCU_MAX(a, b) (((a) > (b)) ? (a) : (b))

#endif