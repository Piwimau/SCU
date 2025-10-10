#ifndef SCU_IO_H
#define SCU_IO_H

#include <stdarg.h>
#include <stdint.h>
#include "scu/error.h"

/** @brief Represents a file stream used to input and output data. */
typedef struct SCUFile SCUFile;

/** @brief Represents an origin for seeking within a file stream. */
typedef enum SCUSeekOrigin {

    /** @brief Indicates to seek from the beginning of the file stream. */
    SCU_SEEK_ORIGIN_SET,

    /**
     * @brief Indicates to seek from the current position of the file stream.
     */
    SCU_SEEK_ORIGIN_CUR,

    /** @brief Indicates to seek from the end of the file stream. */
    SCU_SEEK_ORIGIN_END

} SCUSeekOrigin;

/**
 * @brief Returns a pointer to a file stream associated with the standard input
 * stream.
 *
 * @note This function is an implementation detail and is not meant to be called
 * directly. Use the `SCU_STDIN` macro instead.
 *
 * @warning The returned file stream must not be modified or passed to
 * `scu_fclose()`.
 *
 * @return A pointer to a file stream associated with the standard input stream.
 */
SCUFile* scu_stdin();

/**
 * @brief Expands to an expression of type `SCUFile*` that is associated with
 * the standard input stream.
 *
 * @warning The file stream must not be modified or passed to `scu_fclose()`.
 */
#define SCU_STDIN scu_stdin()

/**
 * @brief Returns a pointer to a file stream associated with the standard output
 * stream.
 *
 * @note This function is an implementation detail and is not meant to be called
 * directly. Use the `SCU_STDOUT` macro instead.
 *
 * @warning The returned file stream must not be modified or passed to
 * `scu_fclose()`.
 *
 * @return A pointer to a file stream associated with the standard output
 * stream.
 */
SCUFile* scu_stdout();

/**
 * @brief Expands to an expression of type `SCUFile*` that is associated with
 * the standard output stream.
 *
 * @warning The file stream must not be modified or passed to `scu_fclose()`.
 */
#define SCU_STDOUT scu_stdout()

/**
 * @brief Returns a pointer to a file stream associated with the standard error
 * stream.
 *
 * @note This function is an implementation detail and is not meant to be called
 * directly. Use the `SCU_STDERR` macro instead.
 *
 * @warning The returned file stream must not be modified or passed to
 * `scu_fclose()`.
 *
 * @return A pointer to a file stream associated with the standard error stream.
 */
SCUFile* scu_stderr();

/**
 * @brief Expands to an expression of type `SCUFile*` that is associated with
 * the standard error stream.
 *
 * @warning The file stream must not be modified or passed to `scu_fclose()`.
 */
#define SCU_STDERR scu_stderr()

/**
 * @brief Opens a file with a specified name and mode.
 *
 * The `mode` string must be a valid `fopen()`-style mode string. The following
 * modes are supported:
 *
 * - `"r"`: Opens a file for reading. If the file does not exist, a failure
 *   occurs.
 *
 * - `"r+"`: Opens a file for reading and writing. If the file does not exist, a
 *   failure occurs.
 *
 * - `"w"`: Opens a file for writing. If the file already exists, its contents
 *   are overwritten. Otherwise, a new file is created.
 *
 * - `"w+"`: Opens a file for reading and writing. If the file already exists,
 *   its contents are overwritten. Otherwise, a new file is created.
 *
 * - `"a"`: Opens a file for appending. If the file does not exist, a new file
 *   is created.
 *
 * - `"a+"`: Opens a file for reading and appending. If the file does not exist,
 *   a new file is created.
 *
 * The mode flag `"b"` may optionally be specified to open the file in binary
 * mode, which disables special handling of certain bytes (e.g., newline
 * translation on Windows). Additionally, the mode flag `"x"` may optionally be
 * appended to `"w"` or `"w+"` specifiers, which causes this function to fail if
 * the file already exists (instead of simply overwriting its contents).
 *
 * @note The exact format of `name` is implementation-defined, and it does not
 * necessarily have to correspond to an actual file in the filesystem.
 *
 * This function dynamically allocates memory using `scu_malloc()`.
 *
 * @warning If the operation succeeds, the file stream returned via `*file` must
 * be closed with `scu_fclose()` to properly release any associated resources.
 *
 * The behavior is undefined if `mode` is not one of the supported mode strings
 * listed above.
 *
 * @param[out] file A pointer to a file stream associated with the opened file,
 *                  or `nullptr` on failure.
 * @param[in]  name The name of the file to open.
 * @param[in]  mode An `fopen()`-style mode string that specifies the mode in
 *                  which to open the file.
 * @return `SCU_ERROR_OPENING_FILE` if the file could not be opened,
 * `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_fopen(
    SCUFile* restrict* restrict file,
    const char* restrict name,
    const char* restrict mode
);

/**
 * @brief Creates and opens a temporary file.
 *
 * This function creates and opens a temporary file in binary update mode (as if
 * by calling `scu_fopen()` with the mode `"wb+"`). The name of the file is
 * guaranteed to be unique within the filesystem.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`.
 *
 * @warning If the operation succeeds, the file stream returned via `*file` must
 * be closed with `scu_fclose()` to properly release any associated resources.
 *
 * @param[out] file A pointer to a file stream associated with the temporary
 *                  file, or `nullptr` on failure.
 * @return `SCU_ERROR_OPENING_FILE` if an error occurred while creating or
 * opening the temporary file, `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory
 * condition occurred, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_fopentmp(SCUFile** file);

/**
 * @brief Reopens a file stream with a specified name and mode.
 *
 * This function first attempts to close the specified file stream (ignoring any
 * errors). Then, if `name` is not `nullptr`, it attempts to open the file with
 * the specified `name` and `mode` (as if by calling `scu_fopen()`). Otherwise,
 * it attempts to reopen the file associated with the specified file stream.
 *
 * The `mode` string must be a valid `fopen()`-style mode string. The following
 * modes are supported:
 *
 * - `"r"`: Opens a file for reading. If the file does not exist, a failure
 *   occurs.
 *
 * - `"r+"`: Opens a file for reading and writing. If the file does not exist, a
 *   failure occurs.
 *
 * - `"w"`: Opens a file for writing. If the file already exists, its contents
 *   are overwritten. Otherwise, a new file is created.
 *
 * - `"w+"`: Opens a file for reading and writing. If the file already exists,
 *   its contents are overwritten. Otherwise, a new file is created.
 *
 * - `"a"`: Opens a file for appending. If the file does not exist, a new file
 *   is created.
 *
 * - `"a+"`: Opens a file for reading and appending. If the file does not exist,
 *   a new file is created.
 *
 * The mode flag `"b"` may optionally be specified to open the file in binary
 * mode, which disables special handling of certain bytes (e.g., newline
 * translation on Windows). Additionally, the mode flag `"x"` may optionally be
 * appended to `"w"` or `"w+"` specifiers, which causes this function to fail if
 * the file already exists (instead of simply overwriting its contents).
 *
 * @note The exact format of `name` is implementation-defined, and it does not
 * necessarily have to correspond to an actual file in the filesystem.
 * Additionally, it is implementation-defined which mode changes are allowed
 * when `name` is `nullptr`.
 *
 * This function does not allocate a new `SCUFile` object, but modifies the
 * specified file stream in-place.
 *
 * @warning If the operation succeeds, and `file` is not one of the standard
 * streams `SCU_STDIN`, `SCU_STDOUT` or `SCU_STDERR`, the file stream must be
 * closed with `scu_fclose()` to properly release any associated resources.
 *
 * The behavior is undefined if `mode` is not one of the supported mode strings
 * listed above.
 *
 * @param[in, out] file The file stream to reopen.
 * @param[in]      name The name of the file to open. If equal to `nullptr`,
 *                      the function will attempt to reopen the file associated
 *                      with the specified file stream.
 * @param[in]      mode An `fopen()`-style mode string that specifies the mode
 *                      in which to open the file.
 * @return `SCU_ERROR_REOPENING_FILE` if the file stream could not be reopened,
 * or `SCU_ERROR_NONE` on success.
 */
