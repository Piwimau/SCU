#ifndef SCU_ASSERT_H
#define SCU_ASSERT_H

#include <stdint.h>

/**
 * @brief Declares a compile-time assertion.
 *
 * This macro can be used to check a condition at compile-time. If the condition
 * is not met, the code will fail to compile and a diagnostic message will be
 * generated.
 *
 * ```c
 * SCU_STATIC_ASSERT((sizeof(int) * CHAR_WIDTH) == 32);
 * ```
 *
 * Optionally, a message may be passed as the second argument for providing
 * additional information when the assertion fails.
 *
 * ```c
 * SCU_STATIC_ASSERT(
 *     (sizeof(int) * CHAR_WIDTH) == 32,
 *     "Expected int to be 32 bits wide."
 * );
 * ```
 *
 * @note As of C23, `static_assert` became a keyword (instead of a macro defined
 * in `assert.h`). This macro is simply provided for reasons of completeness and
 * consistency with the `SCU_ASSERT()` macro.
 *
 * @param[in] expr The expression to evaluate at compile-time.
 * @param[in] ...  An optional message for providing additional information if
 *                 the assertion fails.
 */
#define SCU_STATIC_ASSERT(expr, ...)              \
    static_assert(expr __VA_OPT__(,) __VA_ARGS__)

/**
 * @brief Handles a runtime assertion failure.
 *
 * @note This function is an implementation detail and not meant to be called
 * directly. Use the `SCU_ASSERT()` macro instead.
 *
 * @warning This function terminates the program abnormally and does not return
 * (as indicated by the `[[noreturn]]` attribute).
 *
 * @param[in] expr The expression which caused the assertion failure.
 * @param[in] file The name of the file in which the assertion failure occurred.
 * @param[in] line The line in which the assertion failure occurred.
 * @param[in] func The name of the function in which the assertion failure
 *                 occurred.
 * @param[in] fmt  An optional `printf()`-style format string for providing
 *                 additional information. If equal to `nullptr`, no additional
 *                 message is displayed and the variable arguments are ignored.
 * @param[in] ...  A variable number of arguments to be formatted according to
 *                 the `fmt` string.
 */
[[noreturn]]
void scu_assert_fail(
    const char* restrict expr,
    const char* restrict file,
    int64_t line,
    const char* restrict func,
    const char* restrict fmt,
    ...
);

#ifdef NDEBUG

    /**
     * @brief Does nothing, as `NDEBUG` is defined.
     *
     * @param[in] expr Unused.
     */
    #define SCU_ASSERT(expr, ...) ((void) 0)

#else

    /**
     * @brief Declares a runtime assertion.
     *
     * This macro can be used to check a condition at runtime. If the condition
     * is not met, a diagnostic message will be printed to the standard error
     * stream and the program will be terminated abnormally.
     *
     * A `printf()`-style format string and a variable number of arguments may
     * optionally be passed to provide additional information.
     *
     * ```c
     * void example(int* values, int length) {
     *     SCU_ASSERT(values != nullptr);
     *     SCU_ASSERT(
     *         length >= 0,
     *         "The length must be positive (was %d).",
     *         length
     *     );
     *     ...
     * }
     * ```
     *
     * @note Runtime assertions are disabled when the standard `NDEBUG` macro is
     * defined before this header is (directly or transitively) included.
     *
     * @param[in] expr The expression to test.
     * @param[in] ...  A variable number of arguments for providing additional
     *                 information. If present, the first argument must be a
     *                 null-terminated `printf()`-style format string, followed
     *                 by any number of additional arguments to be formatted.
     */
    #define SCU_ASSERT(expr, ...)                                              \
        do {                                                                   \
            if (!(expr)) {                                                     \
                __VA_OPT__(                                                    \
                    scu_assert_fail(                                           \
                        #expr,                                                 \
                        __FILE__,                                              \
                        __LINE__,                                              \
                        __func__,                                              \
                        __VA_ARGS__                                            \
                    );                                                         \
                )                                                              \
                scu_assert_fail(#expr, __FILE__, __LINE__, __func__, nullptr); \
            }                                                                  \
        }                                                                      \
        while (false)

#endif

#endif