#ifndef SCU_IO_H
#define SCU_IO_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <SCU/error.h>

/**
 * @brief Reads characters from a given input stream into a dynamically allocated buffer until a
 * newline character (`\n`) is found or the end-of-file condition occurs.
 *
 * @note This function assumes the content read from `stream` to be UTF-8 encoded and processes it
 * accordingly.
 *
 * `*buffer` is allowed to be a `nullptr`, in which case `*capacity` must be zero (and vice versa).
 * If `*buffer` is not a `nullptr`, it must have been allocated by `SCU_MALLOC()`, `SCU_CALLOC()`
 * or `SCU_REALLOC()` (or compatible functions these macros are implemented with, which are the
 * standard `malloc()`, `calloc()` and `realloc()` functions by default) and `*capacity` must be
 * greater than zero.
 *
 * On success, `*buffer` is resized as required to fit the line read from `stream` and the new
 * capacity is stored in `*capacity`. The buffer contains the newline character (`\n`) if one is
 * found and is guaranteed to be null-terminated. If the end-of-file condition occurs after reading
 * at least one character, this is treated as a successful read and `SCU_ERROR_NONE` is returned.
 *
 * @warning On failure, `*buffer` and `*capacity` remain in the state they were in just before the
 * error occurred. The content of the buffer pointed to by `*buffer` is indeterminate and it might
 * not be null-terminated. Any characters read from `stream` in the meantime are not recovered.
 *
 * The caller is expected to close `stream` and deallocate `*buffer` with `SCU_FREE()` when no
 * longer needed.
 *
 * @param[in, out] stream   Input stream to read a single line from.
 * @param[in, out] buffer   Dynamically allocated buffer to write the line to. It is resized with
 *                          `SCU_REALLOC()` as required.
 * @param[in, out] capacity Capacity of the buffer (including the terminating `\0` byte),
 *                          updated whenever `*buffer` is resized.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `*capacity` is negative or if `*buffer` is a `nullptr`
 * and `*capacity` is not equal to zero (or vice versa), `SCU_ERROR_OUT_OF_MEMORY` if an
 * out-of-memory condition occurred, `SCU_ERROR_READING_STREAM_FAILED` if reading from `stream`
 * failed, `SCU_ERROR_END_OF_FILE` if end-of-file condition occurred before any characters could be
 * read and `SCU_ERROR_NONE` otherwise.
 */
SCUError scu_readLine(FILE* stream, char** buffer, int64_t* capacity);

/**
 * @brief Writes a formatted string to a given dynamically allocated output buffer, resizing it as
 * required.
 *
 * @note `*buffer` is allowed to be a `nullptr`, in which case `*capacity` must be zero (and vice
 * versa). If `*buffer` is not a `nullptr`, it must have been allocated by `SCU_MALLOC()`,
 * `SCU_CALLOC()` or `SCU_REALLOC()` (or compatible functions these macros are implemented with,
 * which are the standard `malloc()`, `calloc()` and `realloc()` functions by default) and
 * `*capacity` must be greater than zero.
 *
 * On success, `*buffer` is resized as required to fit the formatted string, the new capacity is
 * stored in `*capacity` and `*buffer` is guaranteed to be null-terminated.
 *
 * @warning On failure, `*buffer` and `*capacity` remain in the state they were in just before the
 * error occurred. In this case, the content of the buffer pointed to by `*buffer` is indeterminate
 * and it might not be null-terminated.
 *
 * The caller is expected to deallocate `*buffer` with `SCU_FREE()` when no longer needed.
 *
 * @param[in, out] buffer   Dynamically allocated output buffer to write the formatted message to.
 *                          It is resized with `SCU_REALLOC()` as required.
 * @param[in, out] capacity Capacity of the dynamically allocated output buffer (including the
 *                          terminating `\0` byte), updated if `*buffer` is resized.
 * @param[in]      format   A null-terminated format string following the same conventions as the
 *                          standard `printf()` family of functions.
 * @param[in]      ...      Any number of additional arguments to be formatted and written based on
 *                          the given format string.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `*capacity` is negative or if `*buffer` is a `nullptr`
 * and `*capacity` is not equal to zero (or vice versa), `SCU_ERROR_OUT_OF_MEMORY` if an
 * out-of-memory condition occurred, `SCU_ERROR_WRITING_BUFFER_FAILED` if writing to `*buffer`
 * failed and `SCU_ERROR_NONE` otherwise.
 */
SCUError scu_rsnprintf(char** buffer, int64_t* capacity, const char* format, ...);

