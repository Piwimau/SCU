#ifndef SCU_TIMER_H
#define SCU_TIMER_H

/** @brief Represents a timer for measuring some elapsed time. */
typedef struct SCUTimer SCUTimer;

/**
 * @brief Allocates and initializes a new `SCUTimer`.
 *
 * @note A new `SCUTimer` is not running by default. Use `scu_timer_start()` to start measuring
 * time.
 *
 * @warning An `SCUTimer` returned by this function is dynamically allocated and must be passed to
 * `scu_timer_free()` to avoid a memory leak.
 *
 * @return A pointer to a new initialized `SCUTimer` on success, or a `nullptr` if an out-of-memory
 * condition occurred.
 */
SCUTimer* scu_timer_new();

/**
 * @brief Starts or resumes a given `SCUTimer`.
 *
 * @note If `timer` has never been started before or was reset with `scu_timer_reset()`, this starts
 * a new time interval. Otherwise, it resumes measuring time in the current interval.
 *
 * If `timer` is already running, this function has no effect.
 *
 * @param[in, out] timer `SCUTimer` to start or resume.
 * @return `true` if the given `SCUTimer` was successfully started or resumed or if it was already
 * running, otherwise `false`.
 */
bool scu_timer_start(SCUTimer* timer);

/**
 * @brief Stops a given `SCUTimer` without resetting its elapsed time.
 *
 * @note If you want to simultaneously stop an `SCUTimer` and reset its elapsed time,
 * use `scu_timer_reset()` instead.
 *
 * If `timer` is not running, this function has no effect.
 *
 * @param[in, out] timer `SCUTimer` to stop.
 * @return `true` if the given `SCUTimer` was successfully stopped or if it was not running,
 * otherwise `false`.
 */
bool scu_timer_stop(SCUTimer* timer);

/**
 * @brief Stops a given `SCUTimer` and resets its elapsed time.
 *
 * @note If you want to stop an `SCUTimer` without resetting its elapsed time,
 * use `scu_timer_stop()` instead.
 *
 * @param[in, out] timer `SCUTimer` to reset.
 */
void scu_timer_reset(SCUTimer* timer);

/**
 * @brief Stops a given `SCUTimer`, resets its elapsed time and starts it again.
 *
 * @note This is a convenience function which can be used instead of repeated calls to
 * `scu_timer_reset()` and `scu_timer_start()`.
 *
 * @param[in, out] timer `SCUTimer` to restart.
 * @return `true` if the given `SCUTimer` was successfully restarted, otherwise `false`.
 */
bool scu_timer_restart(SCUTimer* timer);

/**
 * @brief Determines if a given `SCUTimer` is currently running.
 *
 * @param[in] timer `SCUTimer` to examine.
 * @return `true` if the given `SCUTimer` is currently running, otherwise `false`.
 */
bool scu_timer_isRunning(const SCUTimer* timer);

/**
 * @brief Returns the elapsed CPU time measured by a given `SCUTimer` (in seconds).
 *
 * @note The elapsed CPU time is based on the current state of the `SCUTimer`. If it has never been
 * started before or was reset using `scu_timer_reset()`, the elapsed CPU time is zero, as no time
 * interval has been recorded yet. If the `SCUTimer` was previously stopped using
 * `scu_timer_stop()`, the elapsed CPU time corresponds to the difference between the start and end
 * time of the current interval. Otherwise, if the `SCUTimer` is still running, the elapsed CPU time
 * is calculated as the difference between the start time of the current interval and the current
 * point in time.
 *
 * @param[in] timer `SCUTimer` to get the elapsed CPU time of.
 * @return The elapsed CPU time measured by the given `SCUTimer` (in seconds), or a negative value
 * if an error occurred.
 */
double scu_timer_elapsedCPUTime(const SCUTimer* timer);

/**
 * @brief Returns the elapsed wall time measured by a given `SCUTimer` (in seconds).
 *
 * @note The elapsed wall time is based on the current state of the `SCUTimer`. If it has never been
 * started before or was reset using `scu_timer_reset()`, the elapsed wall time is zero, as no time
 * interval has been recorded yet. If the `SCUTimer` was previously stopped using
 * `scu_timer_stop()`, the elapsed wall time corresponds to the difference between the start and end
 * time of the current interval. Otherwise, if the `SCUTimer` is still running, the elapsed wall
 * time is calculated as the difference between the start time of the current interval and the
 * current point in time.
 *
 * @param[in] timer `SCUTimer` to get the elapsed wall time of.
 * @return The elapsed wall time measured by the given `SCUTimer` (in seconds), or a negative value
 * if an error occurred.
 */
double scu_timer_elapsedWallTime(const SCUTimer* timer);

/**
 * @brief Deallocates a given `SCUTimer`.
 *
 * @note For convenience, `timer` may be a `nullptr`.
 *
 * @warning Any use of the `SCUTimer` after it has been deallocated results in undefined behavior.
 *
 * @param[in, out] timer `SCUTimer` to deallocate.
 */
void scu_timer_free(SCUTimer* timer);

#endif