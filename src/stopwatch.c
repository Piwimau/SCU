#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#else
    #include <time.h>
#endif
#include "scu/alloc.h"
#include "scu/assert.h"
#include "scu/common.h"
#include "scu/stopwatch.h"

struct SCUStopwatch {

    /** @brief The starting wall time in nanoseconds. */
    int64_t startWallNs;

    /** @brief The starting CPU time in nanoseconds. */
    int64_t startCpuNs;

    /** @brief The accumulated wall time in nanoseconds. */
    int64_t accWallNs;

    /** @brief The accumulated CPU time in nanoseconds. */
    int64_t accCpuNs;

    /** @brief The current state of the stopwatch. */
    SCUStopwatchState state;

};

/** @brief The number of nanoseconds per second. */
static constexpr int64_t SCU_NANOS_PER_SEC = 1'000'000'000;

#ifdef _WIN32

/** @brief The number of nanoseconds per `FILETIME` tick. */
static constexpr int64_t SCU_NANOS_PER_TICK = 100;

/**
 * @brief Converts a `FILETIME` to nanoseconds.
 *
 * @param[in] filetime The `FILETIME` to convert.
 * @return The equivalent time in nanoseconds.
 */
static inline int64_t scu_filetime_to_ns(const FILETIME* filetime) {
    SCU_ASSERT(filetime != nullptr);
    uint64_t high = filetime->dwHighDateTime;
    uint64_t low = filetime->dwLowDateTime;
    uint64_t ticks = (high << 32) | low;
    return (int64_t) (ticks * SCU_NANOS_PER_TICK);
}

#else

/** @brief Represents a time interval expressed in seconds and nanoseconds. */
typedef struct timespec SCUTimespec;

/**
 * @brief Converts an `SCUTimespec` to nanoseconds.
 *
 * @param[in] timespec The `SCUTimespec` to convert.
 * @return The equivalent time in nanoseconds.
 */
static inline int64_t scu_timespec_to_ns(const SCUTimespec* timespec) {
    SCU_ASSERT(timespec != nullptr);
    return (timespec->tv_sec * SCU_NANOS_PER_SEC) + timespec->tv_nsec;
}

#endif

/**
 * @brief Returns the current wall time in nanoseconds.
 *
 * @return The current wall time in nanoseconds, or -1 on failure.
 */
static inline int64_t scu_wall_ns() {
#ifdef _WIN32
    LARGE_INTEGER counter;
    if (!QueryPerformanceCounter(&counter)) {
        return -1;
    }
    LARGE_INTEGER frequency;
    if (!QueryPerformanceFrequency(&frequency)) {
        return -1;
    }
    int64_t secs = counter.QuadPart / frequency.QuadPart;
    int64_t frac = counter.QuadPart % frequency.QuadPart;
    int64_t ns = (secs * SCU_NANOS_PER_SEC)
        + ((frac * SCU_NANOS_PER_SEC) / frequency.QuadPart);
    return ns;
#else
    SCUTimespec timespec;
    if (clock_gettime(CLOCK_MONOTONIC, &timespec) != 0) {
        return -1;
    }
    return scu_timespec_to_ns(&timespec);
#endif
}

/**
 * @brief Returns the current CPU time in nanoseconds.
 *
 * @return The current CPU time in nanoseconds, or -1 on failure.
 */
static inline int64_t scu_cpu_ns() {
#ifdef _WIN32
    FILETIME creationTime, exitTime, kernelTime, userTime;
    WINBOOL success = GetProcessTimes(
        GetCurrentProcess(),
        &creationTime,
        &exitTime,
        &kernelTime,
        &userTime
    );
    if (!success) {
        return -1;
    }
    return scu_filetime_to_ns(&kernelTime) + scu_filetime_to_ns(&userTime);
#else
    SCUTimespec timespec;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timespec) != 0) {
        return -1;
    }
    return scu_timespec_to_ns(&timespec);
#endif
}

