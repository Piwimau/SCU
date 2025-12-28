#include "scu/alloc.h"
#include "scu/assert.h"
#include "scu/memory.h"
#include "scu/hash-set.h"

/** @brief Represents a bucket in a hash set. */
typedef struct SCUBucket {

    /** @brief The hash of the element stored in the bucket. */
    uint64_t hash;

    /** @brief Indicates whether the bucket is occupied. */
    bool isOccupied;

    /**
     * @brief The element stored in the bucket.
     *
     * @note This is a flexible array member, which is a aligned as strictly as
     * `max_align_t` to ensure proper alignment for any type with fundamental
     * alignment requirements. The actual size of the element is stored by the
     * hash set owning this bucket.
     */
    alignas(max_align_t) unsigned char elem[];

} SCUBucket;

struct SCUHashSet {

    /** @brief The size of each element (in bytes). */
    int64_t elemSize;

    /** @brief The effective size of each bucket (in bytes). */
    int64_t bucketSize;

    /**
     * @brief The maximum number of elements that could theoretically be stored.
     *
     * @note The capacity is always a power of two and equal to the number of
     * buckets. The actual number of elements that can be stored without a
     * reallocation is lower and depends on the load factor of the hash set.
     */
    int64_t capacity;

    /** @brief The current number of elements. */
    int64_t count;

    /** @brief A function used for hashing elements. */
    SCUHashFunc* hashFunc;

    /** @brief A function used for comparing elements for equality. */
    SCUEqualFunc* equalFunc;

    /**
     * @brief The buckets storing the elements.
     *
     * @note This is a dynamically allocated array of `capacity` buckets, or
     * `nullptr` if `capacity` is zero.
     */
    SCUBucket* buckets;

};

/** @brief The default capacity of a hash set. */
static constexpr int64_t SCU_DEFAULT_CAPACITY = 8;

/** @brief The numerator of the maximum load factor of a hash set. */
static constexpr int64_t SCU_MAX_LOAD_FACTOR_NUM = 9;

/** @brief The denominator of the maximum load factor of a hash set. */
static constexpr int64_t SCU_MAX_LOAD_FACTOR_DEN = 10;

/** @brief The growth factor for increasing the capacity of a hash set. */
static constexpr int64_t SCU_GROWTH_FACTOR = 2;

[[nodiscard]]
SCUHashSet* scu_hash_set_new(
    int64_t elemSize,
    SCUHashFunc* hashFunc,
    SCUEqualFunc* equalFunc
) {
    return scu_hash_set_new_with_capacity(
        elemSize,
        SCU_DEFAULT_CAPACITY,
        hashFunc,
        equalFunc
    );
}

/**
 * @brief Returns the smallest power of two greater than or equal to a specified
 * value.
 *
 * @param[in] n The value to examine.
 * @return The smallest power of two greater than or equal to the specified
 * value.
 */
static inline int64_t scu_next_power_of_two(int64_t n) {
    SCU_ASSERT((n >= 0) && (n <= (INT64_C(1) << 62)));
    if (n <= 1) {
        return 1;
    }
    uint64_t v = (uint64_t) n;
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v |= v >> 32;
    v++;
    return (int64_t) v;
}

[[nodiscard]]
SCUHashSet* scu_hash_set_new_with_capacity(
    int64_t elemSize,
    int64_t capacity,
    SCUHashFunc* hashFunc,
    SCUEqualFunc* equalFunc
) {
    SCU_ASSERT(elemSize > 0);
    SCU_ASSERT(capacity >= 0);
    SCU_ASSERT(hashFunc != nullptr);
    SCU_ASSERT(equalFunc != nullptr);
    SCUHashSet* hashSet = scu_malloc(SCU_SIZEOF(SCUHashSet));
    if (hashSet == nullptr) {
        return nullptr;
    }
    hashSet->elemSize = elemSize;
    hashSet->bucketSize = SCU_SIZEOF(SCUBucket) + elemSize;
    hashSet->count = 0;
    hashSet->hashFunc = hashFunc;
    hashSet->equalFunc = equalFunc;
    if (capacity > 0) {
        hashSet->capacity = scu_next_power_of_two(capacity);
        hashSet->buckets = scu_calloc(hashSet->capacity, hashSet->bucketSize);
        if (hashSet->buckets == nullptr) {
            scu_free(hashSet);
            return nullptr;
        }
    }
    else {
        hashSet->capacity = 0;
        hashSet->buckets = nullptr;
    }
    return hashSet;
}

