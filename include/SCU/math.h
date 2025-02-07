#ifndef SCU_MATH_H
#define SCU_MATH_H

/**
 * @brief Returns the minimum of two values.
 *
 * @param[in] a First value for the comparison.
 * @param[in] b Second value for the comparison.
 * @return The minimum of the two values.
 */
#define SCU_MIN(a, b) (((a) < (b)) ? (a) : (b))

/**
 * @brief Returns the maximum of two values.
 *
 * @param[in] a First value for the comparison.
 * @param[in] b Second value for the comparison.
 * @return The maximum of the two values.
 */
#define SCU_MAX(a, b) (((a) > (b)) ? (a) : (b))

#endif