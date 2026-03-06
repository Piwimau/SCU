#ifndef SCU_TIME_H
#define SCU_TIME_H

#include "scu/error.h"
#include "scu/types.h"

/** @brief Represents a timing mode for measuring CPU time. */
typedef enum SCUTimingMode {

    /**
     * @brief Indicates that the CPU time should be measured for the entire
     * process.
     */
    SCU_TIMING_MODE_PROCESS,

    /**
     * @brief Indicates that the CPU time should be measured for the current
     * thread only.
     */
    SCU_TIMING_MODE_THREAD

} SCUTimingMode;

/**
 * @brief Represents a stopwatch for measuring wall and CPU time.
 *
 * @warning The internal representation of the stopwatch is an implementation
 * detail and should not be relied upon. Most importantly, the behavior is
 * undefined if its fields are accessed directly.
 */
typedef struct SCUStopwatch {

    /** @brief The timing mode for measuring CPU time. */
    SCUTimingMode timingMode;

    /** @brief The last starting wall time in nanoseconds. */
    SCUi64 startWallNs;

    /** @brief The last starting CPU time in nanoseconds. */
    SCUi64 startCpuNs;

    /** @brief The accumulated wall time in nanoseconds. */
    SCUi64 accWallNs;

    /** @brief The accumulated CPU time in nanoseconds. */
    SCUi64 accCpuNs;

    /** @brief Whether the stopwatch is currently running. */
    bool isRunning;

} SCUStopwatch;

/** @brief Represents the result of a timing. */
typedef struct SCUTimingResult {

    /** @brief The measured wall time in nanoseconds. */
    SCUi64 wallNs;

    /** @brief The measured CPU time in nanoseconds. */
    SCUi64 cpuNs;

    /** @brief An error code indicating whether the timing was successful. */
    SCUError error;

} SCUTimingResult;

/**
 * @brief Initializes a specified stopwatch.
 *
 * @note This function may be called more than once to reinitialize the same
 * stopwatch with a different timing mode. Any previously accumulated wall and
 * CPU times are discarded, and the stopwatch is stopped if it was previously
 * running.
 *
 * @param[in, out] stopwatch  The stopwatch to initialize.
 * @param[in]      timingMode The timing mode for measuring CPU time.
 */
void scu_stopwatch_init(SCUStopwatch* stopwatch, SCUTimingMode timingMode);

/**
 * @brief Starts a specified stopwatch.
 *
 * @note If the stopwatch is already running, this function does nothing.
 * Otherwise, it starts measuring time from zero (if the stopwatch was never
 * started before or was previously reset) or resumes measuring time from the
 * accumulated wall and CPU time (if the stopwatch was previously stopped).
 *
 * This function does not reset the accumulated wall and CPU time.
 *
 * @param[in, out] stopwatch The stopwatch to start.
 * @return `true` if the stopwatch was started successfully, otherwise `false`.
 */
bool scu_stopwatch_start(SCUStopwatch* stopwatch);

/**
 * @brief Restarts a specified stopwatch.
 *
 * @note If the stopwatch is already running or was previously stopped, this
 * function resets the accumulated wall and CPU time to zero and starts
 * measuring time. Otherwise, if the stopwatch was never started before or was
 * previously reset, this function simply behaves like `scu_stopwatch_start()`.
 *
 * This function resets the accumulated wall and CPU time. It is equivalent to
 * calling `scu_stopwatch_reset()`, followed by `scu_stopwatch_start()`.
 *
 * @param[in, out] stopwatch The stopwatch to restart.
 * @return `true` if the stopwatch was restarted successfully, otherwise
 * `false`.
 */
bool scu_stopwatch_restart(SCUStopwatch* stopwatch);

/**
 * @brief Stops a specified stopwatch.
 *
 * @note If the stopwatch was never started before or was previously stopped or
 * reset, this function does nothing. Otherwise, it stops measuring time and
 * retains the accumulated wall and CPU time.
 *
 * This function does not reset the accumulated wall and CPU time.
 *
 * @param[in, out] stopwatch The stopwatch to stop.
 * @return `true` if the stopwatch was stopped successfully, otherwise `false`.
 */
bool scu_stopwatch_stop(SCUStopwatch* stopwatch);

