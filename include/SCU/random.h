#ifndef SCU_RANDOM_H
#define SCU_RANDOM_H

#include <stdint.h>

/**
 * @brief Represents a pseudorandom number generator (PRNG).
 *
 * @warning Although fast and of relatively high quality, `SCURandom` is not a cryptographically
 * secure pseudorandom number generator (CSPRNG) and should not be used for such purposes.
 */
typedef struct SCURandom SCURandom;

/**
 * @brief Allocates and initializes a new `SCURandom` with a default seed.
 *
 * @warning An `SCURandom` returned by this function is dynamically allocated and must be passed to
 * `scu_random_free()` to avoid a memory leak.
 *
 * @return A pointer to a new initialized `SCURandom` on success, or a `nullptr` if an out-of-memory
 * condition occurred.
 */
SCURandom* scu_random_new();

/**
 * @brief Allocates and initializes a new `SCURandom` with a given seed.
 *
 * @warning An `SCURandom` returned by this function is dynamically allocated and must be passed to
 * `scu_random_free()` to avoid a memory leak.
 *
 * @param[in] seed Seed to initialize the `SCURandom` with.
 * @return A pointer to a new initialized `SCURandom` on success, or a `nullptr` if an out-of-memory
 * condition occurred.
 */
SCURandom* scu_random_withSeed(uint64_t seed);

/**
 * @brief Returns the seed of a given `SCURandom`.
 *
 * @note If the `SCURandom` has been reseeded, this function returns the last seed used for
 * `scu_random_setSeed()`. Otherwise it returns the seed the `SCURandom` was initialized with
 * by `scu_random_new()` or `scu_random_withSeed()`.
 *
 * @param[in] random `SCURandom` to get the seed of.
 * @return The seed of the given `SCURandom`.
 */
int64_t scu_random_getSeed(const SCURandom* random);

/**
 * @brief Reseeds a given `SCURandom` with a specified seed.
 *
 * @param[in, out] random `SCURandom` to reseed.
 * @param[in]      seed   Seed to reseed the `SCURandom` with.
 */
void scu_random_setSeed(SCURandom* random, uint64_t seed);

/**
 * @brief Returns a pseudorandom `int32_t` between min (inclusive) and max (exclusive).
 *
 * @note If `min` is greater than or equal to `max`, `min` is returned.
 *
 * @param[in, out] random `SCURandom` to use.
 * @param[in]      min    Minimum value to return (inclusive).
 * @param[in]      max    Maximum value to return (exclusive).
 * @return A pseudorandom `int32_t` between min (inclusive) and max (exclusive).
 */
int32_t scu_random_int32(SCURandom* random, int32_t min, int32_t max);

/**
 * @brief Returns a pseudorandom `uint32_t` between min (inclusive) and max (exclusive).
 *
 * @note If `min` is greater than or equal to `max`, `min` is returned.
 *
 * @param[in, out] random `SCURandom` to use.
 * @param[in]      min    Minimum value to return (inclusive).
 * @param[in]      max    Maximum value to return (exclusive).
 * @return A pseudorandom `uint32_t` between min (inclusive) and max (exclusive).
 */
uint32_t scu_random_uint32(SCURandom* random, uint32_t min, uint32_t max);

/**
 * @brief Returns a pseudorandom `int64_t` between min (inclusive) and max (exclusive).
 *
 * @note If `min` is greater than or equal to `max`, `min` is returned.
 *
 * @param[in, out] random `SCURandom` to use.
 * @param[in]      min    Minimum value to return (inclusive).
 * @param[in]      max    Maximum value to return (exclusive).
 * @return A pseudorandom `int64_t` between min (inclusive) and max (exclusive).
 */
int64_t scu_random_int64(SCURandom* random, int64_t min, int64_t max);

/**
 * @brief Returns a pseudorandom `uint64_t` between min (inclusive) and max (exclusive).
 *
 * @note If `min` is greater than or equal to `max`, `min` is returned.
 *
 * @param[in, out] random `SCURandom` to use.
 * @param[in]      min    Minimum value to return (inclusive).
 * @param[in]      max    Maximum value to return (exclusive).
 * @return A pseudorandom `uint64_t` between min (inclusive) and max (exclusive).
 */
uint64_t scu_random_uint64(SCURandom* random, uint64_t min, uint64_t max);

/**
 * @brief Returns a pseudorandom `float` between min (inclusive) and max (exclusive).
 *
 * @note If `min` is greater than or equal to `max`, `min` is returned.
 *
 * @param[in, out] random `SCURandom` to use.
 * @param[in]      min    Minimum value to return (inclusive).
 * @param[in]      max    Maximum value to return (exclusive).
 * @return A pseudorandom `float` between min (inclusive) and max (exclusive).
 */
float scu_random_float(SCURandom* random, float min, float max);

/**
 * @brief Returns a pseudorandom `double` between min (inclusive) and max (exclusive).
 *
 * @note If `min` is greater than or equal to `max`, `min` is returned.
 *
 * @param[in, out] random `SCURandom` to use.
 * @param[in]      min    Minimum value to return (inclusive).
 * @param[in]      max    Maximum value to return (exclusive).
 * @return A pseudorandom `double` between min (inclusive) and max (exclusive).
 */
double scu_random_double(SCURandom* random, double min, double max);

/**
 * @brief Deallocates a given `SCURandom`.
 *
 * @note For convenience, `random` is allowed to be a `nullptr`.
 *
 * @warning Any use of the `SCURandom` after it has been deallocated results in undefined behavior.
 *
 * @param[in, out] random `SCURandom` to deallocate.
 */
void scu_random_free(SCURandom* random);

#endif