#ifndef SCU_TIME_H
#define SCU_TIME_H

#include "scu/types.h"

/**
 * @brief Represents a stopwatch for measuring wall and CPU time.
 *
 * @warning The internal representation of the stopwatch is an implementation
 * detail and should not be relied upon. Most importantly, the behavior is
 * undefined if its fields are accessed directly.
 */
typedef struct SCUStopwatch {

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

/** @brief Represents a timing. */
typedef struct SCUTiming {

    /** @brief The measured wall time in nanoseconds. */
    SCUi64 wallNs;

    /** @brief The measured CPU time in nanoseconds. */
    SCUi64 cpuNs;

} SCUTiming;

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
 * @note If the stopwatch was never started before or was previously reset, this
 * function returns a zero-initialized timing. Otherwise, it returns the
 * accumulated wall and CPU time measured by the stopwatch in nanoseconds up to
 * the point when it was last stopped (if the stopwatch is stopped) or up to the
 * current point in time (if the stopwatch is running).
 *
 * In the unlikely event that retrieving the elapsed times fails, both fields of
 * the returned timing are set to `-1`.
 *
 * @param[in] stopwatch The stopwatch to examine.
 * @return A timing containing the elapsed wall and CPU time in nanoseconds.
 */
SCUTiming scu_stopwatch_elapsed(const SCUStopwatch* stopwatch);

/**
 * @brief Measures the wall and CPU time required to execute a block of code.
 *
 * This macro simplifies the process of measuring the wall and CPU time required
 * to execute a block of code. It creates a new stopwatch, starts it, executes
 * the block of code, stops the stopwatch, and retrieves the elapsed times,
 * which are assigned to `timing->wallNs` and `timing->cpuNs` respectively.
 *
 * The following example demonstrates the basic usage of this macro:
 *
 * ```c
 * SCUTiming timing;
 * SCU_TIME(&timing) {
 *     // Some code to be timed...
 * }
 * if ((timing.wallNs == -1) || (timing.cpuNs == -1)) {
 *     // Handle the error...
 * }
 * else {
 *     // Use timing.wallNs and timing.cpuNs...
 * }
 * ```
 *
 * @note If the stopwatch cannot be started, the block of code is not executed.
 * In this case, both `timing->wallNs` and `timing->cpuNs` are set to `-1`. This
 * is also the case if retrieving the elapsed times fails after executing the
 * block of code and stopping the stopwatch.
 *
 * @param[out] timing A timing for the elapsed wall and CPU time on success,
 *                    or a timing with both fields set to `-1` on failure.
 */
#define SCU_TIME(timing)                                                     \
    for (bool scuOnce = true; scuOnce; scuOnce = false)                      \
        for (SCUStopwatch scuStopwatch = { }; scuOnce; scuOnce = false)      \
            for (                                                            \
                ;                                                            \
                scuOnce && (scu_stopwatch_start(&scuStopwatch)               \
                    ? true                                                   \
                    : ((timing)->wallNs = -1, (timing)->cpuNs = -1, false)); \
                scuOnce = false,                                             \
                scu_stopwatch_stop(&scuStopwatch),                           \
                *(timing) = scu_stopwatch_elapsed(&scuStopwatch)             \
            )

#endif