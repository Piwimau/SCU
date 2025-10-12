#ifndef SCU_TIMER_H
#define SCU_TIMER_H

#include <stdint.h>
#include "scu/error.h"

/** @brief Represents the state of an `SCUTimer`. */
typedef enum SCUTimerState {

    /** @brief Indicates that the timer is stopped and not measuring time. */
    SCU_TIMER_STATE_STOPPED,

    /** @brief Indicates that the timer is running and measuring time. */
    SCU_TIMER_STATE_RUNNING

} SCUTimerState;

/** @brief Represents a timer for measuring wall and CPU time. */
typedef struct SCUTimer SCUTimer;

/** @brief Represents the result of a time measurement. */
typedef struct SCUTimerResult {

    /** @brief The measured wall time in nanoseconds. */
    int64_t wallNs;

    /** @brief The measured CPU time in nanoseconds. */
    int64_t cpuNs;

} SCUTimerResult;

/**
 * @brief Allocates and initializes a new `SCUTimer`.
 *
 * @note The timer is initialized in a stopped state with an accumulated wall
 * and CPU time of zero. Use `scu_timer_start()` or `scu_timer_restart()` to
 * start measuring time.
 *
 * This function dynamically allocates memory using `scu_malloc()`.
 *
 * @warning The caller is responsible for deallocating the timer with
 * `scu_timer_free()` when it is no longer needed.
 *
 * @return A pointer to a new `SCUTimer`, or `nullptr` on failure.
 */
[[nodiscard]]
SCUTimer* scu_timer_new();

/**
 * @brief Starts an `SCUTimer`.
 *
 * @note If `timer` is already running, this function has no effect. Otherwise,
 * it starts measuring time from zero (if `timer` was never started before or
 * was previously reset) or resumes measuring time from the accumulated wall and
 * CPU time (if `timer` was previously stopped).
 *
 * This function does not reset the accumulated wall and CPU time.
 *
 * @param[in, out] timer The timer to start.
 * @return `SCU_ERROR_TIMER_FAILED` if an error occurred while starting `timer`,
 * or `SCU_ERROR_NONE` on success.
 */
SCUError scu_timer_start(SCUTimer* timer);

/**
 * @brief Restarts an `SCUTimer`.
 *
 * @note If `timer` is already running or was previously stopped, this function
 * resets the accumulated wall and CPU time to zero and starts measuring time.
 * Otherwise, if `timer` was never started before or was previously reset, this
 * function simply behaves like `scu_timer_start()`.
 *
 * This function resets the accumulated wall and CPU time. It is equivalent to
 * calling `scu_timer_reset()` followed by `scu_timer_start()`.
 *
 * @param[in, out] timer The timer to restart.
 * @return `SCU_ERROR_TIMER_FAILED` if an error occurred while restarting
 * `timer`, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_timer_restart(SCUTimer* timer);

/**
 * @brief Stops an `SCUTimer`.
 *
 * @note If `timer` was never started before or was previously stopped or reset,
 * this function has no effect. Otherwise, it stops measuring time and retains
 * the accumulated wall and CPU time.
 *
 * This function does not reset the accumulated wall and CPU time.
 *
 * @param[in, out] timer The timer to stop.
 * @return `SCU_ERROR_TIMER_FAILED` if an error occurred while stopping `timer`,
 * or `SCU_ERROR_NONE` on success.
 */
SCUError scu_timer_stop(SCUTimer* timer);

/**
 * @brief Resets an `SCUTimer`.
 *
 * @note If `timer` was never started before or was previously reset, this
 * function has no effect. Otherwise, it stops measuring time (if `timer` is
 * running) and resets the accumulated wall and CPU time to zero.
 *
 * This function resets the accumulated wall and CPU time. It does not start
 * `timer` again.
 *
 * @param[in, out] timer The timer to reset.
 */
void scu_timer_reset(SCUTimer* timer);

/**
 * @brief Returns the current state of an `SCUTimer`.
 *
 * @param[in] timer The timer to query.
 * @return `SCU_TIMER_STATE_RUNNING` if `timer` is currently running, otherwise
 * `SCU_TIMER_STATE_STOPPED`.
 */
SCUTimerState scu_timer_state(const SCUTimer* timer);

/**
 * @brief Returns the accumulated wall time in nanoseconds.
 *
 * @note If `timer` was never started before or was previously reset, this
 * function returns zero. Otherwise, it returns the total wall time measured by
 * `timer` in nanoseconds up to the point when it was last stopped (if `timer`
 * is stopped) or up to the current point in time (if `timer` is running).
 *
 * @param[in] timer The timer to query.
 * @return The accumulated wall time in nanoseconds, or -1 on failure.
 */
int64_t scu_timer_wall_ns(const SCUTimer* timer);

/**
 * @brief Returns the accumulated CPU time in nanoseconds.
 *
 * @note If `timer` was never started before or was previously reset, this
 * function returns zero. Otherwise, it returns the total CPU time measured by
 * `timer` in nanoseconds up to the point when it was last stopped (if `timer`
 * is stopped) or up to the current point in time (if `timer` is running).
 *
 * @param[in] timer The timer to query.
 * @return The accumulated CPU time in nanoseconds, or -1 on failure.
 */
int64_t scu_timer_cpu_ns(const SCUTimer* timer);

/**
 * @brief Deallocates an `SCUTimer`.
 *
 * @note If `timer` is `nullptr`, this function has no effect.
 *
 * @warning The behavior is undefined if `timer` is used after it has been
 * deallocated.
 *
 * @param[in] timer The timer to deallocate.
 */
void scu_timer_free(SCUTimer* timer);

/**
 * @brief Measures the wall and CPU time required to execute a block of code.
 *
 * This macro simplifies the process of measuring the wall and CPU time required
 * to execute a block of code. It allocates a new `SCUTimer`, starts it,
 * executes the block of code, stops the timer, retrieves the measured times,
 * and deallocates the timer. If any error occurs during this process, the macro
 * sets the wall and CPU time in the `SCUTimerResult` pointed to by `result` to
 * -1.
 *
 * ```c
 * SCUTimerResult result;
 * SCU_TIME(&result) {
 *     // Some code to be timed...
 * }
 * if ((result.wallNs == -1) || (result.cpuNs == -1)) {
 *     // Handle error...
 * }
 * else {
 *     // Use result.wallNs and result.cpuNs...
 * }
 * ```
 *
 * @param[out] result A pointer to an `SCUTimerResult` where the measured wall
 *                    and CPU time are stored.
 */
#define SCU_TIME(result)                                        \
    for (bool scuOnce = true; scuOnce;)                         \
        for (                                                   \
            SCUTimer* scuTimer = scu_timer_new();               \
            scuOnce;                                            \
            scuOnce = false,                                    \
            scu_timer_free(scuTimer),                           \
            scuTimer = nullptr                                  \
        )                                                       \
            for (                                               \
                SCUError scuError = (scuTimer != nullptr)       \
                    ? scu_timer_start(scuTimer)                 \
                    : SCU_ERROR_OUT_OF_MEMORY;                  \
                scuOnce;                                        \
                scuOnce = false,                                \
                scu_timer_stop(scuTimer),                       \
                (result)->wallNs = scu_timer_wall_ns(scuTimer), \
                (result)->cpuNs = scu_timer_cpu_ns(scuTimer),   \
                scu_timer_free(scuTimer),                       \
                scuTimer = nullptr                              \
            )                                                   \
                if (scuError != SCU_ERROR_NONE) {               \
                    (result)->wallNs = -1;                      \
                    (result)->cpuNs = -1;                       \
                    break;                                      \
                }                                               \
                else

#endif