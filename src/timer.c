#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif
#include <SCU/memory.h>
#include <SCU/timer.h>

struct SCUTimer {

    /** @brief Start timestamp of the current CPU time interval (in seconds). */
    double startCPUTimestamp;

    /** @brief Elapsed CPU time since the start of the current interval (in seconds). */
    double elapsedCPUTime;

    /** @brief Start timestamp of the current wall time interval (in seconds). */
    double startWallTimestamp;

    /** @brief Elapsed wall time since the start of the current interval (in seconds). */
    double elapsedWallTime;

    /** @brief Whether the `SCUTimer` is currently running. */
    bool isRunning;

};

#ifdef _WIN32

/** @brief Number of file time ticks (100 ns intervals) in a second. */
static constexpr double SCU_FILETIME_TICKS_PER_SECOND = 1.0E7;

/**
 * @brief Converts a `FILETIME` structure to seconds.
 *
 * @param[in] filetime `FILETIME` structure to convert to seconds.
 * @return The number of seconds equivalent to the given `FILETIME` structure.
 */
static inline double scu_filetimeToSeconds(FILETIME filetime) {
    ULARGE_INTEGER temp;
    temp.LowPart = filetime.dwLowDateTime;
    temp.HighPart = filetime.dwHighDateTime;
    return temp.QuadPart / SCU_FILETIME_TICKS_PER_SECOND;
}

#else

/** @brief Number of nanoseconds in a second. */
static constexpr double SCU_NANOSECONDS_PER_SECOND = 1.0E9;

/**
 * @brief Converts a `timespec` structure to seconds.
 *
 * @param[in] timespec `timespec` structure to convert to seconds.
 * @return The number of seconds equivalent to the given `timespec` structure.
 */
static inline double scu_timespecToSeconds(struct timespec timespec) {
    return timespec.tv_sec + (timespec.tv_nsec / SCU_NANOSECONDS_PER_SECOND);
}

#endif

/**
 * @brief Returns a timestamp for measuring the elapsed CPU time (in seconds).
 *
 * @return A timestamp for measuring the elapsed CPU time (in seconds), or a negative value if an
 * error ocurred.
 */
static inline double scu_cpuTimestamp() {
#ifdef _WIN32
    FILETIME creationTime, exitTime, kernelTime, userTime;
    if (!GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime, &kernelTime, &userTime)) {
        return -1.0;
    }
    return scu_filetimeToSeconds(kernelTime) + scu_filetimeToSeconds(userTime);
#else
    struct timespec timespec;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &timespec) < 0) {
        return -1.0;
    }
    return scu_timespecToSeconds(timespec);
#endif
}

/**
 * @brief Returns a timestamp for measuring the elapsed wall time (in seconds).
 *
 * @return A timestamp for measuring the elapsed wall time (in seconds), or a negative value if an
 * error ocurred.
 */
static inline double scu_wallTimestamp() {
#ifdef _WIN32
    LARGE_INTEGER frequency, counter;
    if (!QueryPerformanceFrequency(&frequency) || !QueryPerformanceCounter(&counter)) {
        return -1.0;
    }
    return ((double) counter.QuadPart) / frequency.QuadPart;
#else
    struct timespec timespec;
    if (clock_gettime(CLOCK_MONOTONIC, &timespec) < 0) {
        return -1.0;
    }
    return scu_timespecToSeconds(timespec);
#endif
}

SCUTimer* scu_timer_new() {
    SCUTimer* timer = SCU_MALLOC(sizeof(SCUTimer));
    if (timer != nullptr) {
        *timer = (SCUTimer) { };
    }
    return timer;
}

bool scu_timer_start(SCUTimer* timer) {
    if (!timer->isRunning) {
        double cpuTimestamp = scu_cpuTimestamp();
        double wallTimestamp = scu_wallTimestamp();
        if ((cpuTimestamp < 0.0) || (wallTimestamp < 0.0)) {
            return false;
        }
        timer->startCPUTimestamp = cpuTimestamp;
        timer->startWallTimestamp = wallTimestamp;
        timer->isRunning = true;
    }
    return true;
}

bool scu_timer_stop(SCUTimer* timer) {
    if (timer->isRunning) {
        double cpuTimestamp = scu_cpuTimestamp();
        double wallTimestamp = scu_wallTimestamp();
        if ((cpuTimestamp < 0.0) || (wallTimestamp < 0.0)) {
            return false;
        }
        timer->elapsedCPUTime += cpuTimestamp - timer->startCPUTimestamp;
        timer->elapsedWallTime += wallTimestamp - timer->startWallTimestamp;
        timer->isRunning = false;
    }
    return true;
}

void scu_timer_reset(SCUTimer* timer) {
    *timer = (SCUTimer) { };
}

bool scu_timer_restart(SCUTimer* timer) {
    scu_timer_reset(timer);
    return scu_timer_start(timer);
}

bool scu_timer_isRunning(const SCUTimer* timer) {
    return timer->isRunning;
}

double scu_timer_elapsedCPUTime(const SCUTimer* timer) {
    if (!timer->isRunning) {
        return timer->elapsedCPUTime;
    }
    double cpuTimestamp = scu_cpuTimestamp();
    if (cpuTimestamp < 0.0) {
        return cpuTimestamp;
    }
    return timer->elapsedCPUTime + (cpuTimestamp - timer->startCPUTimestamp);
}

double scu_timer_elapsedWallTime(const SCUTimer* timer) {
    if (!timer->isRunning) {
        return timer->elapsedWallTime;
    }
    double wallTimestamp = scu_wallTimestamp();
    if (wallTimestamp < 0.0) {
        return wallTimestamp;
    }
    return timer->elapsedWallTime + (wallTimestamp - timer->startWallTimestamp);
}

void scu_timer_free(SCUTimer* timer) {
    SCU_FREE(timer);
}