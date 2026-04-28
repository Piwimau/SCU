#ifndef SCU_LIST_H
#define SCU_LIST_H

#include "scu/compare.h"
#include "scu/error.h"
#include "scu/types.h"

/**
 * @brief Allocates and initializes a new list with a specified element size and
 * an unspecified default capacity.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`. The
 * pointer returned is suitably aligned for any type with fundamental alignment
 * requirements.
 *
 * @warning The caller is responsible for deallocating the list with
 * `scu_list_free()` when it is no longer needed.
 *
 * @param[in] elemSize The size of each element (in bytes).
 * @return A pointer to the new list, or `nullptr` on failure.
 */
[[nodiscard]]
void* scu_list_new(Scuisize elemSize);

/**
 * @brief Allocates and initializes a new list with a specified element size
 * and initial capacity.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`. The
 * pointer returned is suitably aligned for any type with fundamental alignment
 * requirements.
 *
 * @warning The caller is responsible for deallocating the list with
 * `scu_list_free()` when it is no longer needed.
 *
 * @param[in] elemSize The size of each element (in bytes).
 * @param[in] capacity The initial capacity (in number of elements).
 * @return A pointer to the new list, or `nullptr` on failure.
 */
[[nodiscard]]
void* scu_list_new_with_capacity(Scuisize elemSize, Scuisize capacity);

/**
 * @brief Creates a shallow copy of a specified list.
 *
 * This function creates a shallow copy of the specified list by allocating a
 * new list and copying all elements from the original list to the new list.
 * Modifications to the elements in the cloned list will not affect the original
 * list (and vice versa).
 *
 * @note This function dynamically allocates memory using `scu_malloc()`. The
 * pointer returned is suitably aligned for any type with fundamental alignment
 * requirements.
 *
 * @warning The caller is responsible for deallocating the cloned list with
 * `scu_list_free()` when it is no longer needed.
 *
 * @param[in] list The list to clone.
 * @return A pointer to the cloned list, or `nullptr` on failure.
 */
[[nodiscard]]
void* scu_list_clone(const void* list);

/**
 * @brief Returns the capacity of a specified list, i.e., the maximum number of
 * elements that can be stored before a reallocation is required.
 *
 * @note The capacity can be influenced to a certain extent using
 * `scu_list_ensure_capacity()` and `scu_list_trim_excess()`. See their
 * respective documentation for details.
 *
 * @param[in] list The list to examine.
 * @return The capacity of the specified list.
 */
Scuisize scu_list_capacity(const void* list);

/**
 * @brief Returns the number of elements in a specified list.
 *
 * @param[in] list The list to examine.
 * @return The number of elements in the specified list.
 */
Scuisize scu_list_count(const void* list);