[[nodiscard]]
SCUHashSet* scu_hash_set_clone(const SCUHashSet* hashSet) {
    SCU_ASSERT(hashSet != nullptr);
    SCUHashSet* clone = scu_malloc(SCU_SIZEOF(SCUHashSet));
    if (clone == nullptr) {
        return nullptr;
    }
    clone->elemSize = hashSet->elemSize;
    clone->bucketSize = hashSet->bucketSize;
    clone->capacity = hashSet->capacity;
    clone->count = hashSet->count;
    clone->hashFunc = hashSet->hashFunc;
    clone->equalFunc = hashSet->equalFunc;
    if (hashSet->capacity > 0) {
        clone->buckets = scu_malloc(hashSet->bucketSize * hashSet->capacity);
        if (clone->buckets == nullptr) {
            scu_free(clone);
            return nullptr;
        }
        scu_memcpy(
            clone->buckets,
            hashSet->buckets,
            hashSet->bucketSize * hashSet->capacity
        );
    }
    else {
        clone->buckets = nullptr;
    }
    return clone;
}

int64_t scu_hash_set_capacity(const SCUHashSet* hashSet) {
    SCU_ASSERT(hashSet != nullptr);
    return hashSet->capacity;
}

int64_t scu_hash_set_count(const SCUHashSet* hashSet) {
    SCU_ASSERT(hashSet != nullptr);
    return hashSet->count;
}

/**
 * @brief Returns a pointer to a bucket at a specified index.
 *
 * @param[in] buckets    A pointer to an array of buckets.
 * @param[in] index      The index of the bucket to retrieve.
 * @param[in] bucketSize The effective size of each bucket (in bytes).
 * @return A pointer to the bucket at the specified index.
 */
static inline SCUBucket* scu_bucket_at(
    SCUBucket* buckets,
    int64_t index,
    int64_t bucketSize
) {
    SCU_ASSERT(buckets != nullptr);
    SCU_ASSERT(index >= 0);
    SCU_ASSERT(bucketSize > SCU_SIZEOF(SCUBucket));
    return (SCUBucket*) (((unsigned char*) buckets) + (index * bucketSize));
}

/**
 * @brief Returns the ideal bucket index for a specified hash.
 *
 * @param[in] hash     The hash to examine.
 * @param[in] capacity The capacity (in number of buckets).
 * @return The ideal bucket index for the specified hash.
 */
static inline int64_t scu_ideal_index(uint64_t hash, int64_t capacity) {
    SCU_ASSERT(capacity > 0);
    return (int64_t) (hash & ((uint64_t) (capacity - 1)));
}

/**
 * @brief Wraps an index to fit within the bounds of a specified capacity.
 *
 * @param[in] index    The index to wrap.
 * @param[in] capacity The capacity (in number of buckets).
 * @return The wrapped index within the bounds of the specified capacity.
 */
static inline int64_t scu_wrap_index(int64_t index, int64_t capacity) {
    SCU_ASSERT(capacity > 0);
    return (int64_t) ((uint64_t) index & (uint64_t) (capacity - 1));
}

/**
 * @brief Returns the probe distance of an element with a specified hash at a
 * given index.
 *
 * @note The probe distance is the number of positions an element had to travel
 * forward (with wrap-around) from its ideal position due to collisions.
 *
 * @param[in] hash     The hash of the element.
 * @param[in] index    The index of the element.
 * @param[in] capacity The capacity (in number of buckets).
 * @return The probe distance of the element.
 */
static inline int64_t scu_probe_distance(
    uint64_t hash,
    int64_t index,
    int64_t capacity
) {
    SCU_ASSERT(capacity > 0);
    SCU_ASSERT((index >= 0) && (index < capacity));
    int64_t idealIndex = scu_ideal_index(hash, capacity);
    return scu_wrap_index(index - idealIndex, capacity);
}

