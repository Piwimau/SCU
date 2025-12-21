#ifndef SCU_STOPWATCH_H
#define SCU_STOPWATCH_H

#include <stdint.h>
#include "scu/error.h"

/** @brief Represents a stopwatch able to measure wall and CPU time. */
typedef struct SCUStopwatch SCUStopwatch;

/** @brief Represents the state of an `SCUStopwatch`. */
typedef enum SCUStopwatchState {

    /** @brief Indicates that a stopwatch is stopped and not measuring time. */
    SCU_STOPWATCH_STATE_STOPPED,

    /** @brief Indicates that a stopwatch is running and measuring time. */
    SCU_STOPWATCH_STATE_RUNNING

} SCUStopwatchState;

/** @brief Represents a timing. */
typedef struct SCUTiming {

    /** @brief The measured wall time in nanoseconds. */
    int64_t wallNs;

    /** @brief The measured CPU time in nanoseconds. */
    int64_t cpuNs;

} SCUTiming;

/**
 * @brief Allocates and initializes a new `SCUStopwatch`.
 *
 * @note The stopwatch is initialized in a stopped state with an accumulated
 * wall and CPU time of zero. Use `scu_stopwatch_start()` or
 * `scu_stopwatch_restart()` to start measuring time.
 *
 * This function dynamically allocates memory using `scu_malloc()`.
 *
 * @warning The caller is responsible for deallocating the stopwatch with
 * `scu_stopwatch_free()` when it is no longer needed.
 *
 * @return A pointer to a new `SCUStopwatch`, or `nullptr` on failure.
 */
[[nodiscard]]
SCUStopwatch* scu_stopwatch_new();

/**
 * @brief Starts an `SCUStopwatch`.
 *
 * @note If `stopwatch` is already running, this function does nothing.
 * Otherwise, it starts measuring time from zero (if `stopwatch` was never
 * started before or was previously reset) or resumes measuring time from the
 * accumulated wall and CPU time (if `stopwatch` was previously stopped).
 *
 * This function does not reset the accumulated wall and CPU time.
 *
 * @param[in, out] stopwatch The stopwatch to start.
 * @return `SCU_ERROR_STOPWATCH_FAILED` if an error occurred while starting
 * `stopwatch`, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_stopwatch_start(SCUStopwatch* stopwatch);

/**
 * @brief Restarts an `SCUStopwatch`.
 *
 * @note If `stopwatch` is already running or was previously stopped, this
 * function resets the accumulated wall and CPU time to zero and starts
 * measuring time. Otherwise, if `stopwatch` was never started before or was
 * previously reset, this function simply behaves like `scu_stopwatch_start()`.
 *
 * This function resets the accumulated wall and CPU time. It is equivalent to
 * calling `scu_stopwatch_reset()` followed by `scu_stopwatch_start()`.
 *
 * @param[in, out] stopwatch The stopwatch to restart.
 * @return `SCU_ERROR_STOPWATCH_FAILED` if an error occurred while restarting
 * `stopwatch`, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_stopwatch_restart(SCUStopwatch* stopwatch);

/**
 * @brief Stops an `SCUStopwatch`.
 *
 * @note If `stopwatch` was never started before or was previously stopped or
 * reset, this function does nothing. Otherwise, it stops measuring time and
 * retains the accumulated wall and CPU time.
 *
 * This function does not reset the accumulated wall and CPU time.
 *
 * @param[in, out] stopwatch The stopwatch to stop.
 * @return `SCU_ERROR_STOPWATCH_FAILED` if an error occurred while stopping
 * `stopwatch`, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_stopwatch_stop(SCUStopwatch* stopwatch);

/**
 * @brief Resets an `SCUStopwatch`.
 *
 * @note If `stopwatch` was never started before or was previously reset, this
 * function does nothing. Otherwise, it stops measuring time (if `stopwatch` is
 * running) and resets the accumulated wall and CPU time to zero.
 *
 * This function resets the accumulated wall and CPU time. It does not start
 * `stopwatch` again.
 *
 * @param[in, out] stopwatch The stopwatch to reset.
 */
void scu_stopwatch_reset(SCUStopwatch* stopwatch);

