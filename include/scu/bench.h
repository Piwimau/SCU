#ifndef SCU_BENCH_H
#define SCU_BENCH_H

#include "scu/error.h"
#include "scu/time.h"
#include "scu/types.h"

/** @brief Represents the statistics of a benchmark. */
typedef struct SCUBenchStats {

    /**
     * @brief The minimum time taken for a single iteration (in nanoseconds).
     */
    SCUi64 minNs;

    /**
     * @brief The maximum time taken for a single iteration (in nanoseconds).
     */
    SCUi64 maxNs;

    /** @brief The mean time taken for a single iteration (in nanoseconds). */
    SCUf64 meanNs;

    /** @brief The median time taken for a single iteration (in nanoseconds). */
    SCUf64 medianNs;

    /**
     * @brief The standard deviation of the time taken for a single iteration
     * (in nanoseconds).
     */
    SCUf64 stdDevNs;

} SCUBenchStats;

/** @brief Represents a result of a benchmark. */
typedef struct SCUBenchResult {

    /** @brief The wall time statistics. */
    SCUBenchStats wall;

    /** @brief The CPU time statistics. */
    SCUBenchStats cpu;

    /** @brief The number of iterations performed. */
    SCUisize iterations;

    /** @brief An error code indicating whether the benchmark was successful. */
    SCUError error;

} SCUBenchResult;

/**
 * @brief Represents a context for a benchmark.
 *
 * @warning This structure is an implementation detail and not intended to be
 * used by callers. The internal representation should not be relied upon and
 * may change without notice. Most importantly, the behavior is undefined if its
 * fields are accessed directly.
 */
typedef struct SCUBenchCtx {

    /** @brief The timing mode for measuring CPU time. */
    SCUTimingMode timingMode;

    /** @brief The timing result for the current iteration. */
    SCUTimingResult timingResult;

    /** @brief The wall time samples (in nanoseconds). */
    SCUi64* wallSamples;

    /** @brief The CPU time samples (in nanoseconds). */
    SCUi64* cpuSamples;

    /** @brief The number of warmup iterations. */
    SCUisize warmup;

    /** @brief The number of iterations to perform (after warmup). */
    SCUisize iterations;

    /** @brief The current iteration. */
    SCUisize iteration;

    /** @brief An error code indicating whether the benchmark was successful. */
    SCUError error;

    /** @brief A pointer for storing the result of the benchmark. */
    SCUBenchResult* benchResult;

} SCUBenchCtx;

/**
 * @brief Allocates and initializes a new benchmark context.
 *
 * @note This function is an implementation detail and not intended to be used
 * by callers directly. Use the `SCU_BENCH()` macro instead.
 *
 * @warning Although the returned context itself is not dynamically allocated,
 * some of its associated resources (e.g., the lists of samples) are. It must be
 * passed to `scu_bench_ctx_is_running()` and `scu_bench_ctx_advance()`, which
 * manage the underlying resources and deallocate them when the benchmark is
 * complete.
 *
 * @param[in] timingMode  The timing mode for measuring CPU time.
 * @param[in] warmup      The number of warmup iterations.
 * @param[in] iterations  The number of iterations to perform (after warmup).
 * @param[in] benchResult A pointer for storing the result of the benchmark.
 * @return A new benchmark context.
 */
[[nodiscard]]
SCUBenchCtx scu_bench_ctx_new(
    SCUTimingMode timingMode,
    SCUisize warmup,
    SCUisize iterations,
    SCUBenchResult* benchResult
);

/**
 * @brief Determines whether a specified benchmark is still running.
 *
 * @note This function is an implementation detail and not intended to be used
 * by callers directly. Use the `SCU_BENCH()` macro instead.
 *
 * @param[in, out] ctx The benchmark context to examine.
 * @return `true` if the specified benchmark is still running, otherwise
 * `false`.
 */
bool scu_bench_ctx_is_running(SCUBenchCtx* ctx);

/**
 * @brief Advances a specified benchmark to the next iteration.
 *
 * @note This function is an implementation detail and not intended to be used
 * by callers directly. Use the `SCU_BENCH()` macro instead.
 *
 * @param[in, out] ctx The benchmark context to advance.
 */
void scu_bench_ctx_advance(SCUBenchCtx* ctx);

/**
 * @brief Benchmarks a block of code.
 *
 * This macro simplifies the process of benchmarking a block of code. It creates
 * a new benchmark context, executes the block of code for the specified number
 * of iterations (with an optional number of warmup iterations), and stores the
 * benchmark results in `*result`.
 *
 * The following example demonstrates the basic usage of this macro:
 *
 * ```c
 * SCUBenchResult result;
 * SCU_BENCH(SCU_TIMING_MODE_PROCESS, 10, 100, &result) {
 *     // Some code to be benchmarked...
 * }
 * if (result.error != SCU_ERROR_NONE) {
 *     // Handle the error...
 * }
 * else {
 *     // Use result.wall, result.cpu, and result.iterations...
 * }
 * ```
 *
 * @note If the benchmark cannot be started, the block of code is not executed.
 * In this case, `result->error` is set to an appropriate error code. This is
 * also the case if retrieving the elapsed times fails after executing the block
 * of code, or if the benchmark fails for any other reason. In all of these
 * cases, `result->wall` and `result->cpu` are zero-initialized, and
 * `result->iterations` is set to the number of iterations that were
 * successfully completed before the error occurred (which may be zero).
 *
 * Zero may be passed both to `warmup` and `iterations` to indicate that no
 * warmup or (real) iterations are required. In this case, the benchmark is
 * still considered to be successfully executed, and `result->error` is set to
 * `SCU_ERROR_NONE`. Additionally, `result->wall`, `result->cpu`, and
 * `result->iterations` are zero-initialized.
 *
 * @warning Exiting the block of code early by means of jump statements (such as
 * `return` or `goto`) will result in memory leaks, as the underlying benchmark
 * context is not properly advanced to the next iteration or deallocated after
 * the last iteration.
 *
 * @param[in] mode       The timing mode for measuring CPU time.
 * @param[in] warmup     The number of warmup iterations.
 * @param[in] iterations The number of iterations to perform (after warmup).
 * @param[in] result     A pointer for storing the result of the benchmark.
 */
#define SCU_BENCH(mode, warmup, iterations, result)       \
    for (                                                 \
        SCUBenchCtx scuCtx = scu_bench_ctx_new(           \
            (mode),                                       \
            (warmup),                                     \
            (iterations),                                 \
            (result)                                      \
        );                                                \
        scu_bench_ctx_is_running(&scuCtx);                \
        scu_bench_ctx_advance(&scuCtx)                    \
    )                                                     \
        SCU_TIME(scuCtx.timingMode, &scuCtx.timingResult)

#endif