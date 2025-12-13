#include "scu/alloc.h"
#include "scu/assert.h"
#include "scu/memory.h"
#include "scu/set.h"

struct SCUBucket {

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

};

/** @brief Represents a bucket in a hash set. */
typedef struct SCUBucket SCUBucket;

struct SCUSet {

    /** @brief The size of each element (in bytes). */
    int64_t elemSize;

    /** @brief The stride between consecutive buckets (in bytes). */
    int64_t stride;

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
SCUSet* scu_set_new(
    int64_t elemSize,
    SCUHashFunc* hashFunc,
    SCUEqualFunc* equalFunc
) {
    return scu_set_new_with_capacity(
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
    SCU_ASSERT((n >= 0) && (n <= (1LL << 62)));
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
SCUSet* scu_set_new_with_capacity(
    int64_t elemSize,
    int64_t capacity,
    SCUHashFunc* hashFunc,
    SCUEqualFunc* equalFunc
) {
    SCU_ASSERT(elemSize > 0);
    SCU_ASSERT(capacity >= 0);
    SCU_ASSERT(hashFunc != nullptr);
    SCU_ASSERT(equalFunc != nullptr);
    SCUSet* set = scu_malloc(SCU_SIZEOF(SCUSet));
    if (set == nullptr) {
        return nullptr;
    }
    set->elemSize = elemSize;
    set->stride = SCU_SIZEOF(SCUBucket) + elemSize;
    set->count = 0;
    set->hashFunc = hashFunc;
    set->equalFunc = equalFunc;
    if (capacity > 0) {
        set->capacity = scu_next_power_of_two(capacity);
        set->buckets = scu_calloc(set->capacity, set->stride);
        if (set->buckets == nullptr) {
            scu_free(set);
            return nullptr;
        }
    }
    else {
        set->capacity = 0;
        set->buckets = nullptr;
    }
    return set;
}

int64_t scu_set_capacity(const SCUSet* set) {
    SCU_ASSERT(set != nullptr);
    return set->capacity;
}

int64_t scu_set_count(const SCUSet* set) {
    SCU_ASSERT(set != nullptr);
    return set->count;
}

/**
 * @brief Returns a pointer to a bucket at a specified index.
 *
 * @param[in] buckets A pointer to an array of buckets.
 * @param[in] index   The index of the bucket to retrieve.
 * @param[in] stride  The stride between consecutive buckets (in bytes).
 * @return A pointer to the bucket at the specified index.
 */
static inline SCUBucket* scu_bucket_at(
    SCUBucket* buckets,
    int64_t index,
    int64_t stride
) {
    SCU_ASSERT(buckets != nullptr);
    SCU_ASSERT(index >= 0);
    SCU_ASSERT(stride > SCU_SIZEOF(SCUBucket));
    return (SCUBucket*) (((unsigned char*) buckets) + (index * stride));
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
 * @param[in] hash  The hash of the element.
 * @param[in] index The index of the element.
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
 * @brief Rehashes old buckets by adding their elements to a specified set.
 *
 * @warning This function assumes that the specified set has enough capacity to
 * hold all elements of the old buckets. Additionally, the contents of
 * `oldBuckets` may be modified during the rehashing process for optimization
 * purposes. After this function returns, the state of `oldBuckets` is
 * explicitly undefined.
 *
 * @param[in, out] set         The set to rehash into.
 * @param[in, out] oldBuckets  The buckets to rehash.
 * @param[in]      oldCapacity The old capacity (in number of buckets).
 */
static inline void scu_set_rehash_buckets(
    SCUSet* set,
    SCUBucket* oldBuckets,
    int64_t oldCapacity
) {
    SCU_ASSERT(set != nullptr);
    SCU_ASSERT(oldBuckets != nullptr);
    SCU_ASSERT(oldCapacity > 0);
    for (int64_t i = 0; i < oldCapacity; i++) {
        SCUBucket* oldBucket = scu_bucket_at(oldBuckets, i, set->stride);
        if (oldBucket->isOccupied) {
            int64_t index = scu_ideal_index(oldBucket->hash, set->capacity);
            int64_t distance = 0;
            while (true) {
                SCUBucket* newBucket = scu_bucket_at(
                    set->buckets,
                    index,
                    set->stride
                );
                if (!newBucket->isOccupied) {
                    scu_memcpy(newBucket, oldBucket, set->stride);
                    set->count++;
                    break;
                }
                int64_t otherDistance = scu_probe_distance(
                    newBucket->hash,
                    index,
                    set->capacity
                );
                if (distance > otherDistance) {
                    scu_memswap(oldBucket, newBucket, set->stride);
                    distance = otherDistance;
                }
                index = scu_wrap_index(index + 1, set->capacity);
                distance++;
            }
        }
    }
}

SCUError scu_set_ensure_capacity(SCUSet* set, int64_t capacity) {
    SCU_ASSERT(set != nullptr);
    SCU_ASSERT(capacity >= 0);
    int64_t minCapacity = ((capacity * SCU_MAX_LOAD_FACTOR_DEN)
        + SCU_MAX_LOAD_FACTOR_NUM - 1) / SCU_MAX_LOAD_FACTOR_NUM;
    if (set->capacity >= minCapacity) {
        return SCU_ERROR_NONE;
    }
    int64_t newCapacity = scu_next_power_of_two(minCapacity);
    SCUBucket* newBuckets = scu_calloc(newCapacity, set->stride);
    if (newBuckets == nullptr) {
        return SCU_ERROR_OUT_OF_MEMORY;
    }
    int64_t oldCapacity = set->capacity;
    int64_t oldCount = set->count;
    SCUBucket* oldBuckets = set->buckets;
    set->capacity = newCapacity;
    set->count = 0;
    set->buckets = newBuckets;
    if (oldCount > 0) {
        scu_set_rehash_buckets(set, oldBuckets, oldCapacity);
    }
    scu_free(oldBuckets);
    return SCU_ERROR_NONE;
}

SCUError scu_set_add_impl(SCUSet* restrict set, const void* restrict elem) {
    SCU_ASSERT(set != nullptr);
    SCU_ASSERT(elem != nullptr);
    if ((set->count * SCU_MAX_LOAD_FACTOR_DEN)
            >= (set->capacity * SCU_MAX_LOAD_FACTOR_NUM)) {
        int64_t newCapacity = (set->capacity == 0)
            ? SCU_DEFAULT_CAPACITY
            : (set->capacity * SCU_GROWTH_FACTOR);
        SCUError error = scu_set_ensure_capacity(set, newCapacity);
        if (error != SCU_ERROR_NONE) {
            return error;
        }
    }
    SCUBucket* tempBucket = scu_malloc(set->stride);
    if (tempBucket == nullptr) {
        return SCU_ERROR_OUT_OF_MEMORY;
    }
    tempBucket->hash = set->hashFunc(elem);
    tempBucket->isOccupied = true;
    scu_memcpy(tempBucket->elem, elem, set->elemSize);
    int64_t index = scu_ideal_index(tempBucket->hash, set->capacity);
    int64_t distance = 0;
    while (true) {
        SCUBucket* bucket = scu_bucket_at(set->buckets, index, set->stride);
        if (!bucket->isOccupied) {
            scu_memcpy(bucket, tempBucket, set->stride);
            set->count++;
            scu_free(tempBucket);
            return SCU_ERROR_NONE;
        }
        if ((bucket->hash == tempBucket->hash)
                && set->equalFunc(bucket->elem, tempBucket->elem)) {
            scu_free(tempBucket);
            return SCU_ERROR_ELEM_PRESENT;
        }
        int64_t otherDistance = scu_probe_distance(
            bucket->hash,
            index,
            set->capacity
        );
        if (distance > otherDistance) {
            scu_memswap(bucket, tempBucket, set->stride);
            distance = otherDistance;
        }
        index = scu_wrap_index(index + 1, set->capacity);
        distance++;
    }
}

bool scu_set_contains_impl(const SCUSet* set, const void* elem) {
    SCU_ASSERT(set != nullptr);
    SCU_ASSERT(elem != nullptr);
    if (set->count == 0) {
        return false;
    }
    uint64_t hash = set->hashFunc(elem);
    int64_t index = scu_ideal_index(hash, set->capacity);
    int64_t distance = 0;
    while (true) {
        SCUBucket* bucket = scu_bucket_at(set->buckets, index, set->stride);
        if (!bucket->isOccupied) {
            return false;
        }
        int64_t otherDistance = scu_probe_distance(
            bucket->hash,
            index,
            set->capacity
        );
        if (distance > otherDistance) {
            return false;
        }
        if ((bucket->hash == hash) && set->equalFunc(bucket->elem, elem)) {
            return true;
        }
        index = scu_wrap_index(index + 1, set->capacity);
        distance++;
    }
}

bool scu_set_remove_impl(SCUSet* restrict set, const void* restrict elem) {
    SCU_ASSERT(set != nullptr);
    SCU_ASSERT(elem != nullptr);
    if (set->count == 0) {
        return false;
    }
    uint64_t hash = set->hashFunc(elem);
    int64_t index = scu_ideal_index(hash, set->capacity);
    int64_t distance = 0;
    while (true) {
        SCUBucket* bucket = scu_bucket_at(set->buckets, index, set->stride);
        if (!bucket->isOccupied) {
            return false;
        }
        int64_t otherDistance = scu_probe_distance(
            bucket->hash,
            index,
            set->capacity
        );
        if (distance > otherDistance) {
            return false;
        }
        if ((bucket->hash == hash) && set->equalFunc(bucket->elem, elem)) {
            break;
        }
        index = scu_wrap_index(index + 1, set->capacity);
        distance++;
    }
    SCUBucket* bucket = scu_bucket_at(set->buckets, index, set->stride);
    while (true) {
        int64_t nextIndex = scu_wrap_index(index + 1, set->capacity);
        SCUBucket* nextBucket = scu_bucket_at(
            set->buckets,
            nextIndex,
            set->stride
        );
        if (!nextBucket->isOccupied) {
            break;
        }
        int64_t nextDistance = scu_probe_distance(
            nextBucket->hash,
            nextIndex,
            set->capacity
        );
        if (nextDistance == 0) {
            break;
        }
        scu_memcpy(bucket, nextBucket, set->stride);
        index = nextIndex;
        bucket = nextBucket;
    }
    bucket->isOccupied = false;
    set->count--;
    return true;
}

void scu_set_clear(SCUSet* set) {
    SCU_ASSERT(set != nullptr);
    if (set->count > 0) {
        for (int64_t i = 0; i < set->capacity; i++) {
            SCUBucket* bucket = scu_bucket_at(set->buckets, i, set->stride);
            bucket->isOccupied = false;
        }
        set->count = 0;
    }
}

SCUError scu_set_trim_excess(SCUSet* set) {
    SCU_ASSERT(set != nullptr);
    if (set->count == 0) {
        scu_free(set->buckets);
        set->buckets = nullptr;
        set->capacity = 0;
        return SCU_ERROR_NONE;
    }
    int64_t minCapacity = ((set->count * SCU_MAX_LOAD_FACTOR_DEN)
        + SCU_MAX_LOAD_FACTOR_NUM - 1) / SCU_MAX_LOAD_FACTOR_NUM;
    int64_t newCapacity = scu_next_power_of_two(minCapacity);
    if (set->capacity <= newCapacity) {
        return SCU_ERROR_NONE;
    }
    SCUBucket* newBuckets = scu_calloc(newCapacity, set->stride);
    if (newBuckets == nullptr) {
        return SCU_ERROR_OUT_OF_MEMORY;
    }
    int64_t oldCapacity = set->capacity;
    SCUBucket* oldBuckets = set->buckets;
    set->capacity = newCapacity;
    set->count = 0;
    set->buckets = newBuckets;
    scu_set_rehash_buckets(set, oldBuckets, oldCapacity);
    scu_free(oldBuckets);
    return SCU_ERROR_NONE;
}

SCUSetIterator scu_set_iterator(const SCUSet* set) {
    SCU_ASSERT(set != nullptr);
    return (SCUSetIterator) { .set = (SCUSet*) set, .index = -1 };
}

bool scu_set_iterator_move_next(SCUSetIterator* iterator) {
    SCU_ASSERT(iterator != nullptr);
    SCU_ASSERT(iterator->set != nullptr);
    SCUSet* set = iterator->set;
    int64_t index = iterator->index;
    SCU_ASSERT((index >= -1) && (index <= set->capacity));
    if (set->count == 0) {
        iterator->index = set->capacity;
        return false;
    }
    index++;
    while (index < set->capacity) {
        SCUBucket* bucket = scu_bucket_at(set->buckets, index, set->stride);
        if (bucket->isOccupied) {
            iterator->index = index;
            return true;
        }
        index++;
    }
    iterator->index = set->capacity;
    return false;
}

void* scu_set_iterator_current(const SCUSetIterator* iterator) {
    SCU_ASSERT(iterator != nullptr);
    SCU_ASSERT(iterator->set != nullptr);
    SCUSet* set = iterator->set;
    int64_t index = iterator->index;
    SCU_ASSERT((index >= 0) && (index < set->capacity));
    SCUBucket* bucket = scu_bucket_at(set->buckets, index, set->stride);
    SCU_ASSERT(bucket->isOccupied);
    return bucket->elem;
}

void scu_set_iterator_reset(SCUSetIterator* iterator) {
    SCU_ASSERT(iterator != nullptr);
    SCU_ASSERT(iterator->set != nullptr);
    SCU_ASSERT(
        (iterator->index >= -1) && (iterator->index <= iterator->set->capacity)
    );
    iterator->index = -1;
}

void scu_set_free(SCUSet* set) {
    if (set != nullptr) {
        scu_free(set->buckets);
        scu_free(set);
    }
}