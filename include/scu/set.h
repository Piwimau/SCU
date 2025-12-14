#ifndef SCU_SET_H
#define SCU_SET_H

#include <stdint.h>
#include "scu/common.h"
#include "scu/equal.h"
#include "scu/error.h"
#include "scu/hash.h"

/** @brief Represents an unordered set of elements. */
typedef struct SCUSet SCUSet;

struct SCUSetIter {

    /** @brief The set being iterated over. */
    SCUSet* set;

    /** @brief The current index within the set. */
    int64_t index;

};

/**
 * @brief Represents an iterator for a set.
 *
 * @note The internal representation of the iterator is an implementation detail
 * and should not be relied upon. Most importantly, the behavior is undefined if
 * its fields are accessed directly.
 */
typedef struct SCUSetIter SCUSetIter;

/**
 * @brief Allocates and initializes a new set with a specified element size,
 * hash function, equality function, and an unspecified default capacity.
 *
 * @note This function dynamically allocates memory using `scu_malloc()` and
 * `scu_calloc()`.
 *
 * @warning The caller is responsible for deallocating the set with
 * `scu_set_free()` when it is no longer needed.
 *
 * @param[in] elemSize  The size of each element (in bytes).
 * @param[in] hashFunc  A function used for hashing elements.
 * @param[in] equalFunc A function used for comparing elements for equality.
 * @return A pointer to the new set, or `nullptr` on failure.
 */
[[nodiscard]]
SCUSet* scu_set_new(
    int64_t elemSize,
    SCUHashFunc* hashFunc,
    SCUEqualFunc* equalFunc
);

/**
 * @brief Allocates and initializes a new set with a specified element size,
 * hash function, equality function, and initial capacity.
 *
 * @note This function dynamically allocates memory using `scu_malloc()` and
 * `scu_calloc()`.
 *
 * @warning The caller is responsible for deallocating the set with
 * `scu_set_free()` when it is no longer needed.
 *
 * @param[in] elemSize  The size of each element (in bytes).
 * @param[in] capacity  The initial capacity (in number of elements).
 * @param[in] hashFunc  A function used for hashing elements.
 * @param[in] equalFunc A function used for comparing elements for equality.
 * @return A pointer to the new set, or `nullptr` on failure.
 */
[[nodiscard]]
SCUSet* scu_set_new_with_capacity(
    int64_t elemSize,
    int64_t capacity,
    SCUHashFunc* hashFunc,
    SCUEqualFunc* equalFunc
);

/**
 * @brief Returns the capacity of a specified set, i.e., the maximum number of
 * elements that can be stored before a reallocation is required.
 *
 * @note The capacity can be influenced to a certain extent using
 * `scu_set_ensure_capacity()` and `scu_set_trim_excess()`. See their respective
 * documentation for details.
 *
 * @param[in] set The set to examine.
 * @return The capacity of the specified set.
 */
int64_t scu_set_capacity(const SCUSet* set);

/**
 * @brief Returns the number of elements in a specified set.
 *
 * @param[in] set The set to examine.
 * @return The number of elements in the specified set.
 */
int64_t scu_set_count(const SCUSet* set);

/**
 * @brief Ensures that a specified set has at least a specified capacity.
 *
 * @note This function dynamically allocates memory using `scu_calloc()`.
 *
 * @param[in, out] set      The set to ensure the capacity of.
 * @param[in]      capacity The desired capacity (in number of elements).
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_set_ensure_capacity(SCUSet* set, int64_t capacity);

/**
 * @brief Adds a new element to a specified set.
 *
 * @note This function is an implementation detail and not intended to be called
 * directly. Use the `scu_set_add()` macro instead.
 *
 * This function dynamically allocates memory using `scu_malloc()` and
 * `scu_calloc()`.
 *
 * @param[in, out] set  The set to add the element to.
 * @param[in]      elem The element to add.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * `SCU_ERROR_ELEM_PRESENT` if the element is already present, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_set_add_impl(SCUSet* restrict set, const void* restrict elem);

/**
 * @brief Adds a new element to a specified set.
 *
 * @note This macro dynamically allocates memory using `scu_malloc()` and
 * `scu_calloc()`.
 *
 * @param[in, out] set  The set to add the element to.
 * @param[in]      elem The element to add.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * `SCU_ERROR_ELEM_PRESENT` if the element is already present, or
 * `SCU_ERROR_NONE` on success.
 */
#define scu_set_add(set, elem) scu_set_add_impl(set, &(elem))

/**
 * @brief Determines whether a specified set contains a specified element.
 *
 * @note This function is an implementation detail and not intended to be called
 * directly. Use the `scu_set_contains()` macro instead.
 *
 * @param[in] set  The set to examine.
 * @param[in] elem The element to search for.
 * @return `true` if the element is present in the set, otherwise `false`.
 */
bool scu_set_contains_impl(const SCUSet* set, const void* elem);

/**
 * @brief Determines whether a specified set contains a specified element.
 *
 * @param[in] set  The set to examine.
 * @param[in] elem The element to search for.
 * @return `true` if the element is present in the set, otherwise `false`.
 */
#define scu_set_contains(set, elem) scu_set_contains_impl(set, &(elem))

