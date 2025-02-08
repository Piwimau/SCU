#ifndef SCU_ERROR_H
#define SCU_ERROR_H

/** @brief Represents an error code used to signal a success or failure condition. */
typedef enum SCUError {

    /** @brief Indicates that an operation was successful (i. e. no error occurred). */
    SCU_ERROR_NONE,

    /** @brief Indicates that one of the arguments passed to a function was invalid. */
    SCU_ERROR_INVALID_ARGUMENT,

    /** @brief Indicates that an out-of-memory condition occurred. */
    SCU_ERROR_OUT_OF_MEMORY,

    /**
     * @brief Indicates that the end-of-file condition occurred before any characters could be read
     * from an input stream.
     */
    SCU_ERROR_END_OF_FILE,

    /** @brief Indicates that reading from an input stream failed. */
    SCU_ERROR_READING_STREAM_FAILED,

    /** @brief Indicates that writing to an output buffer failed. */
    SCU_ERROR_WRITING_BUFFER_FAILED

} SCUError;

#endif