/**
 * @brief Ensures that a specified list has at least a specified capacity.
 *
 * This function ensures that the specified list has at least the specified
 * capacity. If the current capacity is less than the desired capacity, the list
 * is reallocated using `scu_realloc()` and the pointer to the new block of
 * memory is assigned to `*list`.
 *
 * @note This function is an implementation detail and not intended to be called
 * directly. Use the `scu_list_ensure_capacity()` macro instead.
 *
 * This function dynamically allocates memory using `scu_realloc()`. The pointer
 * assigned to `*list` is suitably aligned for any type with fundamental
 * alignment requirements.
 *
 * @warning The caller is responsible for updating any existing pointers to the
 * list using the pointer assigned to `*list`, as previous pointers may have
 * been invalidated due to reallocation.
 *
 * @param[in, out] list     The list to ensure the capacity of.
 * @param[in]      capacity The desired capacity (in number of elements).
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
ScuError scu_list_ensure_capacity_impl(void** list, Scuisize capacity);

/**
 * @brief Ensures that a specified list has at least a specified capacity.
 *
 * This macro ensures that the specified list has at least the specified
 * capacity. If the current capacity is less than the desired capacity, the list
 * is reallocated using `scu_realloc()` and the pointer to the new block of
 * memory is assigned to `*list`.
 *
 * @note This macro dynamically allocates memory using `scu_realloc()`. The
 * pointer assigned to `*list` is suitably aligned for any type with fundamental
 * alignment requirements.
 *
 * @warning The caller is responsible for updating any existing pointers to the
 * list using the pointer assigned to `*list`, as previous pointers may have
 * been invalidated due to reallocation.
 *
 * @param[in, out] list     The list to ensure the capacity of.
 * @param[in]      capacity The desired capacity (in number of elements).
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
#define scu_list_ensure_capacity(list, capacity)             \
    scu_list_ensure_capacity_impl((void**) (list), capacity)

/**
 * @brief Adds a new element to the end of a specified list.
 *
 * This function adds a new element to the end of the specified list. If the
 * capacity of the list is insufficient to accommodate the new element, the list
 * is reallocated using `scu_realloc()` and the pointer to the new block of
 * memory is assigned to `*list`. The new element is initialized by copying the
 * data from `*elem` into the next available slot in the list.
 *
 * @note This function is an implementation detail and not intended to be called
 * directly. Use the `scu_list_add()` macro instead.
 *
 * This function dynamically allocates memory using `scu_realloc()`. The pointer
 * assigned to `*list` is suitably aligned for any type with fundamental
 * alignment requirements.
 *
 * @warning The caller is responsible for updating any existing pointers to the
 * list using the pointer assigned to `*list`, as previous pointers may have
 * been invalidated due to reallocation.
 *
 * @param[in, out] list The list to add the element to.
 * @param[in]      elem The element to add.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
ScuError scu_list_add_impl(void** restrict list, const void* restrict elem);

/**
 * @brief Adds a new element to the end of a specified list.
 *
 * This macro adds a new element to the end of the specified list. If the
 * capacity of the list is insufficient to accommodate the new element, the list
 * is reallocated using `scu_realloc()` and the pointer to the new block of
 * memory is assigned to `*list`. The new element is initialized by copying the
 * data from `elem` into the next available slot in the list.
 *
 * @note This macro dynamically allocates memory using `scu_realloc()`. The
 * pointer assigned to `*list` is suitably aligned for any type with fundamental
 * alignment requirements.
 *
 * @warning The caller is responsible for updating any existing pointers to the
 * list using the pointer assigned to `*list`, as previous pointers may have
 * been invalidated due to reallocation.
 *
 * @param[in, out] list The list to add the element to.
 * @param[in]      elem The element to add.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
#define scu_list_add(list, elem) scu_list_add_impl((void**) (list), elem)

/**
 * @brief Inserts a new element at a specified index into a specified list.
 *
 * This function inserts a new element at the specified index into the specified
 * list. If the capacity of the list is insufficient to accommodate the new
 * element, the list is reallocated using `scu_realloc()` and the pointer to
 * the new block of memory is assigned to `*list`. Any elements at and after the
 * specified index are shifted one position to the right to make room for the
 * new element, which is initialized by copying the data from `*elem` into the
 * now unoccupied slot.
 *
 * Note that `index` may be equal to `scu_list_count(*list)`, in which case the
 * new element is added to the end of the list. In this case, the behavior is
 * equivalent to `scu_list_add(*list, elem)`.
 *
 * @note This function is an implementation detail and not intended to be called
 * directly. Use the `scu_list_insert_at()` macro instead.
 *
 * This function dynamically allocates memory using `scu_realloc()`. The pointer
 * assigned to `*list` is suitably aligned for any type with fundamental
 * alignment requirements.
 *
 * @warning The caller is responsible for updating any existing pointers to the
 * list using the pointer assigned to `*list`, as previous pointers may have
 * been invalidated due to reallocation.
 *
 * @param[in, out] list  The list to insert the element into.
 * @param[in]      index The index at which to insert the new element.
 * @param[in]      elem  The element to insert.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
ScuError scu_list_insert_at_impl(
    void** restrict list,
    Scuisize index,
    const void* restrict elem
);

/**
 * @brief Inserts a new element at a specified index into a specified list.
 *
 * This macro inserts a new element at the specified index into the specified
 * list. If the capacity of the list is insufficient to accommodate the new
 * element, the list is reallocated using `scu_realloc()` and the pointer to
 * the new block of memory is assigned to `*list`. Any elements at and after the
 * specified index are shifted one position to the right to make room for the
 * new element, which is initialized by copying the data from `elem` into the
 * now unoccupied slot.
 *
 * Note that `index` may be equal to `scu_list_count(*list)`, in which case the
 * new element is added to the end of the list. In this case, the behavior is
 * equivalent to `scu_list_add(*list, elem)`.
 *
 * @note This macro dynamically allocates memory using `scu_realloc()`. The
 * pointer assigned to `*list` is suitably aligned for any type with fundamental
 * alignment requirements.
 *
 * @warning The caller is responsible for updating any existing pointers to the
 * list using the pointer assigned to `*list`, as previous pointers may have
 * been invalidated due to reallocation.
 *
 * @param[in, out] list  The list to insert the element into.
 * @param[in]      index The index at which to insert the new element.
 * @param[in]      elem  The element to insert.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
#define scu_list_insert_at(list, index, elem)             \
    scu_list_insert_at_impl((void**) (list), index, elem)

/**
 * @brief Removes an element at a specified index from a specified list.
 *
 * This function removes the element at the specified index from the specified
 * list. Any elements after the specified index are shifted one position to the
 * left to fill the gap left by the removed element.
 *
 * @note As the capacity of the list remains unchanged, no reallocation occurs
 * and the pointer to the list remains valid. Consider using
 * `scu_list_trim_excess()` if you wish to reduce the memory usage of the list
 * after removing elements.
 *
 * @warning This function does not deallocate the removed element, it only
 * shifts any remaining elements after the specified index to the left. The
 * caller is responsible for deallocating the removed element if it is a pointer
 * to a dynamically allocated object and no other references to it exist.
 *
 * @param[in, out] list  The list to remove the element from.
 * @param[in]      index The index of the element to remove.
 */