/**
 * @brief Rehashes old buckets by adding their elements to a specified hash set.
 *
 * @warning This function assumes that the specified hash set has enough
 * capacity to hold all elements of the old buckets. Additionally, the contents
 * of `oldBuckets` may be modified during the rehashing process for optimization
 * purposes. After this function returns, the state of `oldBuckets` is
 * undefined.
 *
 * @param[in, out] hashSet     The hash set to rehash into.
 * @param[in, out] oldBuckets  The old buckets to rehash.
 * @param[in]      oldCapacity The old capacity (in number of buckets).
 */
static inline void scu_hash_set_rehash_buckets(
    SCUHashSet* hashSet,
    SCUBucket* oldBuckets,
    int64_t oldCapacity
) {
    SCU_ASSERT(hashSet != nullptr);
    SCU_ASSERT(oldBuckets != nullptr);
    SCU_ASSERT(oldCapacity > 0);
    for (int64_t i = 0; i < oldCapacity; i++) {
        SCUBucket* oldBucket = scu_bucket_at(
            oldBuckets,
            i,
            hashSet->bucketSize
        );
        if (oldBucket->isOccupied) {
            int64_t index = scu_ideal_index(oldBucket->hash, hashSet->capacity);
            int64_t distance = 0;
            while (true) {
                SCUBucket* newBucket = scu_bucket_at(
                    hashSet->buckets,
                    index,
                    hashSet->bucketSize
                );
                if (!newBucket->isOccupied) {
                    scu_memcpy(newBucket, oldBucket, hashSet->bucketSize);
                    hashSet->count++;
                    break;
                }
                int64_t otherDistance = scu_probe_distance(
                    newBucket->hash,
                    index,
                    hashSet->capacity
                );
                if (distance > otherDistance) {
                    scu_memswap(oldBucket, newBucket, hashSet->bucketSize);
                    distance = otherDistance;
                }
                index = scu_wrap_index(index + 1, hashSet->capacity);
                distance++;
            }
        }
    }
}

SCUError scu_hash_set_ensure_capacity(SCUHashSet* hashSet, int64_t capacity) {
    SCU_ASSERT(hashSet != nullptr);
    SCU_ASSERT(capacity >= 0);
    int64_t minCapacity = ((capacity * SCU_MAX_LOAD_FACTOR_DEN)
        + SCU_MAX_LOAD_FACTOR_NUM - 1) / SCU_MAX_LOAD_FACTOR_NUM;
    if (hashSet->capacity >= minCapacity) {
        return SCU_ERROR_NONE;
    }
    int64_t newCapacity = scu_next_power_of_two(minCapacity);
    SCUBucket* newBuckets = scu_calloc(newCapacity, hashSet->bucketSize);
    if (newBuckets == nullptr) {
        return SCU_ERROR_OUT_OF_MEMORY;
    }
    int64_t oldCapacity = hashSet->capacity;
    int64_t oldCount = hashSet->count;
    SCUBucket* oldBuckets = hashSet->buckets;
    hashSet->capacity = newCapacity;
    hashSet->count = 0;
    hashSet->buckets = newBuckets;
    if (oldCount > 0) {
        scu_hash_set_rehash_buckets(hashSet, oldBuckets, oldCapacity);
    }
    scu_free(oldBuckets);
    return SCU_ERROR_NONE;
}

