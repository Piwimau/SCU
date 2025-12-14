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

/**
 * @brief Returns the size of an expression (in bytes) as an `int64_t`.
 *
 * @param[in] expr The expression to evaluate the size of.
 * @return The size of the expression (in bytes) as an `int64_t`.
 */
#define SCU_SIZEOF(expr) ((int64_t) sizeof(expr))

/**
 * @brief Returns the number of elements in a statically allocated array.
 *
 * @warning Do not use this macro with a pointer instead of a statically
 * allocated array, as it will yield an incorrect result.
 *
 * @param[in] array The statically allocated array.
 * @return The number of elements in the statically allocated array.
 */
#define SCU_COUNTOF(array) (SCU_SIZEOF(array) / SCU_SIZEOF((array)[0]))

/**
 * @brief Iterates over each element in a statically allocated array.
 *
 * This macro expands to a for loop that iterates over each element in the
 * specified statically allocated array. During each iteration, the provided
 * variable is assigned a pointer to the current element.
 *
 * The following example demonstrates the basic usage of this macro:
 *
 * ```c
 * // T is the type of the elements stored in the statically allocated array.
 * T elems[] = { ... };
 * ...
 * T* elem;
 * SCU_ARRAY_FOREACH(elem, elems) {
 *     // Do something with *elem.
 * }
 * ```
 *
 * @note The variable `elem` must be declared manually before the loop. It must
 * be of a pointer type compatible with the array's element type.
 *
 * @warning The behavior is undefined if `array` is not a statically allocated
 * array.
 *
 * @param[out] elem  A pointer to the current element during each iteration.
 * @param[in]  array The statically allocated array to iterate over.
 */
#define SCU_ARRAY_FOREACH(elem, array)                                        \
    for ((elem) = (array); (elem) < ((array) + SCU_COUNTOF(array)); (elem)++)

#endif