/**
 * @brief Writes a formatted string to a given dynamically allocated output buffer, resizing it as
 * required.
 *
 * @note `*buffer` is allowed to be a `nullptr`, in which case `*capacity` must be zero (and vice
 * versa). If `*buffer` is not a `nullptr`, it must have been allocated by `SCU_MALLOC()`,
 * `SCU_CALLOC()` or `SCU_REALLOC()` (or compatible functions these macros are implemented with,
 * which are the standard `malloc()`, `calloc()` and `realloc()` functions by default) and
 * `*capacity` must be greater than zero.
 *
 * On success, `*buffer` is resized as required to fit the formatted string, the new capacity is
 * stored in `*capacity` and `*buffer` is guaranteed to be null-terminated.
 *
 * @warning On failure, `*buffer` and `*capacity` remain in the state they were in just before the
 * error occurred. In this case, the content of the buffer pointed to by `*buffer` is indeterminate
 * and it might not be null-terminated.
 *
 * The caller is expected to call `va_end()` with the `args` parameter and deallocate `*buffer`
 * with `SCU_FREE()` when no longer needed.
 *
 * @param[in, out] buffer   Dynamically allocated output buffer to write the formatted message to.
 *                          It is resized with `SCU_REALLOC()` as required.
 * @param[in, out] capacity Capacity of the dynamically allocated output buffer (including the
 *                          terminating `\0` byte), updated if `*buffer` is resized.
 * @param[in]      format   A null-terminated format string following the same conventions as the
 *                          standard `printf()` family of functions.
 * @param[in]      args     Any number of additional arguments to be formatted and written based on
 *                          the given format string.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `*capacity` is negative or if `*buffer` is a `nullptr`
 * and `*capacity` is not equal to zero (or vice versa), `SCU_ERROR_OUT_OF_MEMORY` if an
 * out-of-memory condition occurred, `SCU_ERROR_WRITING_BUFFER_FAILED` if writing to `*buffer`
 * failed and `SCU_ERROR_NONE` otherwise.
 */
SCUError scu_vrsnprintf(char** buffer, int64_t* capacity, const char* format, va_list args);

/**
 * @brief Appends a formatted string to a given dynamically allocated output buffer, resizing it as
 * required.
 *
 * @note `*buffer` is allowed to be a `nullptr`, in which case `*capacity` must be zero (and vice
 * versa). If `*buffer` is not a `nullptr`, it must have been allocated by `SCU_MALLOC()`,
 * `SCU_CALLOC()` or `SCU_REALLOC()` (or compatible functions these macros are implemented with,
 * which are the standard `malloc()`, `calloc()` and `realloc()` functions by default) and
 * `*capacity` must be greater than zero.
 *
 * On success, `*buffer` is resized as required to fit the formatted string, the new capacity is
 * stored in `*capacity` and `*buffer` is guaranteed to be null-terminated.
 *
 * @warning On failure, `*buffer` and `*capacity` remain in the state they were in just before the
 * error occurred. In this case, the content of the buffer pointed to by `*buffer` is indeterminate
 * and it might not be null-terminated.
 *
 * The caller is expected to deallocate `*buffer` with `SCU_FREE()` when no longer needed.
 *
 * @param[in, out] buffer   Dynamically allocated output buffer to write the formatted message to.
 *                          It is resized with `SCU_REALLOC()` as required.
 * @param[in, out] capacity Capacity of the dynamically allocated output buffer (including the
 *                          terminating `\0` byte), updated if `*buffer` is resized.
 * @param[in]      format   A null-terminated format string following the same conventions as the
 *                          standard `printf()` family of functions.
 * @param[in]      ...      Any number of additional arguments to be formatted and written based on
 *                          the given format string.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `*capacity` is negative or if `*buffer` is a `nullptr`
 * and `*capacity` is not equal to zero (or vice versa), `SCU_ERROR_OUT_OF_MEMORY` if an
 * out-of-memory condition occurred, `SCU_ERROR_WRITING_BUFFER_FAILED` if writing to `*buffer`
 * failed and `SCU_ERROR_NONE` otherwise.
 */
SCUError scu_rasnprintf(char** buffer, int64_t* capacity, const char* format, ...);

/**
 * @brief Appends a formatted string to a given dynamically allocated output buffer, resizing it as
 * required.
 *
 * @note `*buffer` is allowed to be a `nullptr`, in which case `*capacity` must be zero (and vice
 * versa). If `*buffer` is not a `nullptr`, it must have been allocated by `SCU_MALLOC()`,
 * `SCU_CALLOC()` or `SCU_REALLOC()` (or compatible functions these macros are implemented with,
 * which are the standard `malloc()`, `calloc()` and `realloc()` functions by default) and
 * `*capacity` must be greater than zero.
 *
 * On success, `*buffer` is resized as required to fit the formatted string, the new capacity is
 * stored in `*capacity` and `*buffer` is guaranteed to be null-terminated.
 *
 * @warning On failure, `*buffer` and `*capacity` remain in the state they were in just before the
 * error occurred. In this case, the content of the buffer pointed to by `*buffer` is indeterminate
 * and it might not be null-terminated.
 *
 * The caller is expected to call `va_end()` with the `args` parameter and deallocate `*buffer`
 * with `SCU_FREE()` when no longer needed.
 *
 * @param[in, out] buffer   Dynamically allocated output buffer to write the formatted message to.
 *                          It is resized with `SCU_REALLOC()` as required.
 * @param[in, out] capacity Capacity of the dynamically allocated output buffer (including the
 *                          terminating `\0` byte), updated if `*buffer` is resized.
 * @param[in]      format   A null-terminated format string following the same conventions as the
 *                          standard `printf()` family of functions.
 * @param[in]      args     Any number of additional arguments to be formatted and written based on
 *                          the given format string.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `*capacity` is negative or if `*buffer` is a `nullptr`
 * and `*capacity` is not equal to zero (or vice versa), `SCU_ERROR_OUT_OF_MEMORY` if an
 * out-of-memory condition occurred, `SCU_ERROR_WRITING_BUFFER_FAILED` if writing to `*buffer`
 * failed and `SCU_ERROR_NONE` otherwise.
 */
SCUError scu_vrasnprintf(char** buffer, int64_t* capacity, const char* format, va_list args);

#endif