/**
 * @brief Returns the current state of an `SCUStopwatch`.
 *
 * @param[in] stopwatch The stopwatch to query.
 * @return `SCU_STOPWATCH_STATE_RUNNING` if `stopwatch` is currently running,
 * otherwise `SCU_STOPWATCH_STATE_STOPPED`.
 */
SCUStopwatchState scu_stopwatch_state(const SCUStopwatch* stopwatch);

/**
 * @brief Returns the accumulated wall time in nanoseconds.
 *
 * @note If `stopwatch` was never started before or was previously reset, this
 * function returns zero. Otherwise, it returns the total wall time measured by
 * `stopwatch` in nanoseconds up to the point when it was last stopped (if
 * `stopwatch` is stopped) or up to the current point in time (if `stopwatch` is
 * running).
 *
 * @param[in] stopwatch The stopwatch to query.
 * @return The accumulated wall time in nanoseconds, or -1 on failure.
 */
int64_t scu_stopwatch_wall_ns(const SCUStopwatch* stopwatch);

/**
 * @brief Returns the accumulated CPU time in nanoseconds.
 *
 * @note If `stopwatch` was never started before or was previously reset, this
 * function returns zero. Otherwise, it returns the total CPU time measured by
 * `stopwatch` in nanoseconds up to the point when it was last stopped (if
 * `stopwatch` is stopped) or up to the current point in time (if `stopwatch` is
 * running).
 *
 * @param[in] stopwatch The stopwatch to query.
 * @return The accumulated CPU time in nanoseconds, or -1 on failure.
 */
int64_t scu_stopwatch_cpu_ns(const SCUStopwatch* stopwatch);

/**
 * @brief Deallocates an `SCUStopwatch`.
 *
 * @note If `stopwatch` is a `nullptr`, this function does nothing.
 *
 * @warning The behavior is undefined if `stopwatch` is used after it has been
 * deallocated.
 *
 * @param[in] stopwatch The stopwatch to deallocate.
 */
void scu_stopwatch_free(SCUStopwatch* stopwatch);

/**
 * @brief Measures the wall and CPU time required to execute a block of code.
 *
 * This macro simplifies the process of measuring the wall and CPU time required
 * to execute a block of code. It allocates a new `SCUStopwatch`, starts it,
 * executes the block of code, stops the stopwatch, retrieves the measured
 * times, and deallocates the stopwatch. If any error occurs during this
 * process, the macro sets the wall and CPU time in `timing` to -1.
 *
 * The following example demonstrates the basic usage of this macro:
 *
 * ```c
 * SCUTiming timing;
 * SCU_TIME(&timing) {
 *     // Some code to be timed...
 * }
 * if ((timing.wallNs == -1) || (timing.cpuNs == -1)) {
 *     // Handle error...
 * }
 * else {
 *     // Use timing.wallNs and timing.cpuNs...
 * }
 * ```
 *
 * @param[out] timing A pointer to an `SCUTiming` where the measured wall and
 * CPU time are stored.
 */
#define SCU_TIME(timing)                                                \
    for (bool scuOnce = true; scuOnce;)                                 \
        for (                                                           \
            SCUStopwatch* scuStopwatch = scu_stopwatch_new();           \
            scuOnce;                                                    \
            scuOnce = false,                                            \
            scu_stopwatch_free(scuStopwatch),                           \
            scuStopwatch = nullptr                                      \
        )                                                               \
            for (                                                       \
                SCUError scuError = (scuStopwatch != nullptr)           \
                    ? scu_stopwatch_start(scuStopwatch)                 \
                    : SCU_ERROR_OUT_OF_MEMORY;                          \
                scuOnce;                                                \
                scuOnce = false,                                        \
                scu_stopwatch_stop(scuStopwatch),                       \
                (timing)->wallNs = scu_stopwatch_wall_ns(scuStopwatch), \
                (timing)->cpuNs = scu_stopwatch_cpu_ns(scuStopwatch),   \
                scu_stopwatch_free(scuStopwatch),                       \
                scuStopwatch = nullptr                                  \
            )                                                           \
                if (scuError != SCU_ERROR_NONE) {                       \
                    (timing)->wallNs = -1;                              \
                    (timing)->cpuNs = -1;                               \
                    break;                                              \
                }                                                       \
                else

#endif