/**
 * @brief Resets a specified stopwatch.
 *
 * @note If the stopwatch was never started before or was previously reset, this
 * function does nothing. Otherwise, it stops measuring time (if the stopwatch
 * is running) and resets the accumulated wall and CPU time to zero.
 *
 * This function resets the accumulated wall and CPU time. It does not start
 * the stopwatch again.
 *
 * @param[in, out] stopwatch The stopwatch to reset.
 */
void scu_stopwatch_reset(SCUStopwatch* stopwatch);

/**
 * @brief Determines whether a specified stopwatch is currently running.
 *
 * @param[in] stopwatch The stopwatch to examine.
 * @return `true` if the stopwatch is currently running, otherwise `false`.
 */
bool scu_stopwatch_is_running(const SCUStopwatch* stopwatch);

/**
 * @brief Retrieves the elapsed wall and CPU time from a specified stopwatch.
 *
 * @note If the stopwatch was never started before or was previously reset, the
 * the returned timing result has both `wallNs` and `cpuNs` fields set to `0`,
 * and the `error` field set to `SCU_ERROR_NONE`. Otherwise, the timing result
 * contains the accumulated wall and CPU time measured by the stopwatch in
 * nanoseconds up to the point when it was last stopped (if the stopwatch is
 * stopped) or up to the current point in time (if the stopwatch is running).
 * The `error` field is also set to `SCU_ERROR_NONE` in this case.
 *
 * In the (unlikely) case that retrieving the elapsed times fails, the `error`
 * field of the returned timing result is set to `SCU_ERROR_TIMING_FAILED`, and
 * both `wallNs` and `cpuNs` contain an unspecified value.
 *
 * @param[in] stopwatch The stopwatch to examine.
 * @return A timing result containing the elapsed wall and CPU time in
 * nanoseconds on success, or an appropriate error code on failure.
 */
SCUTimingResult scu_stopwatch_elapsed(const SCUStopwatch* stopwatch);

/**
 * @brief Measures the wall and CPU time required to execute a block of code.
 *
 * This macro simplifies the process of measuring the wall and CPU time required
 * to execute a block of code. It creates a new stopwatch, starts it, executes
 * the block of code, stops the stopwatch, and retrieves the elapsed times,
 * which are assigned to `result->wallNs` and `result->cpuNs` respectively.
 *
 * The following example demonstrates the basic usage of this macro:
 *
 * ```c
 * SCUTimingResult result;
 * SCU_TIME(SCU_TIMING_MODE_PROCESS, &result) {
 *     // Some code to be timed...
 * }
 * if (result.error != SCU_ERROR_NONE) {
 *     // Handle the error...
 * }
 * else {
 *     // Use result.wallNs and result.cpuNs...
 * }
 * ```
 *
 * @note If the stopwatch cannot be started, the block of code is not executed.
 * In this case, both `result->wallNs` and `result->cpuNs` are set to an
 * unspecified value, and `result->error` is set to `SCU_ERROR_TIMING_FAILED`.
 * This is also the case if retrieving the elapsed times fails after executing
 * the block of code and stopping the stopwatch.
 *
 * @param[in]  timingMode The timing mode for measuring CPU time.
 * @param[out] result     A timing result containing the elapsed wall and CPU
 * time in nanoseconds on success, or an appropriate error code on failure.
 */
#define SCU_TIME(timingMode, result)                                    \
    for (bool scuOnce = true; scuOnce; scuOnce = false)                 \
        for (                                                           \
            SCUStopwatch scuStopwatch = { .timingMode = (timingMode) }; \
            scuOnce;                                                    \
            scuOnce = false                                             \
        )                                                               \
            for (                                                       \
                ;                                                       \
                scuOnce && (scu_stopwatch_start(&scuStopwatch)          \
                    ? true                                              \
                    : (                                                 \
                        (result)->wallNs = -1,                          \
                        (result)->cpuNs = -1,                           \
                        (result)->error = SCU_ERROR_TIMING_FAILED,      \
                        false                                           \
                    ));                                                 \
                scuOnce = false,                                        \
                scu_stopwatch_stop(&scuStopwatch),                      \
                *(result) = scu_stopwatch_elapsed(&scuStopwatch)        \
            )

#endif