void scu_list_remove_at(void* list, Scuisize index);

/**
 * @brief Clears all elements from a specified list.
 *
 * @note As the capacity of the list remains unchanged, no reallocation occurs
 * and the pointer to the list remains valid. Consider using
 * `scu_list_trim_excess()` if you wish to reduce the memory usage of the list
 * after clearing it.
 *
 * @warning This function does not deallocate the list itself nor the elements
 * contained within, it only resets the number of elements to zero. The caller
 * is responsible for deallocating the individual elements if they are pointers
 * to dynamically allocated objects and no other references to them exist.
 *
 * @param[in, out] list The list to clear.
 */
void scu_list_clear(void* list);

/**
 * @brief Trims the excess capacity of a specified list to match its current
 * number of elements.
 *
 * This function reduces the capacity of the specified list to match its current
 * number of elements. If the capacity is already equal to the number of
 * elements, no reallocation occurs and the pointer to the list remains valid.
 * Otherwise, the list is reallocated using `scu_realloc()` and the pointer to
 * the new block of memory is assigned to `*list`.
 *
 * @note This function is an implementation detail and not intended to be called
 * directly. Use the `scu_list_trim_excess()` macro instead.
 *
 * This function dynamically allocates memory using `scu_realloc()`. The pointer
 * assigned to `*list` is suitably aligned for any type with fundamental
 * alignment requirements.
 *
 * @warning The caller is responsible for updating any existing pointers to the
 * list using the pointer assigned to `*list`, as previous pointers may have
 * been invalidated due to reallocation.
 *
 * @param[in, out] list The list to trim.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
ScuError scu_list_trim_excess_impl(void** list);

/**
 * @brief Trims the excess capacity of a specified list to match its current
 * number of elements.
 *
 * This macro reduces the capacity of the specified list to match its current
 * number of elements. If the capacity is already equal to the number of
 * elements, no reallocation occurs and the pointer to the list remains valid.
 * Otherwise, the list is reallocated using `scu_realloc()` and the pointer to
 * the new block of memory is assigned to `*list`.
 *
 * @note This macro dynamically allocates memory using `scu_realloc()`. The
 * pointer assigned to `*list` is suitably aligned for any type with fundamental
 * alignment requirements.
 *
 * @warning The caller is responsible for updating any existing pointers to the
 * list using the pointer assigned to `*list`, as previous pointers may have
 * been invalidated due to reallocation.
 *
 * @param[in, out] list The list to trim.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
#define scu_list_trim_excess(list) scu_list_trim_excess_impl((void**) (list))

/**
 * @brief Sorts a specified list using a provided comparison function.
 *
 * @note No guarantees are made regarding the complexity and stability of the
 * underlying sorting algorithm. Most importantly, if two elements are
 * considered equivalent by the provided comparison function, their relative
 * order in the sorted list may not be the same as in the original list.
 *
 * @warning The behavior is undefined if `cmpFunc` modifies the elements passed
 * to it, or if `cmpFunc` returns inconsistent results when called more than
 * once with the same arguments.
 *
 * @param[in, out] list    The list to sort.
 * @param[in]      cmpFunc A comparison function used to determine the order of
 *                         the elements.
 */
void scu_list_sort(void* list, ScuCompareFunc* cmpFunc);

/**
 * @brief Deallocates a specified list.
 *
 * @note If `list` is a `nullptr`, this function does nothing.
 *
 * @warning This function only deallocates the memory occupied by the list
 * itself, but not the elements contained within. The caller is responsible for
 * deallocating the individual elements if they are pointers to dynamically
 * allocated objects and no other references to them exist.
 *
 * The behavior is undefined if `list` is used after it has been deallocated.
 *
 * @param[in, out] list The list to deallocate.
 */
void scu_list_free(void* list);

/**
 * @brief Iterates over each element in a specified list.
 *
 * This macro expands to a for loop that iterates over each element in the
 * specified list. During each iteration, the provided variable is assigned a
 * pointer to the current element.
 *
 * The following example demonstrates the basic usage of this macro:
 *
 * ```c
 * // T is the type of the elements stored in the list.
 * T* list = scu_list_new(SCU_SIZEOF(T));
 * ...
 * T* elem;
 * SCU_LIST_FOREACH(elem, list) {
 *     // Do something with *elem.
 * }
 * ```
 *
 * @note The variable `elem` must be declared manually before the loop. It must
 * be of a pointer type compatible with the list's element type.
 *
 * @warning The behavior is undefined if the list is modified (e.g., elements
 * are added or removed) while being iterated over.
 *
 * @param[out] elem A pointer to the current element during each iteration.
 * @param[in]  list The list to iterate over.
 */
#define SCU_LIST_FOREACH(elem, list)                                          \
    for ((elem) = (list); (elem) < ((list) + scu_list_count(list)); (elem)++)

#endif