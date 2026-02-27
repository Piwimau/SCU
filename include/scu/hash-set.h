#ifndef SCU_HASH_SET_H
#define SCU_HASH_SET_H

#include "scu/common.h"
#include "scu/equal.h"
#include "scu/error.h"
#include "scu/hash.h"
#include "scu/types.h"

/** @brief Represents an unordered hash set of elements. */
typedef struct SCUHashSet SCUHashSet;

/**
 * @brief Represents an iterator for a hash set.
 *
 * @warning The internal representation of the iterator is an implementation
 * detail and should not be relied upon. Most importantly, the behavior is
 * undefined if its fields are accessed directly.
 */
typedef struct SCUHashSetIter {

    /** @brief The hash set being iterated over. */
    SCUHashSet* hashSet;

    /** @brief The current index within the hash set. */
    SCUisize index;

} SCUHashSetIter;

/**
 * @brief Allocates and initializes a new hash set with a specified element
 * size, hash function, equality function, and an unspecified default capacity.
 *
 * @note This function dynamically allocates memory using `scu_malloc()` and
 * `scu_calloc()`.
 *
 * @warning The caller is responsible for deallocating the hash set with
 * `scu_hash_set_free()` when it is no longer needed.
 *
 * @param[in] elemSize  The size of each element (in bytes).
 * @param[in] hashFunc  A function used for hashing elements.
 * @param[in] equalFunc A function used for comparing elements for equality.
 * @return A pointer to the new hash set, or `nullptr` on failure.
 */
[[nodiscard]]
SCUHashSet* scu_hash_set_new(
    SCUisize elemSize,
    SCUHashFunc* hashFunc,
    SCUEqualFunc* equalFunc
);

/**
 * @brief Allocates and initializes a new hash set with a specified element
 * size, hash function, equality function, and initial capacity.
 *
 * @note This function dynamically allocates memory using `scu_malloc()` and
 * `scu_calloc()`.
 *
 * @warning The caller is responsible for deallocating the hash set with
 * `scu_hash_set_free()` when it is no longer needed.
 *
 * @param[in] elemSize  The size of each element (in bytes).
 * @param[in] capacity  The initial capacity (in number of elements).
 * @param[in] hashFunc  A function used for hashing elements.
 * @param[in] equalFunc A function used for comparing elements for equality.
 * @return A pointer to the new hash set, or `nullptr` on failure.
 */
[[nodiscard]]
SCUHashSet* scu_hash_set_new_with_capacity(
    SCUisize elemSize,
    SCUisize capacity,
    SCUHashFunc* hashFunc,
    SCUEqualFunc* equalFunc
);

/**
 * @brief Creates a shallow copy of a specified hash set.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`.
 *
 * @warning The caller is responsible for deallocating the cloned hash set with
 * `scu_hash_set_free()` when it is no longer needed.
 *
 * @param[in] hashSet The hash set to clone.
 * @return A pointer to the cloned hash set, or `nullptr` on failure.
 */
[[nodiscard]]
SCUHashSet* scu_hash_set_clone(const SCUHashSet* hashSet);

/**
 * @brief Returns the capacity of a specified hash set, i.e., the maximum number
 * of elements that can be stored before a reallocation is required.
 *
 * @note The capacity can be influenced to a certain extent using
 * `scu_hash_set_ensure_capacity()` and `scu_hash_set_trim_excess()`. See their
 * respective documentation for details.
 *
 * @param[in] hashSet The hash set to examine.
 * @return The capacity of the specified hash set.
 */
SCUisize scu_hash_set_capacity(const SCUHashSet* hashSet);

/**
 * @brief Returns the number of elements in a specified hash set.
 *
 * @param[in] hashSet The hash set to examine.
 * @return The number of elements in the specified hash set.
 */
SCUisize scu_hash_set_count(const SCUHashSet* hashSet);

/**
 * @brief Ensures that a specified hash set has at least a specified capacity.
 *
 * @note This function dynamically allocates memory using `scu_calloc()`.
 *
 * @param[in, out] hashSet  The hash set to ensure the capacity of.
 * @param[in]      capacity The desired capacity (in number of elements).
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_hash_set_ensure_capacity(SCUHashSet* hashSet, SCUisize capacity);

/**
 * @brief Adds a new element to a specified hash set.
 *
 * @note This function dynamically allocates memory using `scu_malloc()` and
 * `scu_calloc()`.
 *
 * @param[in, out] hashSet The hash set to add the element to.
 * @param[in]      elem    The element to add.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * `SCU_ERROR_ALREADY_PRESENT` if the element is already present in the hash
 * set, or `SCU_ERROR_NONE` on success.
 */
SCUError scu_hash_set_add(
    SCUHashSet* restrict hashSet,
    const void* restrict elem
);

/**
 * @brief Determines whether a specified hash set contains a specified element.
 *
 * @param[in] hashSet The hash set to examine.
 * @param[in] elem    The element to search for.
 * @return `true` if the element is present in the hash set, otherwise `false`.
 */
bool scu_hash_set_contains(const SCUHashSet* hashSet, const void* elem);