SCUError scu_freopen(
    SCUFile* restrict file,
    const char* restrict name,
    const char* restrict mode
);

/**
 * @brief Closes a specified file stream and releases any associated resources.
 *
 * @warning The behavior is undefined if `file` is used after calling this
 * function.
 *
 * @param[in, out] file The file stream to close.
 * @return `SCU_ERROR_CLOSING_FILE` if the file stream could not be closed, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_fclose(SCUFile* file);

/**
 * @brief Writes any buffered data to the underlying file associated with a
 * specified file stream.
 *
 * @warning The behavior is undefined if `file` is an input stream or an update
 * stream on which the last operation was input.
 *
 * @param[in, out] file The file stream to flush. If equal to `nullptr`, all
 *                      open output streams are flushed.
 * @return `SCU_ERROR_FLUSHING_FILE` if the file stream could not be flushed, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_fflush(SCUFile* file);

/**
 * @brief Removes a file with a specified name.
 *
 * @note If the file is currently opened by any process, the behavior is
 * implementation-defined.
 *
 * @param[in] name The name of the file to remove.
 * @return `SCU_ERROR_REMOVING_FILE` if an error occurred while removing the
 * file, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_fremove(const char* name);

/**
 * @brief Renames a file.
 *
 * @note If a file with the new name already exists, the behavior is
 * implementation-defined.
 *
 * @param[in] oldName The current name of the file.
 * @param[in] newName The new name of the file.
 * @return `SCU_ERROR_RENAMING_FILE` if an error occurred while renaming the
 * file, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_frename(const char* oldName, const char* newName);

/**
 * @brief Reads `count` objects of size `size` from a specified file stream into
 * a buffer.
 *
 * @note The `buffer` is reinterpreted as a contiguous array of `count * size`
 * bytes.
 *
 * If `count` or `size` is zero, `buffer` is ignored (it may even be a
 * `nullptr`), `*read` is set to zero (if `read` is not `nullptr`) and the
 * function returns `SCU_ERROR_NONE`.
 *
 * @warning If an error occurs while reading from the specified file stream, the
 * value of the file position indicator is indeterminate. The same holds true
 * for the value of an object that is only partially read.
 *
 * @param[in, out] file   The file stream to read from.
 * @param[out]     buffer The buffer to write the data to.
 * @param[in]      count  The number of objects to read.
 * @param[in]      size   The size of each object (in bytes).
 * @param[out]     read   The number of objects read, which may be less than
 *                        `count` if the end-of-file-condition is reached or an
 *                        error occurs. If `read` is `nullptr`, it is ignored.
 * @return `SCU_ERROR_END_OF_FILE` if the end-of-file condition is reached
 * before `count` objects are read, `SCU_ERROR_READING_FILE` if an error
 * occurred while reading from the specified file stream, or `SCU_ERROR_NONE` on
 * success.
 */
SCUError scu_fread(
    SCUFile* restrict file,
    void* restrict buffer,
    int64_t count,
    int64_t size,
    int64_t* restrict read
);

/**
 * @brief Reads `count` objects of size `size` from the standard input stream
 * into a buffer.
 *
 * @note The `buffer` is reinterpreted as a contiguous array of `count * size`
 * bytes.
 *
 * If `count` or `size` is zero, `buffer` is ignored (it may even be a
 * `nullptr`), `*read` is set to zero (if `read` is not `nullptr`) and the
 * function returns `SCU_ERROR_NONE`.
 *
 * Calling this function is equivalent to calling `scu_fread(SCU_STDIN, buffer,
 * count, size, read)`.
 *
 * @warning If an error occurs while reading from the standard input stream, the
 * value of the file position indicator is indeterminate. The same holds true
 * for the value of an object that is only partially read.
 *
 * @param[out] buffer The buffer to write the data to.
 * @param[in]  count  The number of objects to read.
 * @param[in]  size   The size of each object (in bytes).
 * @param[out] read   The number of objects read, which may be less than `count`
 *                    if the end-of-file-condition is reached or an error
 *                    occurs. If `read` is `nullptr`, it is ignored.
 * @return `SCU_ERROR_END_OF_FILE` if the end-of-file condition is reached
 * before `count` objects are read, `SCU_ERROR_READING_FILE` if an error
 * occurred while reading from the standard input stream, or `SCU_ERROR_NONE` on
 * success.
 */
SCUError scu_read(
    void* restrict buffer,
    int64_t count,
    int64_t size,
    int64_t* restrict read
);