[[nodiscard]]
SCUStopwatch* scu_stopwatch_new() {
    SCUStopwatch* stopwatch = scu_malloc(SCU_SIZEOF(SCUStopwatch));
    if (stopwatch != nullptr) {
        *stopwatch = (SCUStopwatch) { };
    }
    return stopwatch;
}

SCUError scu_stopwatch_start(SCUStopwatch* stopwatch) {
    SCU_ASSERT(stopwatch != nullptr);
    if (stopwatch->state != SCU_STOPWATCH_STATE_RUNNING) {
        int64_t wallNs = scu_wall_ns();
        if (wallNs == -1) {
            return SCU_ERROR_STOPWATCH_FAILED;
        }
        int64_t cpuNs = scu_cpu_ns();
        if (cpuNs == -1) {
            return SCU_ERROR_STOPWATCH_FAILED;
        }
        stopwatch->startWallNs = wallNs;
        stopwatch->startCpuNs = cpuNs;
        stopwatch->state = SCU_STOPWATCH_STATE_RUNNING;
    }
    return SCU_ERROR_NONE;
}

SCUError scu_stopwatch_restart(SCUStopwatch* stopwatch) {
    SCU_ASSERT(stopwatch != nullptr);
    int64_t wallNs = scu_wall_ns();
    if (wallNs == -1) {
        return SCU_ERROR_STOPWATCH_FAILED;
    }
    int64_t cpuNs = scu_cpu_ns();
    if (cpuNs == -1) {
        return SCU_ERROR_STOPWATCH_FAILED;
    }
    stopwatch->startWallNs = wallNs;
    stopwatch->startCpuNs = cpuNs;
    stopwatch->accWallNs = 0;
    stopwatch->accCpuNs = 0;
    stopwatch->state = SCU_STOPWATCH_STATE_RUNNING;
    return SCU_ERROR_NONE;
}

SCUError scu_stopwatch_stop(SCUStopwatch* stopwatch) {
    SCU_ASSERT(stopwatch != nullptr);
    if (stopwatch->state == SCU_STOPWATCH_STATE_RUNNING) {
        int64_t wallNs = scu_wall_ns();
        if (wallNs == -1) {
            return SCU_ERROR_STOPWATCH_FAILED;
        }
        int64_t cpuNs = scu_cpu_ns();
        if (cpuNs == -1) {
            return SCU_ERROR_STOPWATCH_FAILED;
        }
        stopwatch->accWallNs += wallNs - stopwatch->startWallNs;
        stopwatch->accCpuNs += cpuNs - stopwatch->startCpuNs;
        stopwatch->state = SCU_STOPWATCH_STATE_STOPPED;
    }
    return SCU_ERROR_NONE;
}

void scu_stopwatch_reset(SCUStopwatch* stopwatch) {
    SCU_ASSERT(stopwatch != nullptr);
    *stopwatch = (SCUStopwatch) { };
}

SCUStopwatchState scu_stopwatch_state(const SCUStopwatch* stopwatch) {
    SCU_ASSERT(stopwatch != nullptr);
    return stopwatch->state;
}

int64_t scu_stopwatch_wall_ns(const SCUStopwatch* stopwatch) {
    SCU_ASSERT(stopwatch != nullptr);
    if (stopwatch->state == SCU_STOPWATCH_STATE_RUNNING) {
        int64_t wallNs = scu_wall_ns();
        if (wallNs == -1) {
            return -1;
        }
        return stopwatch->accWallNs + (wallNs - stopwatch->startWallNs);
    }
    return stopwatch->accWallNs;
}

int64_t scu_stopwatch_cpu_ns(const SCUStopwatch* stopwatch) {
    SCU_ASSERT(stopwatch != nullptr);
    if (stopwatch->state == SCU_STOPWATCH_STATE_RUNNING) {
        int64_t cpuNs = scu_cpu_ns();
        if (cpuNs == -1) {
            return -1;
        }
        return stopwatch->accCpuNs + (cpuNs - stopwatch->startCpuNs);
    }
    return stopwatch->accCpuNs;
}

void scu_stopwatch_free(SCUStopwatch* stopwatch) {
    scu_free(stopwatch);
}