/**
 * @brief Removes a specified element from a specified hash set.
 *
 * @note Consider using `scu_hash_set_trim_excess()` if you wish to reduce the
 * memory usage of the hash set after removing elements.
 *
 * @warning This function does not deallocate the removed element, it only
 * removes it from the hash set. The caller is responsible for deallocating the
 * removed element if it is a pointer to a dynamically allocated object and no
 * other references to it exist.
 *
 * @param[in, out] hashSet The hash set to remove the element from.
 * @param[in]      elem    The element to remove.
 * @return `true` if the element was present and removed from the hash set,
 * otherwise `false`.
 */
bool scu_hash_set_remove(
    SCUHashSet* restrict hashSet,
    const void* restrict elem
);

/**
 * @brief Removes all elements from a specified hash set.
 *
 * @note Consider using `scu_hash_set_trim_excess()` if you wish to reduce the
 * memory usage of the hash set after clearing it.
 *
 * @warning This function does not deallocate the hash set itself nor the
 * elements contained within, it only resets the number of elements to zero. The
 * caller is responsible for deallocating the individual elements if they are
 * pointers to dynamically allocated objects and no other references to them
 * exist.
 *
 * @param[in, out] hashSet The hash set to clear.
 */
void scu_hash_set_clear(SCUHashSet* hashSet);

/**
 * @brief Trims the excess capacity of a specified hash set to match its current
 * number of elements.
 *
 * @note This function dynamically allocates memory using `scu_calloc()`.
 *
 * @param[in, out] hashSet The hash set to trim.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_hash_set_trim_excess(SCUHashSet* hashSet);

/**
 * @brief Returns an iterator for a specified hash set.
 *
 * @note The iterator is initially positioned before the first element of the
 * hash set (if any). This means that `scu_hash_set_iter_move_next()` must be
 * called before accessing the first and subsequent elements with
 * `scu_hash_set_iter_current()`.
 *
 * @warning The behavior is undefined if the hash set being iterated over is
 * modified (e.g., elements are added or removed) while the iterator is in use.
 *
 * @param[in] hashSet The hash set to iterate over.
 * @return An iterator for the specified hash set.
 */
SCUHashSetIter scu_hash_set_iter(const SCUHashSet* hashSet);

/**
 * @brief Advances a specified hash set iterator to the next element.
 *
 * @param[in, out] iter The iterator to advance.
 * @return `true` if the iterator was successfully advanced to the next element,
 * otherwise `false` (i.e., the hash set does not contain any more elements).
 */
bool scu_hash_set_iter_move_next(SCUHashSetIter* iter);

/**
 * @brief Returns the current element of a specified hash set iterator.
 *
 * @param[in] iter The iterator to examine.
 * @return A pointer to the current element.
 */
void* scu_hash_set_iter_current(const SCUHashSetIter* iter);

/**
 * @brief Resets a specified hash set iterator to its initial position.
 *
 * @note The iterator is initially positioned before the first element of the
 * hash set (if any). This means that `scu_hash_set_iter_move_next()` must be
 * called before accessing the first and subsequent elements with
 * `scu_hash_set_iter_current()`.
 *
 * @param[in, out] iter The iterator to reset.
 */
void scu_hash_set_iter_reset(SCUHashSetIter* iter);

/**
 * @brief Deallocates a specified hash set.
 *
 * @note If `hashSet` is a `nullptr`, this function does nothing.
 *
 * @warning This function only deallocates the memory occupied by the hash set
 * itself, but not the elements contained within. The caller is responsible for
 * deallocating the individual elements if they are pointers to dynamically
 * allocated objects and no other references to them exist.
 *
 * The behavior is undefined if the hash set is used after it has been
 * deallocated.
 *
 * @param[in, out] hashSet The hash set to deallocate.
 */
void scu_hash_set_free(SCUHashSet* hashSet);

/**
 * @brief Iterates over each element in a specified hash set.
 *
 * This macro expands to a for loop that iterates over each element in the
 * specified hash set. During each iteration, the provided variable is assigned
 * a pointer to the current element.
 *
 * The following example demonstrates the basic usage of this macro:
 *
 * ```c
 * // T is the type of the elements stored in the hash set.
 * SCUHashSet* elems = scu_hash_set_new(SCU_SIZEOF(T), ...);
 * ...
 * T* elem;
 * SCU_HASH_SET_FOREACH(elem, elems) {
 *     // Do something with *elem.
 * }
 * ```
 *
 * @note The variable `elem` must be declared manually before the loop. It must
 * be of a pointer type compatible with the hash set's element type.
 *
 * @warning The behavior is undefined if the hash set is modified (e.g.,
 * elements are added or removed) while being iterated over.
 *
 * @param[out] elem    A pointer to the current element during each iteration.
 * @param[in]  hashSet The hash set to iterate over.
 */
#define SCU_HASH_SET_FOREACH(elem, hashSet)                                     \
    for (                                                                       \
        SCUHashSetIter SCU_XCONCAT(it, __LINE__) = scu_hash_set_iter(hashSet);  \
        scu_hash_set_iter_move_next(&SCU_XCONCAT(it, __LINE__))                 \
            && ((elem) = scu_hash_set_iter_current(&SCU_XCONCAT(it, __LINE__)), \
                true);                                                          \
    )

#endif