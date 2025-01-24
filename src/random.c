#ifdef _WIN32
#include <windows.h>
#include <bcrypt.h>
#else
#include <stdio.h>
#endif
#include <SCU/memory.h>
#include <SCU/random.h>

struct SCURandom {

    /** @brief Seed used to initialize the state of the `SCURandom`. */
    uint64_t seed;

    /**
     * @brief State of the `SCURandom`.
     *
     * @note This particular implementation is based on the
     * [xoshiro256**](https://prng.di.unimi.it/xoshiro256starstar.c) PRNG by David Blackman and
     * Sebastiano Vigna, which uses a state of `4 * 64 = 256` bits.
     * See [this website](https://prng.di.unimi.it/) to learn more about the generator and other
     * existing variants.
     */
    uint64_t state[4];

};

/**
 * @brief Rotates a given `uint64_t` value to the left by a specified number of bits.
 *
 * @param[in] value Value to rotate to the left.
 * @param[in] bits  Number of bits by which to rotate the value.
 * @return The given `uint64_t` value rotated to the left by the specified number of bits.
 */
static inline uint64_t scu_rotateLeft(uint64_t value, int32_t bits) {
    return (value << bits) | (value >> (64 - bits));
}

/**
 * @brief Advances the internal state of a given `SCURandom`.
 *
 * @param[in, out] random `SCURandom` to advance the internal state of.
 * @return A pseudorandom `uint64_t`.
 */
static inline uint64_t scu_next(SCURandom* random) {
    uint64_t result = scu_rotateLeft(random->state[1] * 5, 7) * 9;
    uint64_t temp = random->state[1] << 17;
    random->state[2] ^= random->state[0];
    random->state[3] ^= random->state[1];
    random->state[1] ^= random->state[2];
    random->state[0] ^= random->state[3];
    random->state[2] ^= temp;
    random->state[3] = scu_rotateLeft(random->state[3], 45);
    return result;
}

SCURandom* scu_random_new() {
    uint64_t seed;
#ifdef _WIN32
    NTSTATUS status = BCryptGenRandom(
        nullptr,
        (PUCHAR) &seed,
        sizeof(seed),
        BCRYPT_USE_SYSTEM_PREFERRED_RNG
    );
    if (!BCRYPT_SUCCESS(status)) {
        return nullptr;
    }
#else
    FILE* urandom = fopen("/dev/urandom", "rb");
    if (urandom == nullptr) {
        return nullptr;
    }
    if (fread(&seed, sizeof(seed), 1, urandom) < 1) {
        fclose(urandom);
        return nullptr;
    }
    if (fclose(urandom) == EOF) {
        return nullptr;
    }
#endif
    return scu_random_withSeed(seed);
}

SCURandom* scu_random_withSeed(uint64_t seed) {
    SCURandom* random = SCU_MALLOC(sizeof(SCURandom));
    if (random != nullptr) {
        scu_random_setSeed(random, seed);
    }
    return random;
}

int64_t scu_random_getSeed(const SCURandom* random) {
    return random->seed;
}

void scu_random_setSeed(SCURandom* random, uint64_t seed) {
    random->seed = seed;
    // Initialize the state with a simple [SplitMix64](https://prng.di.unimi.it/splitmix64.c)
    // generator as suggested by the authors [here](https://prng.di.unimi.it/xoshiro256starstar.c).
    for (int32_t i = 0; i < 4; i++) {
        uint64_t z = seed += 0x9E3779B97F4A7C15;
        z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9;
        z = (z ^ (z >> 27)) * 0x94D049BB133111EB;
        random->state[i] = z ^ (z >> 31);
    }
}

int32_t scu_random_int32(SCURandom* random, int32_t min, int32_t max) {
    if (min >= max) {
        return min;
    }
    // Cast to unsigned to avoid undefined behavior in case of a signed integer overflow.
    uint32_t range = ((uint32_t) max) - min;
    // Rejection sampling to generate uniformly distributed pseudorandom numbers and avoid the bias
    // that would otherwise be introduced by the modulo operator. Typically, very few iterations are
    // required to find a suitable pseudorandom number.
    uint32_t threshold = -range % range;
    uint32_t result;
    do {
        // We simply extract the required 32 bits from the top of the large pseudorandom `uint64_t`
        // generated by `scu_next()`.
        result = scu_next(random) >> 32;
    }
    while (result < threshold);
    return min + (result % range);
}

uint32_t scu_random_uint32(SCURandom* random, uint32_t min, uint32_t max) {
    if (min >= max) {
        return min;
    }
    uint32_t range = max - min;
    // Rejection sampling to generate uniformly distributed pseudorandom numbers and avoid the bias
    // that would otherwise be introduced by the modulo operator. Typically, very few iterations are
    // required to find a suitable pseudorandom number.
    uint32_t threshold = -range % range;
    uint32_t result;
    do {
        // We simply extract the required 32 bits from the top of the large pseudorandom `uint64_t`
        // generated by `scu_next()`.
        result = scu_next(random) >> 32;
    }
    while (result < threshold);
    return min + (result % range);
}

int64_t scu_random_int64(SCURandom* random, int64_t min, int64_t max) {
    if (min >= max) {
        return min;
    }
    // Cast to unsigned to avoid undefined behavior in case of a signed integer overflow.
    uint64_t range = ((uint64_t) max) - min;
    // Rejection sampling to generate uniformly distributed pseudorandom numbers and avoid the bias
    // that would otherwise be introduced by the modulo operator. Typically, very few iterations are
    // required to find a suitable pseudorandom number.
    uint64_t threshold = -range % range;
    uint64_t result;
    do {
        result = scu_next(random);
    }
    while (result < threshold);
    return min + (result % range);
}

uint64_t scu_random_uint64(SCURandom* random, uint64_t min, uint64_t max) {
    if (min >= max) {
        return min;
    }
    uint64_t range = max - min;
    // Rejection sampling to generate uniformly distributed pseudorandom numbers and avoid the bias
    // that would otherwise be introduced by the modulo operator. Typically, very few iterations are
    // required to find a suitable pseudorandom number.
    uint64_t threshold = -range % range;
    uint64_t result;
    do {
        result = scu_next(random);
    }
    while (result < threshold);
    return min + (result % range);
}

float scu_random_float(SCURandom* random, float min, float max) {
    if (min >= max) {
        return min;
    }
    // We generate a uniformly distributed `float` in the range [0.0F, 1.0F) as described by the
    // authors [here](https://prng.di.unimi.it/#remarks).
    float scale = (scu_next(random) >> 40) * (1.0F / (1UL << 24));
    return min + (scale * (max - min));
}

double scu_random_double(SCURandom* random, double min, double max) {
    if (min >= max) {
        return min;
    }
    // We generate a uniformly distributed `double` in the range [0.0F, 1.0F) as described by the
    // authors [here](https://prng.di.unimi.it/#remarks).
    double scale = (scu_next(random) >> 11) * (1.0 / (1ULL << 53));
    return min + (scale * (max - min));
}

void scu_random_free(SCURandom* random) {
    SCU_FREE(random);
}