SCUError scu_hash_set_add(
    SCUHashSet* restrict hashSet,
    const void* restrict elem
) {
    SCU_ASSERT(hashSet != nullptr);
    SCU_ASSERT(elem != nullptr);
    if ((hashSet->count * SCU_MAX_LOAD_FACTOR_DEN)
            >= (hashSet->capacity * SCU_MAX_LOAD_FACTOR_NUM)) {
        int64_t newCapacity = (hashSet->capacity == 0)
            ? SCU_DEFAULT_CAPACITY
            : (hashSet->capacity * SCU_GROWTH_FACTOR);
        SCUError error = scu_hash_set_ensure_capacity(hashSet, newCapacity);
        if (error != SCU_ERROR_NONE) {
            return error;
        }
    }
    SCUBucket* tempBucket = scu_malloc(hashSet->bucketSize);
    if (tempBucket == nullptr) {
        return SCU_ERROR_OUT_OF_MEMORY;
    }
    tempBucket->hash = hashSet->hashFunc(elem);
    tempBucket->isOccupied = true;
    scu_memcpy(tempBucket->elem, elem, hashSet->elemSize);
    int64_t index = scu_ideal_index(tempBucket->hash, hashSet->capacity);
    int64_t distance = 0;
    while (true) {
        SCUBucket* bucket = scu_bucket_at(
            hashSet->buckets,
            index,
            hashSet->bucketSize
        );
        if (!bucket->isOccupied) {
            scu_memcpy(bucket, tempBucket, hashSet->bucketSize);
            hashSet->count++;
            scu_free(tempBucket);
            return SCU_ERROR_NONE;
        }
        if ((bucket->hash == tempBucket->hash)
                && hashSet->equalFunc(bucket->elem, tempBucket->elem)) {
            scu_free(tempBucket);
            return SCU_ERROR_ALREADY_PRESENT;
        }
        int64_t otherDistance = scu_probe_distance(
            bucket->hash,
            index,
            hashSet->capacity
        );
        if (distance > otherDistance) {
            scu_memswap(bucket, tempBucket, hashSet->bucketSize);
            distance = otherDistance;
        }
        index = scu_wrap_index(index + 1, hashSet->capacity);
        distance++;
    }
}

bool scu_hash_set_contains(const SCUHashSet* hashSet, const void* elem) {
    SCU_ASSERT(hashSet != nullptr);
    SCU_ASSERT(elem != nullptr);
    if (hashSet->count == 0) {
        return false;
    }
    uint64_t hash = hashSet->hashFunc(elem);
    int64_t index = scu_ideal_index(hash, hashSet->capacity);
    int64_t distance = 0;
    while (true) {
        SCUBucket* bucket = scu_bucket_at(
            hashSet->buckets,
            index,
            hashSet->bucketSize
        );
        if (!bucket->isOccupied) {
            return false;
        }
        int64_t otherDistance = scu_probe_distance(
            bucket->hash,
            index,
            hashSet->capacity
        );
        if (distance > otherDistance) {
            return false;
        }
        if ((bucket->hash == hash) && hashSet->equalFunc(bucket->elem, elem)) {
            return true;
        }
        index = scu_wrap_index(index + 1, hashSet->capacity);
        distance++;
    }
}

bool scu_hash_set_remove(
    SCUHashSet* restrict hashSet,
    const void* restrict elem
) {
    SCU_ASSERT(hashSet != nullptr);
    SCU_ASSERT(elem != nullptr);
    if (hashSet->count == 0) {
        return false;
    }
    uint64_t hash = hashSet->hashFunc(elem);
    int64_t index = scu_ideal_index(hash, hashSet->capacity);
    int64_t distance = 0;
    while (true) {
        SCUBucket* bucket = scu_bucket_at(
            hashSet->buckets,
            index,
            hashSet->bucketSize
        );
        if (!bucket->isOccupied) {
            return false;
        }
        int64_t otherDistance = scu_probe_distance(
            bucket->hash,
            index,
            hashSet->capacity
        );
        if (distance > otherDistance) {
            return false;
        }
        if ((bucket->hash == hash) && hashSet->equalFunc(bucket->elem, elem)) {
            break;
        }
        index = scu_wrap_index(index + 1, hashSet->capacity);
        distance++;
    }
    SCUBucket* bucket = scu_bucket_at(
        hashSet->buckets,
        index,
        hashSet->bucketSize
    );
    while (true) {
        int64_t nextIndex = scu_wrap_index(index + 1, hashSet->capacity);
        SCUBucket* nextBucket = scu_bucket_at(
            hashSet->buckets,
            nextIndex,
            hashSet->bucketSize
        );
        if (!nextBucket->isOccupied) {
            break;
        }
        int64_t nextDistance = scu_probe_distance(
            nextBucket->hash,
            nextIndex,
            hashSet->capacity
        );
        if (nextDistance == 0) {
            break;
        }
        scu_memcpy(bucket, nextBucket, hashSet->bucketSize);
        index = nextIndex;
        bucket = nextBucket;
    }
    bucket->isOccupied = false;
    hashSet->count--;
    return true;
}