/**
 * @brief Removes a specified element from a specified set.
 *
 * @note This function is an implementation detail and not intended to be called
 * directly. Use the `scu_set_remove()` macro instead.
 *
 * Consider using `scu_set_trim_excess()` if you wish to reduce the memory usage
 * of the set after removing elements.
 *
 * @warning This function does not deallocate the removed element, it only
 * removes it from the set. The caller is responsible for deallocating the
 * removed element if it is a pointer to a dynamically allocated object and no
 * other references to it exist.
 *
 * @param[in, out] set  The set to remove the element from.
 * @param[in]      elem The element to remove.
 * @return `true` if the element was present and removed, otherwise `false`.
 */
bool scu_set_remove_impl(SCUSet* restrict set, const void* restrict elem);

/**
 * @brief Removes a specified element from a specified set.
 *
 * @note Consider using `scu_set_trim_excess()` if you wish to reduce the memory
 * usage of the set after removing elements.
 *
 * @warning This macro does not deallocate the removed element, it only removes
 * it from the set. The caller is responsible for deallocating the removed
 * element if it is a pointer to a dynamically allocated object and no other
 * references to it exist.
 *
 * @param[in, out] set  The set to remove the element from.
 * @param[in]      elem The element to remove.
 * @return `true` if the element was present and removed, otherwise `false`.
 */
#define scu_set_remove(set, elem) scu_set_remove_impl(set, &(elem))

/**
 * @brief Removes all elements from a specified set.
 *
 * @note Consider using `scu_set_trim_excess()` if you wish to reduce the memory
 * usage of the set after clearing it.
 *
 * @warning This function does not deallocate the set itself nor the elements
 * contained within, it only resets the number of elements to zero. The caller
 * is responsible for deallocating the individual elements if they are pointers
 * to dynamically allocated objects and no other references to them exist.
 *
 * @param[in, out] set The set to clear.
 */
void scu_set_clear(SCUSet* set);

/**
 * @brief Trims the excess capacity of a specified set to match its current
 * number of elements.
 *
 * @note This function dynamically allocates memory using `scu_calloc()`.
 *
 * @param[in, out] set The set to trim.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_set_trim_excess(SCUSet* set);

/**
 * @brief Returns an iterator for a specified set.
 *
 * @note The iterator is initially positioned before the first element of the
 * set (if any). This means that `scu_set_iter_move_next()` must be called
 * before accessing the first and subsequent elements with
 * `scu_set_iter_current()`.
 *
 * @warning The behavior is undefined if the set being iterated over is modified
 * (e.g., elements are added or removed) while the iterator is in use.
 *
 * @param[in] set The set to iterate over.
 * @return An iterator for the specified set.
 */
SCUSetIter scu_set_iter(const SCUSet* set);

/**
 * @brief Advances a specified set iterator to the next element.
 *
 * @param[in, out] iter The iterator to advance.
 * @return `true` if the iterator was successfully advanced to the next element,
 * otherwise `false` (i.e., the set does not contain any more elements).
 */
bool scu_set_iter_move_next(SCUSetIter* iter);

/**
 * @brief Returns the current element of a specified set iterator.
 *
 * @param[in] iter The iterator to examine.
 * @return A pointer to the current element.
 */
void* scu_set_iter_current(const SCUSetIter* iter);

/**
 * @brief Resets a specified set iterator to its initial position.
 *
 * @note The iterator is initially positioned before the first element of the
 * set (if any). This means that `scu_set_iter_move_next()` must be called
 * before accessing the first and subsequent elements with
 * `scu_set_iter_current()`.
 *
 * @param[in, out] iter The iterator to reset.
 */
void scu_set_iter_reset(SCUSetIter* iter);

/**
 * @brief Deallocates a specified set.
 *
 * @note If `set` is a `nullptr`, this function does nothing.
 *
 * @warning This function only deallocates the memory occupied by the set
 * itself, but not the elements contained within. The caller is responsible for
 * deallocating the individual elements if they are pointers to dynamically
 * allocated objects and no other references to them exist.
 *
 * The behavior is undefined if `set` is used after it has been deallocated.
 *
 * @param[in, out] set The set to deallocate.
 */
void scu_set_free(SCUSet* set);

/**
 * @brief Iterates over each element in a specified set.
 *
 * This macro expands to a for loop that iterates over each element in the
 * specified set. During each iteration, the provided variable is assigned a
 * pointer to the current element.
 *
 * The following example demonstrates the basic usage of this macro:
 *
 * ```c
 * // T is the type of the elements stored in the set.
 * SCUSet* elems = scu_set_new(SCU_SIZEOF(T), ...);
 * ...
 * T* elem;
 * SCU_SET_FOREACH(elem, elems) {
 *    // Do something with *elem.
 * }
 * ```
 *
 * @note The variable `elem` must be declared manually before the loop. It must
 * be of a pointer type compatible with the set's element type.
 *
 * @warning The behavior is undefined if the set is modified (e.g., elements are
 * added or removed) while being iterated over.
 *
 * @param[out] elem A pointer to the current element during each iteration.
 * @param[in]  set  The set to iterate over.
 */
#define SCU_SET_FOREACH(elem, set)                                         \
    for (                                                                  \
        SCUSetIter SCU_XCONCAT(it, __LINE__) = scu_set_iter(set);          \
        scu_set_iter_move_next(&SCU_XCONCAT(it, __LINE__))                 \
            && ((elem) = scu_set_iter_current(&SCU_XCONCAT(it, __LINE__)), \
                true);                                                     \
    )

#endif