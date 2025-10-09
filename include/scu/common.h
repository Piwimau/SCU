#ifndef SCU_COMMON_H
#define SCU_COMMON_H

#include <stdint.h>

/**
 * @brief Converts an expression to a string literal.
 *
 * @note In contrast to `SCU_XSTRINGIFY()`, this macro does not expand `expr`
 * before stringifying it.
 *
 * @param[in] expr The expression to convert to a string literal.
 * @return A string literal representation of `expr`.
 */
#define SCU_STRINGIFY(expr) #expr

/**
 * @brief Expands an expression and converts it to a string literal.
 *
 * @note In contrast to `SCU_STRINGIFY()`, this macro expands `expr` before
 * stringifying it.
 *
 * @param[in] expr The expression to expand and convert to a string literal.
 * @return A string literal representation of the expanded `expr`.
 */
#define SCU_XSTRINGIFY(expr) SCU_STRINGIFY(expr)

/**
 * @brief Returns the size of an expression (in bytes) as an `int64_t`.
 *
 * @param[in] expr The expression to evaluate the size of.
 * @return The size of the expression (in bytes) as an `int64_t`.
 */
#define SCU_SIZEOF(expr) ((int64_t) sizeof(expr))

#endif