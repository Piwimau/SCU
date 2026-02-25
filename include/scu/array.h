#ifndef SCU_ARRAY_H
#define SCU_ARRAY_H

#include "scu/compare.h"
#include "scu/memory.h"

/**
 * @brief Returns the number of elements in a statically allocated array.
 *
 * @warning Do not use this macro with a pointer instead of a statically
 * allocated array, as it will yield an incorrect result.
 *
 * @param[in] array The statically allocated array.
 * @return The number of elements in the statically allocated array.
 */
#define SCU_COUNTOF(array) (SCU_SIZEOF(array) / SCU_SIZEOF((array)[0]))

/**
 * @brief Iterates over each element in a statically allocated array.
 *
 * This macro expands to a for loop that iterates over each element in the
 * specified statically allocated array. During each iteration, the provided
 * variable is assigned a pointer to the current element.
 *
 * The following example demonstrates the basic usage of this macro:
 *
 * ```c
 * // T is the type of the elements stored in the statically allocated array.
 * T elems[] = { ... };
 * ...
 * T* elem;
 * SCU_ARRAY_FOREACH(elem, elems) {
 *     // Do something with *elem.
 * }
 * ```
 *
 * @note The variable `elem` must be declared manually before the loop. It must
 * be of a pointer type compatible with the array's element type.
 *
 * @warning The behavior is undefined if `array` is not a statically allocated
 * array.
 *
 * @param[out] elem  A pointer to the current element during each iteration.
 * @param[in]  array The statically allocated array to iterate over.
 */
#define SCU_ARRAY_FOREACH(elem, array)                                        \
    for ((elem) = (array); (elem) < ((array) + SCU_COUNTOF(array)); (elem)++)

/**
 * @brief Sorts a specified array using a provided comparison function.
 *
 * @note If `count` is zero, `array` is ignored and it may even be a `nullptr`.
 *
 * No guarantees are made regarding the complexity and stability of the
 * underlying sorting algorithm. Most importantly, if two elements are
 * considered equivalent by the provided comparison function, their relative
 * order in the sorted array may not be the same as in the original array.
 *
 * @warning The behavior is undefined if `array` does not point to a block of
 * memory of at least `count * elemSize` bytes, if `cmpFunc` modifies the
 * elements passed to it, or if `cmpFunc` returns inconsistent results when
 * called more than once with the same arguments.
 *
 * @param[in, out] array    The array to sort.
 * @param[in]      count    The number of elements in the array.
 * @param[in]      elemSize The size of each element (in bytes).
 * @param[in]      cmpFunc  A comparison function used to determine the order of
 *                          the elements.
 */
void scu_array_sort(
    void* array,
    SCUisize count,
    SCUisize elemSize,
    SCUCompareFunc* cmpFunc
);

#endif