/**
 * @brief Writes `count` objects of size `size` from a buffer to a specified
 * file stream.
 *
 * @note The `buffer` is reinterpreted as a contiguous array of `count * size`
 * bytes.
 *
 * If `count` or `size` is zero, `buffer` is ignored (it may even be a
 * `nullptr`), `*written` is set to zero (if `written` is not `nullptr`) and the
 * function returns `SCU_ERROR_NONE`.
 *
 * @warning If an error occurs, the value of the file position indicator of the
 * specified file stream is indeterminate.
 *
 * @param[in, out] file    The file stream to write to.
 * @param[in]      buffer  The buffer to read the data from.
 * @param[in]      count   The number of objects to write.
 * @param[in]      size    The size of each object (in bytes).
 * @param[out]     written The number of objects written, which may be less than
 *                         `count` if an error occurs. If `written` is
 *                         `nullptr`, it is ignored.
 * @return `SCU_ERROR_WRITING_FILE` if an error occurred while writing to the
 * specified file stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_fwrite(
    SCUFile* restrict file,
    const void* restrict buffer,
    int64_t count,
    int64_t size,
    int64_t* restrict written
);

/**
 * @brief Writes `count` objects of size `size` from a buffer to the standard
 * output stream.
 *
 * @note The `buffer` is reinterpreted as a contiguous array of `count * size`
 * bytes.
 *
 * If `count` or `size` is zero, `buffer` is ignored (it may even be a
 * `nullptr`), `*written` is set to zero (if `written` is not `nullptr`) and the
 * function returns `SCU_ERROR_NONE`.
 *
 * Calling this function is equivalent to calling `scu_fwrite(SCU_STDOUT,
 * buffer, count, size, written)`.
 *
 * @warning If an error occurs, the value of the file position indicator of the
 * standard output stream is indeterminate.
 *
 * @param[in]  buffer  The buffer to read the data from.
 * @param[in]  count   The number of objects to write.
 * @param[in]  size    The size of each object (in bytes).
 * @param[out] written The number of objects written, which may be less than
 *                     `count` if an error occurs. If `written` is `nullptr`, it
 *                     is ignored.
 * @return `SCU_ERROR_WRITING_FILE` if an error occurred while writing to the
 * standard output stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_write(
    const void* restrict buffer,
    int64_t count,
    int64_t size,
    int64_t* restrict written
);

/**
 * @brief Reads a single byte from a specified file stream.
 *
 * @param[in, out] file The file stream to read from.
 * @param[out]     c    The byte read from the specified file stream, or a null
 *                      byte ('\0') on failure.
 * @return `SCU_ERROR_END_OF_FILE` if the end-of-file condition is reached
 * before a byte is read, `SCU_ERROR_READING_FILE` if an error occurred while
 * reading from the specified file stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_freadc(SCUFile* restrict file, char* restrict c);

/**
 * @brief Reads a single byte from the standard input stream.
 *
 * Calling this function is equivalent to calling `scu_freadc(SCU_STDIN, c)`.
 *
 * @param[out] c The byte read from the standard input stream, or a null byte
 *               ('\0') on failure.
 * @return `SCU_ERROR_END_OF_FILE` if the end-of-file condition is reached
 * before a byte is read, `SCU_ERROR_READING_FILE` if an error occurred while
 * reading from the standard input stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_readc(char* c);

/**
 * @brief Writes a single byte to a specified file stream.
 *
 * @param[in, out] file The file stream to write to.
 * @param[in]      c    The byte to write.
 * @return `SCU_ERROR_WRITING_FILE` if an error occurred while writing to the
 * specified file stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_fwritec(SCUFile* file, char c);

/**
 * @brief Writes a single byte to the standard output stream.
 *
 * @note Calling this function is equivalent to calling `scu_fwritec(SCU_STDOUT,
 * c)`.
 *
 * @param[in] c The byte to write.
 * @return `SCU_ERROR_WRITING_FILE` if an error occurred while writing to the
 * standard output stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_writec(char c);

/**
 * @brief Pushes a single byte back into a specified file stream, such that
 * a subsequent read operation will return that byte.
 *
 * @note Calls to repositioning functions such as `scu_fseek()` and
 * `scu_frewind()` discard the effects of `scu_funreadc()`.
 *
 * Multiple calls to `scu_funreadc()` without an intervening read operation or
 * repositioning of the file stream may fail, as the size of the pushback buffer
 * is implementation-defined and only guaranteed to be at least one. If multiple
 * calls are successful, subsequent reads will return the pushed-back bytes in
 * reverse order.
 *
 * A successful call to `scu_funreadc()` clears the end-of-file indicator for
 * the specified file stream. Additionally, for binary streams, the file
 * position indicator is decremented by one. For text streams, the file position
 * indicator is decremented in an unspecified manner. However, it is guaranteed
 * that after all pushed-back bytes have been read, the file position indicator
 * will be equal to the original position before the call to `scu_funreadc()`.
 *
 * @warning The behavior is undefined if the file position indicator is zero
 * (i.e., no bytes have been read from the specified file stream yet).
 *
 * @param[in, out] file The file stream to push the byte back into.
 * @param[in]      c    The byte to push back.
 * @return `SCU_ERROR_WRITING_FILE` if the byte could not be pushed back, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_funreadc(SCUFile* file, char c);

/**
 * @brief Reads a byte string from a specified file stream.
 *
 * This function reads up to `size - 1` bytes from the specified file stream
 * into `buffer` and terminates it with a null byte.
 *
 * @note If `size` is zero, `buffer` is ignored (it may even be a `nullptr`) and
 * the function returns `SCU_ERROR_NONE`.
 *
 * If `size` is greater than or equal to one, `buffer` is guaranteed to be
 * null-terminated, even if the end-of-file condition is reached before any
 * bytes are read or if an error occurs while reading from the specified file
 * stream.
 *
 * @param[in, out] file   The file stream to read from.
 * @param[out]     buffer The buffer to write the data to.
 * @param[in]      size   The size of the buffer (in bytes, including the
 *                        terminating null byte).
 * @return `SCU_ERROR_END_OF_FILE` if the end-of-file condition is reached
 * before any bytes are read, `SCU_ERROR_READING_FILE` if an error occurred
 * while reading from the specified file stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_freads(
    SCUFile* restrict file,
    char* restrict buffer,
    int64_t size
);

/**
 * @brief Reads a byte string from the standard input stream.
 *
 * This function reads up to `size - 1` bytes from the standard input stream
 * into `buffer` and terminates it with a null byte.
 *
 * @note If `size` is zero, `buffer` is ignored (it may even be a `nullptr`) and
 * the function returns `SCU_ERROR_NONE`.
 *
 * If `size` is greater than or equal to one, `buffer` is guaranteed to be
 * null-terminated, even if the end-of-file condition is reached before any
 * bytes are read or if an error occurs while reading from the specified file
 * stream.
 *
 * Calling this function is equivalent to calling `scu_freads(SCU_STDIN, buffer,
 * size)`.
 *
 * @param[out] buffer The buffer to write the data to.
 * @param[in]  size   The size of the buffer (in bytes, including the
 *                    terminating null byte).
 * @return `SCU_ERROR_END_OF_FILE` if the end-of-file condition is reached
 * before any bytes are read, `SCU_ERROR_READING_FILE` if an error occurred
 * while reading from the standard input stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_reads(char* buffer, int64_t size);

/**
 * @brief Writes a byte string to a specified file stream.
 *
 * This function writes the null-terminated byte string pointed to by `buffer`
 * to the specified file stream, excluding the terminating null byte.
 *
 * @param[in, out] file   The file stream to write to.
 * @param[in]      buffer The null-terminated byte string to write.
 * @return `SCU_ERROR_WRITING_FILE` if an error occurred while writing to the
 * specified file stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_fwrites(SCUFile* restrict file, const char* restrict buffer);

/**
 * @brief Writes a byte string to the standard output stream.
 *
 * This function writes the null-terminated byte string pointed to by `buffer`
 * to the standard output stream, excluding the terminating null byte.
 *
 * @note Calling this function is equivalent to calling `scu_fwrites(SCU_STDOUT,
 * buffer)`.
 *
 * @param[in] buffer The null-terminated byte string to write.
 * @return `SCU_ERROR_WRITING_FILE` if an error occurred while writing to the
 * standard output stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_writes(const char* buffer);

/**
 * @brief Reads a single line from a specified file stream.
 *
 * This function reads a single line from the specified file stream into
 * `*buffer` and terminates it with a null byte. The buffer is dynamically
 * reallocated using `scu_realloc()` to fit the entire line (including the
 * newline (if present) and the terminating null byte). The new size is
 * reflected in `*size`.
 *
 * @note If `*size` is zero, `*buffer` must be a `nullptr` (and vice versa). In
 * this case, the function allocates a buffer using `scu_realloc()` and an
 * unspecified initial size.
 *
 * If `*size` is greater than or equal to one and no out-of-memory condition
 * occurs, `*buffer` is guaranteed to be null-terminated, even if the
 * end-of-file condition is reached before any bytes are read or if an error
 * occurs while reading from the specified file stream.
 *
 * @warning If `*buffer` is not a `nullptr`, it must have been allocated using
 * `scu_malloc()`, `scu_calloc()` or `scu_realloc()` (or the underlying
 * allocator used by these functions). The caller is expected to free `*buffer`
 * with `scu_free()` when it is no longer needed.
 *
 * @param[in, out] file   The file stream to read from.
 * @param[in, out] buffer A pointer to a buffer to write the data to.
 * @param[in, out] size   A pointer to the size of the buffer (in bytes,
 *                        including the terminating null byte).
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * `SCU_ERROR_END_OF_FILE` if the end-of-file condition is reached before any
 * bytes are read, `SCU_ERROR_READING_FILE` if an error occurred while reading
 * from the specified file stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_freadln(
    SCUFile* restrict file,
    char** restrict buffer,
    int64_t* restrict size
);

/**
 * @brief Reads a single line from the standard input stream.
 *
 * This function reads a single line from the standard input stream into
 * `*buffer` and terminates it with a null byte. The buffer is dynamically
 * reallocated using `scu_realloc()` to fit the entire line (including the
 * newline (if present) and the terminating null byte). The new size is
 * reflected in `*size`.
 *
 * @note If `*size` is zero, `*buffer` must be a `nullptr` (and vice versa). In
 * this case, the function allocates a buffer using `scu_malloc()` and an
 * unspecified initial size.
 *
 * If `*size` is greater than or equal to one, `*buffer` is guaranteed to be
 * null-terminated, even if the end-of-file condition is reached before any
 * bytes are read or if an error occurs.
 *
 * Calling this function is equivalent to calling `scu_freadln(SCU_STDIN,
 * buffer, size)`.
 *
 * @warning If `*buffer` is not a `nullptr`, it must have been allocated using
 * `scu_malloc()`, `scu_calloc()` or `scu_realloc()` (or the underlying
 * allocator used by these functions). The caller is expected to free `*buffer`
 * with `scu_free()` when it is no longer needed.
 *
 * @param[in, out] buffer A pointer to a buffer to write the data to.
 * @param[in, out] size   A pointer to the size of the buffer (in bytes,
 *                        including the terminating null byte).
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * `SCU_ERROR_END_OF_FILE` if the end-of-file condition is reached before any
 * bytes are read, `SCU_ERROR_READING_FILE` if an error occurred while reading
 * from the standard input stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_readln(char** restrict buffer, int64_t* restrict size);

/**
 * @brief Writes a byte string followed by a newline to a specified file stream.
 *
 * This function writes the null-terminated byte string pointed to by `buffer`
 * to the specified file stream, excluding the terminating null byte.
 * Additionally, a newline byte is written after the string.
 *
 * @param[in, out] file   The file stream to write to.
 * @param[in]      buffer The null-terminated byte string to write.
 * @return `SCU_ERROR_WRITING_FILE` if an error occurred while writing to the
 * specified file stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_fwriteln(SCUFile* restrict file, const char* restrict buffer);

/**
 * @brief Writes a byte string followed by a newline to the standard output
 * stream.
 *
 * This function writes the null-terminated byte string pointed to by `buffer`
 * to the standard output stream, excluding the terminating null byte.
 * Additionally, a newline byte is written after the string.
 *
 * @note Calling this function is equivalent to calling
 * `scu_fwriteln(SCU_STDOUT, buffer)`.
 *
 * @param[in] buffer The null-terminated byte string to write.
 * @return `SCU_ERROR_WRITING_FILE` if an error occurred while writing to the
 * standard output stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_writeln(const char* buffer);

/**
 * @brief Reads formatted input from a specified file stream.
 *
 * This function reads data from the specified file stream and interprets it
 * according to a `vfscanf()`-style format string. The read values are stored in
 * the locations pointed to by the variable argument list. The number of
 * arguments read is reflected in `*read` (if `read` is not `nullptr`).
 *
 * @warning The caller is expected to call `va_end()` on `args` after this
 * function returns.
 *
 * @param[in, out] file   The file stream to read from.
 * @param[out]     read   The number of arguments read, or -1 on failure. If
 *                        `read` is `nullptr`, it is ignored.
 * @param[in]      format A `vfscanf()`-style format string that specifies how
 *                        to interpret the input.
 * @param[out]     args   A variable argument list containing pointers to
 *                        locations where the read values should be stored.
 * @return `SCU_ERROR_END_OF_FILE` if the end-of-file condition is reached
 * before any argument is read, `SCU_ERROR_READING_FILE` if an error occurred
 * while reading from the specified file stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_vfscanf(
    SCUFile* restrict file,
    int64_t* restrict read,
    const char* restrict format,
    va_list args
);

/**
 * @brief Reads formatted input from a specified file stream.
 *
 * This function reads data from the specified file stream and interprets it
 * according to an `fscanf()`-style format string. The read values are stored in
 * the locations pointed to by the variable argument list. The number of
 * arguments read is reflected in `*read` (if `read` is not `nullptr`).
 *
 * @param[in, out] file   The file stream to read from.
 * @param[out]     read   The number of arguments read, or -1 on failure. If
 *                        `read` is `nullptr`, it is ignored.
 * @param[in]      format An `fscanf()`-style format string that specifies how
 *                        to interpret the input.
 * @param[out]     ...    A variable argument list containing pointers to
 *                        locations where the read values should be stored.
 * @return `SCU_ERROR_END_OF_FILE` if the end-of-file condition is reached
 * before any argument is read, `SCU_ERROR_READING_FILE` if an error occurred
 * while reading from the specified file stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_fscanf(
    SCUFile* restrict file,
    int64_t* restrict read,
    const char* restrict format,
    ...
);

/**
 * @brief Reads formatted input from the standard input stream.
 *
 * This function reads data from the standard input stream and interprets it
 * according to a `vscanf()`-style format string. The read values are stored in
 * the locations pointed to by the variable argument list. The number of
 * arguments read is reflected in `*read` (if `read` is not `nullptr`).
 *
 * @note Calling this function is equivalent to calling `scu_vfscanf(SCU_STDIN,
 * read, format, args)`.
 *
 * @warning The caller is expected to call `va_end()` on `args` after this
 * function returns.
 *
 * @param[out] read   The number of arguments read, or -1 on failure. If `read`
 *                    is `nullptr`, it is ignored.
 * @param[in]  format A `vscanf()`-style format string that specifies how to
 *                    interpret the input.
 * @param[out] args   A variable argument list containing pointers to locations
 *                    where the read values should be stored.
 * @return `SCU_ERROR_END_OF_FILE` if the end-of-file condition is reached
 * before any argument is read, `SCU_ERROR_READING_FILE` if an error occurred
 * while reading from the standard input stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_vscanf(
    int64_t* restrict read,
    const char* restrict format,
    va_list args
);

/**
 * @brief Reads formatted input from the standard input stream.
 *
 * This function reads data from the standard input stream and interprets it
 * according to a `scanf()`-style format string. The read values are stored in
 * the locations pointed to by the variable argument list. The number of
 * arguments read is reflected in `*read` (if `read` is not `nullptr`).
 *
 * @note Calling this function is equivalent to calling `scu_fscanf(SCU_STDIN,
 * read, format, ...)`.
 *
 * @param[out] read   The number of arguments read, or -1 on failure. If `read`
 *                    is `nullptr`, it is ignored.
 * @param[in]  format A `scanf()`-style format string that specifies how to
 *                    interpret the input.
 * @param[out] ...    A variable argument list containing pointers to locations
 *                    where the read values should be stored.
 * @return `SCU_ERROR_END_OF_FILE` if the end-of-file condition is reached
 * before any argument is read, `SCU_ERROR_READING_FILE` if an error occurred
 * while reading from the standard input stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_scanf(int64_t* restrict read, const char* restrict format, ...);

/**
 * @brief Reads formatted input from a byte string.
 *
 * This function reads data from the specified byte string and interprets it
 * according to a `vsscanf()`-style format string. The read values are stored in
 * the locations pointed to by the variable argument list. The number of
 * arguments read is reflected in `*read` (if `read` is not `nullptr`).
 *
 * @warning The caller is expected to call `va_end()` on `args` after this
 * function returns.
 *
 * @param[in]  buffer The null-terminated byte string to read from.
 * @param[out] read   The number of arguments read, or -1 on failure. If `read`
 *                    is `nullptr`, it is ignored.
 * @param[in]  format A `vsscanf()`-style format string that specifies how to
 *                    interpret the input.
 * @param[out] args   A variable argument list containing pointers to locations
 *                    where the read values should be stored.
 * @return `SCU_ERROR_READING_BUFFER` if the end of the byte string is reached
 * before any argument is read or an error occurs, or `SCU_ERROR_NONE` on
 * success.
 */
