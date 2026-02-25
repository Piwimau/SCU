#ifndef SCU_PREP_H
#define SCU_PREP_H

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
 * @brief Concatenates two tokens into a single token.
 *
 * @note In contrast to `SCU_XCONCAT()`, this macro does not expand `a` and `b`
 * before concatenating them.
 *
 * @param[in] a The first token.
 * @param[in] b The second token.
 * @return The concatenated token.
 */
#define SCU_CONCAT(a, b) a##b

/**
 * @brief Expands two tokens and concatenates them into a single token.
 *
 * @note In contrast to `SCU_CONCAT()`, this macro expands `a` and `b` before
 * concatenating them.
 *
 * @param[in] a The first token.
 * @param[in] b The second token.
 * @return The concatenated token after expanding `a` and `b`.
 */
#define SCU_XCONCAT(a, b) SCU_CONCAT(a, b)

#endif