void scu_hash_set_clear(SCUHashSet* hashSet) {
    SCU_ASSERT(hashSet != nullptr);
    if (hashSet->count > 0) {
        for (int64_t i = 0; i < hashSet->capacity; i++) {
            SCUBucket* bucket = scu_bucket_at(
                hashSet->buckets,
                i,
                hashSet->bucketSize
            );
            bucket->isOccupied = false;
        }
        hashSet->count = 0;
    }
}

SCUError scu_hash_set_trim_excess(SCUHashSet* hashSet) {
    SCU_ASSERT(hashSet != nullptr);
    if (hashSet->count == 0) {
        scu_free(hashSet->buckets);
        hashSet->buckets = nullptr;
        hashSet->capacity = 0;
        return SCU_ERROR_NONE;
    }
    int64_t minCapacity = ((hashSet->count * SCU_MAX_LOAD_FACTOR_DEN)
        + SCU_MAX_LOAD_FACTOR_NUM - 1) / SCU_MAX_LOAD_FACTOR_NUM;
    int64_t newCapacity = scu_next_power_of_two(minCapacity);
    if (hashSet->capacity <= newCapacity) {
        return SCU_ERROR_NONE;
    }
    SCUBucket* newBuckets = scu_calloc(newCapacity, hashSet->bucketSize);
    if (newBuckets == nullptr) {
        return SCU_ERROR_OUT_OF_MEMORY;
    }
    int64_t oldCapacity = hashSet->capacity;
    SCUBucket* oldBuckets = hashSet->buckets;
    hashSet->capacity = newCapacity;
    hashSet->count = 0;
    hashSet->buckets = newBuckets;
    scu_hash_set_rehash_buckets(hashSet, oldBuckets, oldCapacity);
    scu_free(oldBuckets);
    return SCU_ERROR_NONE;
}

SCUHashSetIter scu_hash_set_iter(const SCUHashSet* hashSet) {
    SCU_ASSERT(hashSet != nullptr);
    return (SCUHashSetIter) { .hashSet = (SCUHashSet*) hashSet, .index = -1 };
}

bool scu_hash_set_iter_move_next(SCUHashSetIter* iter) {
    SCU_ASSERT(iter != nullptr);
    SCU_ASSERT(iter->hashSet != nullptr);
    SCUHashSet* hashSet = iter->hashSet;
    int64_t index = iter->index;
    SCU_ASSERT((index >= -1) && (index <= hashSet->capacity));
    if (hashSet->count == 0) {
        iter->index = hashSet->capacity;
        return false;
    }
    index++;
    while (index < hashSet->capacity) {
        SCUBucket* bucket = scu_bucket_at(
            hashSet->buckets,
            index,
            hashSet->bucketSize
        );
        if (bucket->isOccupied) {
            iter->index = index;
            return true;
        }
        index++;
    }
    iter->index = hashSet->capacity;
    return false;
}

void* scu_hash_set_iter_current(const SCUHashSetIter* iter) {
    SCU_ASSERT(iter != nullptr);
    SCU_ASSERT(iter->hashSet != nullptr);
    SCUHashSet* hashSet = iter->hashSet;
    int64_t index = iter->index;
    SCU_ASSERT((index >= 0) && (index < hashSet->capacity));
    SCUBucket* bucket = scu_bucket_at(
        hashSet->buckets,
        index,
        hashSet->bucketSize
    );
    SCU_ASSERT(bucket->isOccupied);
    return bucket->elem;
}

void scu_hash_set_iter_reset(SCUHashSetIter* iter) {
    SCU_ASSERT(iter != nullptr);
    SCU_ASSERT(iter->hashSet != nullptr);
    SCU_ASSERT((iter->index >= -1) && (iter->index <= iter->hashSet->capacity));
    iter->index = -1;
}

void scu_hash_set_free(SCUHashSet* hashSet) {
    if (hashSet != nullptr) {
        scu_free(hashSet->buckets);
        hashSet->buckets = nullptr;
        hashSet->capacity = 0;
        hashSet->count = 0;
        scu_free(hashSet);
    }
}