SCUError scu_vsscanf(
    const char* restrict buffer,
    int64_t* restrict read,
    const char* restrict format,
    va_list args
);

/**
 * @brief Reads formatted input from a byte string.
 *
 * This function reads data from the specified byte string and interprets it
 * according to an `sscanf()`-style format string. The read values are stored in
 * the locations pointed to by the variable argument list. The number of
 * arguments read is reflected in `*read` (if `read` is not `nullptr`).
 *
 * @param[in]  buffer The null-terminated byte string to read from.
 * @param[out] read   The number of arguments read, or -1 on failure. If `read`
 *                    is `nullptr`, it is ignored.
 * @param[in]  format An `sscanf()`-style format string that specifies how to
 *                    interpret the input.
 * @param[out] ...    A variable argument list containing pointers to locations
 *                    where the read values should be stored.
 * @return `SCU_ERROR_READING_BUFFER` if the end of the byte string is reached
 * before any argument is read or an error occurs, or `SCU_ERROR_NONE` on
 * success.
 */
SCUError scu_sscanf(
    const char* restrict buffer,
    int64_t* restrict read,
    const char* restrict format,
    ...
);

/**
 * @brief Writes formatted output to a specified file stream.
 *
 * This function writes data to the specified file stream according to a
 * `vfprintf()`-style format string. The values to be written are taken from the
 * variable argument list. The number of bytes written is reflected in
 * `*written` (if `written` is not `nullptr`).
 *
 * @warning The caller is expected to call `va_end()` on `args` after this
 * function returns.
 *
 * @param[in, out] file    The file stream to write to.
 * @param[out]     written The number of bytes written, or -1 on failure. If
 *                         written is `nullptr`, it is ignored.
 * @param[in]      format  A `vfprintf()`-style format string that specifies how
 *                         to format the output.
 * @param[in]      args    A variable argument list containing the values to be
 *                         written.
 * @return `SCU_ERROR_WRITING_FILE` if an error occurred while writing to the
 * specified file stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_vfprintf(
    SCUFile* restrict file,
    int64_t* restrict written,
    const char* restrict format,
    va_list args
);

/**
 * @brief Writes formatted output to a specified file stream.
 *
 * This function writes data to the specified file stream according to an
 * `fprintf()`-style format string. The values to be written are taken from the
 * variable argument list. The number of bytes written is reflected in
 * `*written` (if `written` is not `nullptr`).
 *
 * @param[in, out] file    The file stream to write to.
 * @param[out]     written The number of bytes written, or -1 on failure. If
 *                         written is `nullptr`, it is ignored.
 * @param[in]      format  An `fprintf()`-style format string that specifies how
 *                         to format the output.
 * @param[in]      ...     A variable argument list containing the values to be
 *                         written.
 * @return `SCU_ERROR_WRITING_FILE` if an error occurred while writing to the
 * specified file stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_fprintf(
    SCUFile* restrict file,
    int64_t* restrict written,
    const char* restrict format,
    ...
);

/**
 * @brief Writes formatted output to the standard output stream.
 *
 * This function writes data to the standard output stream according to a
 * `vprintf()`-style format string. The values to be written are taken from the
 * variable argument list. The number of bytes written is reflected in
 * `*written` (if `written` is not `nullptr`).
 *
 * @note Calling this function is equivalent to calling
 * `scu_vfprintf(SCU_STDOUT, written, format, args)`.
 *
 * @warning The caller is expected to call `va_end()` on `args` after this
 * function returns.
 *
 * @param[out] written The number of bytes written, or -1 on failure. If
 *                     `written` is `nullptr`, it is ignored.
 * @param[in]  format  A `vprintf()`-style format string that specifies how to
 *                     format the output.
 * @param[in]  args    A variable argument list containing the values to be
 *                     written.
 * @return `SCU_ERROR_WRITING_FILE` if an error occurred while writing to the
 * standard output stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_vprintf(
    int64_t* restrict written,
    const char* restrict format,
    va_list args
);

/**
 * @brief Writes formatted output to the standard output stream.
 *
 * This function writes data to the standard output stream according to a
 * `printf()`-style format string. The values to be written are taken from the
 * variable argument list. The number of bytes written is reflected in
 * `*written` (if `written` is not `nullptr`).
 *
 * @note Calling this function is equivalent to calling `scu_fprintf(SCU_STDOUT,
 * written, format, ...)`.
 *
 * @param[out] written The number of bytes written, or -1 on failure. If
 *                     `written` is `nullptr`, it is ignored.
 * @param[in]  format  A `printf()`-style format string that specifies how to
 *                     format the output.
 * @param[in]  ...     A variable argument list containing the values to be
 *                     written.
 * @return `SCU_ERROR_WRITING_FILE` if an error occurred while writing to the
 * standard output stream, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_printf(
    int64_t* restrict written,
    const char* restrict format,
    ...
);

/**
 * @brief Writes formatted output to a byte string.
 *
 * This function writes up to `size - 1` bytes to the byte string pointed to by
 * `buffer` and terminates it with a null byte. The output is formatted
 * according to a `vsnprintf()`-style format string. The values to be written
 * are taken from the variable argument list. The number of bytes written
 * (excluding the terminating null byte) is reflected in `*written` (if
 * `written` is not `nullptr`). If `buffer` is truncated due to `size` and
 * `written` is not `nullptr`, `*written` instead contains the number of
 * bytes (excluding the terminating null byte) that would have been
 * written if `size` had been sufficiently large.
 *
 * @note If `size` is zero, `buffer` is ignored (it may even be a `nullptr`). In
 * this case, the function still computes the number of bytes (excluding the
 * terminating null byte) that would have been written if `size` had been
 * sufficiently large, and reflects this in `*written` (if `written` is not
 * `nullptr`).
 *
 * If `size` is greater than or equal to one, `buffer` is guaranteed to be
 * null-terminated, even if an error occurs.
 *
 * @warning The caller is expected to call `va_end()` on `args` after this
 * function returns.
 *
 * @param[out] buffer  The buffer to write the data to.
 * @param[in]  size    The size of the buffer (in bytes, including the
 *                     terminating null byte).
 * @param[out] written The number of bytes written (excluding the terminating
 *                     null byte), or the number of bytes that would have been
 *                     written if `size` had been sufficiently large, or -1 on
 *                     failure. If `written` is `nullptr`, it is ignored.
 * @param[in] format   A `vsnprintf()`-style format string that specifies how to
 *                     format the output.
 * @param[in] args     A variable argument list containing the values to be
 *                     written.
 * @return `SCU_ERROR_WRITING_BUFFER` if an error occurred while writing to the
 * byte string, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_vsnprintf(
    char* restrict buffer,
    int64_t size,
    int64_t* restrict written,
    const char* restrict format,
    va_list args
);

/**
 * @brief Writes formatted output to a byte string.
 *
 * This function writes up to `size - 1` bytes to the byte string pointed to by
 * `buffer` and terminates it with a null byte. The output is formatted
 * according to an `snprintf()`-style format string. The values to be written
 * are taken from the variable argument list. The number of bytes written
 * (excluding the terminating null byte) is reflected in `*written` (if
 * `written` is not `nullptr`). If `buffer` is truncated due to `size` and
 * `written` is not `nullptr`, `*written` instead contains the number of
 * bytes (excluding the terminating null byte) that would have been
 * written if `size` had been sufficiently large.
 *
 * @note If `size` is zero, `buffer` is ignored (it may even be a `nullptr`). In
 * this case, the function still computes the number of bytes (excluding
 * the terminating null byte) that would have been written if `size` had
 * been sufficiently large, and reflects this in `*written` (if `written` is not
 * `nullptr`).
 *
 * If `size` is greater than or equal to one, `buffer` is guaranteed to be
 * null-terminated, even if an error occurs.
 *
 * @param[out] buffer  The buffer to write the data to.
 * @param[in]  size    The size of the buffer (in bytes, including the
 *                     terminating null byte).
 * @param[out] written The number of bytes written (excluding the terminating
 *                     null byte), or the number of bytes that would have been
 *                     written if `size` had been sufficiently large, or -1 on
 *                     failure. If `written` is `nullptr`, it is ignored.
 * @param[in] format   An `snprintf()`-style format string that specifies how to
 *                     format the output.
 * @param[in] ...      A variable argument list containing the values to be
 *                     written.
 * @return `SCU_ERROR_WRITING_BUFFER` if an error occurred while writing to the
 * byte string, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_snprintf(
    char* restrict buffer,
    int64_t size,
    int64_t* restrict written,
    const char* restrict format,
    ...
);

/**
 * @brief Writes formatted output to a dynamically allocated byte string.
 *
 * This function writes a formatted string to a dynamically allocated buffer
 * according to a `vsnprintf()`-style format string. The buffer is reallocated
 * using `scu_realloc()` as needed to fit the entire output (including the
 * terminating null byte). The pointer to the buffer is stored in `*buffer`, and
 * its size (in bytes, including the terminating null byte) is stored in
 * `*size`. The number of bytes written (excluding the terminating null byte) is
 * reflected in `*written` (if `written` is not `nullptr`).
 *
 * @note If `*size` is zero, `*buffer` must be a `nullptr` (and vice versa). In
 * this case, the function allocates a buffer using `scu_realloc()`.
 *
 * If `*size` is greater than or equal to one and no out-of-memory condition
 * occurs, `*buffer` is guaranteed to be null-terminated.
 *
 * @warning If `*buffer` is not a `nullptr`, it must have been allocated using
 * `scu_malloc()`, `scu_calloc()` or `scu_realloc()` (or the underlying
 * allocator used by these functions). The caller is expected to free `*buffer`
 * with `scu_free()` when it is no longer needed.
 *
 * The caller is expected to call `va_end()` on `args` after this function
 * returns.
 *
 * @param[in, out] buffer  A pointer to a buffer to write the data to.
 * @param[in, out] size    A pointer to the size of the buffer (in bytes,
 *                         including the terminating null byte).
 * @param[out]     written The number of bytes written (excluding the
 *                         terminating null byte), or -1 on failure. If
 *                         `written` is `nullptr`, it is ignored.
 * @param[in]      format  A `vsnprintf()`-style format string that specifies
 *                         how to format the output.
 * @param[in]      args    A variable argument list containing the values to be
 *                         written.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * `SCU_ERROR_WRITING_BUFFER` if an error occurred while writing to the byte
 * string, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_vrsnprintf(
    char** restrict buffer,
    int64_t* restrict size,
    int64_t* restrict written,
    const char* restrict format,
    va_list args
);

/**
 * @brief Writes formatted output to a dynamically allocated byte string.
 *
 * This function writes a formatted string to a dynamically allocated buffer
 * according to an `snprintf()`-style format string. The buffer is reallocated
 * using `scu_realloc()` as needed to fit the entire output (including the
 * terminating null byte). The pointer to the buffer is stored in `*buffer`, and
 * its size (in bytes, including the terminating null byte) is stored in
 * `*size`. The number of bytes written (excluding the terminating null bytes)
 * is reflected in `*written` (if `written` is not `nullptr`).
 *
 * @note If `*size` is zero, `*buffer` must be a `nullptr` (and vice versa). In
 * this case, the function allocates a buffer using `scu_realloc()`.
 *
 * If `*size` is greater than or equal to one and no out-of-memory condition
 * occurs, `*buffer` is guaranteed to be null-terminated.
 *
 * @warning If `*buffer` is not a `nullptr`, it must have been allocated using
 * `scu_malloc()`, `scu_calloc()` or `scu_realloc()` (or the underlying
 * allocator used by these functions). The caller is expected to free `*buffer`
 * with `scu_free()` when it is no longer needed.
 *
 * @param[in, out] buffer  A pointer to a buffer to write the data to.
 * @param[in, out] size    A pointer to the size of the buffer (in bytes,
 *                         including the terminating null byte).
 * @param[out]     written The number of bytes written (excluding the
 *                         terminating null byte), or -1 on failure. If
 *                         `written` is `nullptr`, it is ignored.
 * @param[in]      format  An `snprintf()`-style format string that specifies
 *                         how to format the output.
 * @param[in]      ...     A variable argument list containing the values to be
 *                         written.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * `SCU_ERROR_WRITING_BUFFER` if an error occurred while writing to the byte
 * string, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_rsnprintf(
    char** restrict buffer,
    int64_t* restrict size,
    int64_t* restrict written,
    const char* restrict format,
    ...
);

/**
 * @brief Appends formatted output to a dynamically allocated byte string.
 *
 * This function appends a formatted string to a dynamically allocated,
 * null-terminated buffer according to a `vsnprintf()`-style format string. The
 * buffer is reallocated using `scu_realloc()` as needed to fit the entire
 * output (including the terminating null byte). The pointer to the buffer is
 * stored in `*buffer`, and its size (in bytes, including the terminating null
 * byte) is stored in `*size`. The number of bytes written (excluding the
 * terminating null byte) is reflected in `*written` (if `written` is not
 * `nullptr`).
 *
 * @note If `*size` is zero, `*buffer` must be a `nullptr` (and vice versa). In
 * this case, the function allocates a buffer using `scu_realloc()`.
 *
 * If `*size` is greater than or equal to one and no out-of-memory condition
 * occurs, `*buffer` is guaranteed to be null-terminated.
 *
 * @warning If `*buffer` is not a `nullptr`, it must be null-terminated and have
 * been allocated using `scu_malloc()`, `scu_calloc()` or `scu_realloc()` (or
 * the underlying allocator used by these functions). The caller is expected to
 * free `*buffer` with `scu_free()` when it is no longer needed.
 *
 * The caller is expected to call `va_end()` on `args` after this function
 * returns.
 *
 * @param[in, out] buffer  A pointer to a null-terminated buffer to append the
 *                         data to.
 * @param[in, out] size    A pointer to the size of the buffer (in bytes,
 *                         including the terminating null byte).
 * @param[out]     written The number of bytes written (excluding the
 *                         terminating null byte), or -1 on failure. If
 *                         `written` is `nullptr`, it is ignored.
 * @param[in]      format  A `vsnprintf()`-style format string that specifies
 *                         how to format the output.
 * @param[in]      args    A variable argument list containing the values to be
 *                         written.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * `SCU_ERROR_WRITING_BUFFER` if an error occurred while appending to the byte
 * string, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_vrasnprintf(
    char** restrict buffer,
    int64_t* restrict size,
    int64_t* restrict written,
    const char* restrict format,
    va_list args
);

/**
 * @brief Appends formatted output to a dynamically allocated byte string.
 *
 * This function appends a formatted string to a dynamically allocated,
 * null-terminated buffer according to an `snprintf()`-style format string. The
 * buffer is reallocated using `scu_realloc()` as needed to fit the entire
 * output (including the terminating null byte). The pointer to the buffer is
 * stored in `*buffer`, and its size (in bytes, including the terminating null
 * byte) is stored in `*size`. The number of bytes written (excluding the
 * terminating null byte) is reflected in `*written` (if `written` is not
 * `nullptr`).
 *
 * @note If `*size` is zero, `*buffer` must be a `nullptr` (and vice versa). In
 * this case, the function allocates a buffer using `scu_realloc()`.
 *
 * If `*size` is greater than or equal to one and no out-of-memory condition
 * occurs, `*buffer` is guaranteed to be null-terminated.
 *
 * @warning If `*buffer` is not a `nullptr`, it must be null-terminated and have
 * been allocated using `scu_malloc()`, `scu_calloc()` or `scu_realloc()` (or
 * the underlying allocator used by these functions). The caller is expected to
 * free `*buffer` with `scu_free()` when it is no longer needed.
 *
 * @param[in, out] buffer  A pointer to a null-terminated buffer to append the
 *                         data to.
 * @param[in, out] size    A pointer to the size of the buffer (in bytes,
 *                         including the terminating null byte).
 * @param[out]     written The number of bytes written (excluding the
 *                         terminating null byte), or -1 on failure. If
 *                         `written` is `nullptr`, it is ignored.
 * @param[in]      format  An `snprintf()`-style format string that specifies
 *                         how to format the output.
 * @param[in]      ...     A variable argument list containing the values to be
 *                         written.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * `SCU_ERROR_WRITING_BUFFER` if an error occurred while appending to the byte
 * string, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_rasnprintf(
    char** restrict buffer,
    int64_t* restrict size,
    int64_t* restrict written,
    const char* restrict format,
    ...
);

/**
 * @brief Returns the file position indicator of a specified file stream.
 *
 * @note For binary streams, the value returned by this function is the number
 * of bytes from the beginning of the file. For text streams, the value is
 * unspecified and only meaningful as an input to `scu_fseek()`.
 *
 * @param[in]  file     The file stream to check.
 * @param[out] position The file position indicator, or -1 on failure.
 * @return `SCU_ERROR_TELLING_FILE` if an error occurred while getting the file
 * position indicator, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_ftell(SCUFile* file, int64_t* position);

/**
 * @brief Sets the file position indicator of a specified file stream.
 *
 * @note For binary streams, the new position is exactly `offset` bytes from
 * `seekOrigin`, which is either from the beginning of the file
 * (`SCU_SEEK_ORIGIN_SET`), from the current position (`SCU_SEEK_ORIGIN_CUR`),
 * or from the end of the file (`SCU_SEEK_ORIGIN_END`). Binary streams are not
 * required to support seeking from `SCU_SEEK_ORIGIN_END`, in particular if
 * additional null bytes are output.
 *
 * For text streams, the only supported values for `offset` are zero (works with
 * any `seekOrigin`) and a value returned by a previous call to `scu_ftell()` on
 * a file stream associated with the same file (works with `SCU_SEEK_ORIGIN_SET`
 * only).
 *
 * A call to this function undoes the effects of previous calls to `funreadc()`
 * and clears the end-of-file indicator of the specified file stream.
 *
 * @param[in, out] file       The file stream to modify.
 * @param[in]      seekOrigin The origin from which to set the file position
 *                            indicator.
 * @param[in]      offset     The offset from `seekOrigin` to set the file
 *                            position indicator.
 * @return `SCU_ERROR_SEEKING_FILE` if an error occurred while setting the file
 * position indicator, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_fseek(SCUFile* file, SCUSeekOrigin seekOrigin, int64_t offset);

/**
 * @brief Sets the file position indicator of a specified file stream to the
 * beginning of the file.
 *
 * @note Calling this function is equivalent to calling `scu_fseek(file,
 * SCU_SEEK_ORIGIN_SET, 0)`, except that both the end-of-file and error
 * indicators of the specified file stream are cleared.
 *
 * A call to this function also undoes the effects of previous calls to
 * `funreadc()`.
 *
 * @param[in, out] file The file stream to modify.
 */
void scu_frewind(SCUFile* file);

/**
 * @brief Clears the end-of-file and error indicators of a specified file
 * stream.
 *
 * @param[in, out] file The file stream to modify.
 */
void scu_fclear(SCUFile* file);

/**
 * @brief Determines if the end of a specified file stream has been reached.
 *
 * @note As this function only returns the end-of-file indicator as reported by
 * the last I/O operation, it only makes sense to call it **after** such an
 * operation failed to distinguish between an end-of-file condition and an
 * actual error.
 *
 * @param[in] file The file stream to check.
 * @return `true` if the end of the specified file stream has been reached,
 * otherwise `false`.
 */
bool scu_feof(SCUFile* file);

/**
 * @brief Determines if an error has occurred on a specified file stream.
 *
 * @param[in] file The file stream to check.
 * @return `true` if an error has occurred on the specified file stream,
 * otherwise `false`.
 */
bool scu_ferror(SCUFile* file);

#endif