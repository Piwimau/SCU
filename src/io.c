#include <string.h>
#include <SCU/io.h>
#include <SCU/math.h>
#include <SCU/memory.h>

/** @brief Initial capacity for allocating a buffer. */
static constexpr int64_t SCU_INITIAL_CAPACITY = 128;

/**
 * @brief Ensures that a given dynamically allocated buffer has at least a specified capacity.
 *
 * @note `*buffer` is allowed to be a `nullptr`, in which case `*capacity` must be zero (and vice
 * versa). If `*buffer` is not a `nullptr`, it must have been allocated by `SCU_MALLOC()`,
 * `SCU_CALLOC()` or `SCU_REALLOC()` (or compatible functions these macros are implemented with,
 * which are the standard `malloc()`, `calloc()` and `realloc()` functions by default) and
 * `*capacity` must be greater than zero.
 *
 * @param[in, out] buffer           Dynamically allocated buffer to ensure the capacity of.
 * @param[in, out] capacity         Capacity of the dynamically allocated buffer (including the
 *                                  terminating `\0` byte), updated if `*buffer` is resized.
 * @param[in]      requiredCapacity Minimum capacity to ensure (including the terminating `\0`
 *                                  byte).
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `*capacity` or `requiredCapacity` is negative or if
 * `*buffer` is a `nullptr` and `*capacity` is not equal to zero (or vice versa),
 * `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred and `SCU_ERROR_NONE` otherwise.
 */
static inline SCUError scu_ensureCapacity(
    char** buffer,
    int64_t* capacity,
    int64_t requiredCapacity
) {
    if ((*capacity < 0) || (requiredCapacity < 0) || ((*buffer == nullptr) != (*capacity == 0))) {
        return SCU_ERROR_INVALID_ARGUMENT;
    }
    if (*capacity < requiredCapacity) {
        int64_t newCapacity = SCU_MAX(*capacity, 1);
        while (newCapacity < requiredCapacity) {
            // Resizing with a factor of 1.5 wastes less memory than simply doubling the capacity
            // and may actually allow us to reuse some blocks of memory.
            newCapacity = (newCapacity * 3 / 2) + 1;
        }
        char* newBuffer = SCU_REALLOC(*buffer, newCapacity);
        if (newBuffer == nullptr) {
            return SCU_ERROR_OUT_OF_MEMORY;
        }
        *buffer = newBuffer;
        *capacity = newCapacity;
    }
    return SCU_ERROR_NONE;
}

SCUError scu_readLine(FILE* stream, char** buffer, int64_t* capacity) {
    if ((*capacity < 0) || ((*buffer == nullptr) != (*capacity == 0))) {
        return SCU_ERROR_INVALID_ARGUMENT;
    }
    if (*buffer == nullptr) {
        SCUError error = scu_ensureCapacity(buffer, capacity, SCU_INITIAL_CAPACITY);
        if (error != SCU_ERROR_NONE) {
            return error;
        }
    }
    int64_t index = 0;
    int c;
    while ((c = fgetc(stream)) != EOF) {
        // `index` is equivalent to the current number of characters in `*buffer`. We add one for
        // the next character read from `stream` and one for the terminating `\0` byte to reach the
        // required capacity.
        SCUError error = scu_ensureCapacity(buffer, capacity, index + 2);
        if (error != SCU_ERROR_NONE) {
            return error;
        }
        (*buffer)[index++] = (char) c;
        if (c == '\n') {
            break;
        }
    }
    (*buffer)[index] = '\0';
    if (ferror(stream)) {
        return SCU_ERROR_READING_STREAM_FAILED;
    }
    // Only report the end-of-file condition as an error if no characters could be read.
    if (feof(stream) && (index == 0)) {
        return SCU_ERROR_END_OF_FILE;
    }
    return SCU_ERROR_NONE;
}

SCUError scu_rsnprintf(char** buffer, int64_t* capacity, const char* format, ...) {
    va_list args;
    va_start(args, format);
    SCUError error = scu_vrsnprintf(buffer, capacity, format, args);
    va_end(args);
    return error;
}

SCUError scu_vrsnprintf(char** buffer, int64_t* capacity, const char* format, va_list args) {
    if ((*capacity < 0) || ((*buffer == nullptr) != (*capacity == 0))) {
        return SCU_ERROR_INVALID_ARGUMENT;
    }
    va_list argsCopy;
    va_copy(argsCopy, args);
    int64_t length = vsnprintf(nullptr, 0, format, argsCopy);
    va_end(argsCopy);
    if (length < 0) {
        return SCU_ERROR_WRITING_BUFFER_FAILED;
    }
    SCUError error = scu_ensureCapacity(buffer, capacity, length + 1);
    if (error != SCU_ERROR_NONE) {
        return error;
    }
    if (vsnprintf(*buffer, *capacity, format, args) < 0) {
        return SCU_ERROR_WRITING_BUFFER_FAILED;
    }
    return SCU_ERROR_NONE;
}

SCUError scu_rasnprintf(char** buffer, int64_t* capacity, const char* format, ...) {
    va_list args;
    va_start(args, format);
    SCUError error = scu_vrasnprintf(buffer, capacity, format, args);
    va_end(args);
    return error;
}

SCUError scu_vrasnprintf(char** buffer, int64_t* capacity, const char* format, va_list args) {
    if ((*capacity < 0) || ((*buffer == nullptr) != (*capacity == 0))) {
        return SCU_ERROR_INVALID_ARGUMENT;
    }
    // If there is no buffer to append to, we can simply fall back to using `scu_vrsnprintf()` and
    // avoid some extra work.
    if (*buffer == nullptr) {
        return scu_vrsnprintf(buffer, capacity, format, args);
    }
    int64_t offset = strnlen(*buffer, *capacity);
    va_list argsCopy;
    va_copy(argsCopy, args);
    int64_t length = vsnprintf(nullptr, 0, format, argsCopy);
    va_end(argsCopy);
    if (length < 0) {
        return SCU_ERROR_WRITING_BUFFER_FAILED;
    }
    SCUError error = scu_ensureCapacity(buffer, capacity, offset + length + 1);
    if (error != SCU_ERROR_NONE) {
        return error;
    }
    if (vsnprintf(*buffer + offset, *capacity - offset, format, args) < 0) {
        return SCU_ERROR_WRITING_BUFFER_FAILED;
    }
    return SCU_ERROR_NONE;
}