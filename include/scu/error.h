#ifndef SCU_ERROR_H
#define SCU_ERROR_H

#include <stdint.h>

/** @brief Represents an error code used to signal success or failure. */
typedef enum SCUError {

    /** @brief Indicates that no error occurred. */
    SCU_ERROR_NONE,

    /** @brief Indicates that an out-of-memory condition occurred. */
    SCU_ERROR_OUT_OF_MEMORY,

    /** @brief Indicates that a file could not be (re-)opened. */
    SCU_ERROR_OPENING_FILE,

    /**
     * @brief Indicates that the end-of-file condition was reached before any
     * data could be read from a file stream.
     */
    SCU_ERROR_END_OF_FILE,

    /**
     * @brief Indicates that an error occurred while reading from a file stream.
     */
    SCU_ERROR_READING_FILE,

    /**
     * @brief Indicates that an error occurred while writing to a file stream.
     */
    SCU_ERROR_WRITING_FILE,

    /** @brief Indicates that an error occurred while writing to a buffer. */
    SCU_ERROR_WRITING_BUFFER,

    /** @brief Indicates that an error occurred while flushing a file stream. */
    SCU_ERROR_FLUSHING_FILE,

    /**
     * @brief Indicates that an error occurred while setting the file position
     * indicator of a file stream.
     */
    SCU_ERROR_SEEKING_FILE,

    /** @brief Indicates that an error occurred while closing a file stream. */
    SCU_ERROR_CLOSING_FILE,

    /** @brief Indicates that an error occurred while removing a file. */
    SCU_ERROR_REMOVING_FILE,

    /** @brief Indicates that an error occurred while renaming a file. */
    SCU_ERROR_RENAMING_FILE,

    /** @brief Indicates that an error occurred while using a stopwatch. */
    SCU_ERROR_STOPWATCH_FAILED,

    /** @brief Indicates that something is already present. */
    SCU_ERROR_ALREADY_PRESENT,

    /** @brief Indicates that an input was not in the expected format. */
    SCU_ERROR_INVALID_FORMAT

} SCUError;

/**
 * @brief Prints a diagnostic message to the standard error stream and
 * terminates the program abnormally.
 *
 * @note This function is an implementation detail and is not meant to be called
 * directly. Use the `SCU_FATAL()` macro instead.
 *
 * @warning This function terminates the program abnormally and does not return
 * (as indicated by the `[[noreturn]]` attribute).
 *
 * @param[in] file The name of the file in which the error occurred.
 * @param[in] line The line in which the error occurred.
 * @param[in] func The name of the function in which the error occurred.
 * @param[in] fmt  A `printf()`-style format string containing the error
 *                 message.
 * @param[in] ...  A variable number of arguments to be formatted according to
 *                 the `fmt` string.
 */
[[noreturn]]
void scu_fatal(
    const char* restrict file,
    int64_t line,
    const char* restrict func,
    const char* restrict fmt,
    ...
);

/**
 * @brief Prints a diagnostic message to the standard error stream and
 * terminates the program abnormally.
 *
 * This macro accepts a `printf()`-style format string and a variable number of
 * arguments for providing additional information. It wraps the `scu_fatal()`
 * function, such that it automatically includes the file, line and function in
 * which the error occurred.
 *
 * ```c
 * size_t length = 1024;
 * char* buffer = malloc(length);
 * if (buffer == nullptr) {
 *     SCU_FATAL("Failed to allocate %zu bytes of memory.\n", length);
 * }
 * ```
 *
 * @warning This function terminates the program abnormally and does not return
 * (as indicated by the `[[noreturn]]` attribute).
 *
 * @param[in] fmt A `printf()`-style format string containing the error message.
 * @param[in] ... A variable number of arguments to be formatted according to
 *                the `fmt` string.
 */
#define SCU_FATAL(fmt, ...)                                                \
    scu_fatal(__FILE__, __LINE__, __func__, fmt __VA_OPT__(,) __VA_ARGS__)

/**
 * @brief Marks a code path as unreachable.
 *
 * @warning If executed, this macro invokes `SCU_FATAL()`, which prints a
 * diagnostic message to the standard error stream and terminates the program
 * abnormally.
 */
#define SCU_UNREACHABLE()                                     \
    SCU_FATAL("Reached a code path marked as unreachable.\n")

#endif