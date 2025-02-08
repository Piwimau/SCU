#ifndef SCU_LIST_H
#define SCU_LIST_H

#include <stdint.h>
#include <SCU/error.h>

/**
 * @brief Represents a dynamically resized collection of items that can be accessed by index.
 *
 * @note This is a convenience macro to highlight the fact that an `SCUList(T)` is at least
 * conceptually not the same as a regular `T*` (due to hidden metadata stored before the items).
 * However, it can be treated and used as such, and so this macro could simply be ignored if it
 * does not meet the requirements for style or clarity.
 *
 * @warning The type `T` must not be a function pointer type or a type with an alignment
 * requirement stricter than [`max_align_t`](https://en.cppreference.com/w/c/types/max_align_t).
 *
 * @param[in] T Type of the items to store in the `SCUList`.
 */
#define SCUList(T) T*

/**
 * @brief Allocates and initializes a new `SCUList` with a default capacity.
 *
 * @warning The type `T` must not be a function pointer type or a type with an alignment
 * requirement stricter than [`max_align_t`](https://en.cppreference.com/w/c/types/max_align_t).
 *
 * An `SCUList` returned by this function is dynamically allocated and must be passed to
 * `scu_list_free()` to avoid a memory leak.
 *
 * @param[in] T Type of the items to store in the `SCUList`.
 * @return A pointer to a new initialized `SCUList` on success, otherwise a `nullptr`.
 */
#define scu_list_new(T) scu_list_newInternal(sizeof(T))

/**
 * @brief Allocates and initializes a new `SCUList` with a specified initial capacity.
 *
 * @warning The type `T` must not be a function pointer type or a type with an alignment
 * requirement stricter than [`max_align_t`](https://en.cppreference.com/w/c/types/max_align_t).
 *
 * An `SCUList` returned by this function is dynamically allocated and must be passed to
 * `scu_list_free()` to avoid a memory leak.
 *
 * @param[in] capacity Initial capacity of the `SCUList`.
 * @param[in] T        Type of the items to store in the `SCUList`.
 * @return A pointer to a new initialized `SCUList` on success, otherwise a `nullptr`.
 */
#define scu_list_withCapacity(capacity, T) scu_list_withCapacityInternal(capacity, sizeof(T))

/**
 * @brief Returns the number of items a given `SCUList` can store before a reallocation is
 * required.
 *
 * @param[in] list `SCUList` to get the capacity of.
 * @return The number of items the given `SCUList` can store before a reallocation is required.
 */
#define scu_list_capacity(list) scu_list_capacityInternal(list)

/**
 * @brief Returns the current number of items in a given `SCUList`.
 *
 * @param[in] list `SCUList` to get the current number of items of.
 * @return The current number of items in the given `SCUList`.
 */
#define scu_list_count(list) scu_list_countInternal(list)

/**
 * @brief Returns the size of the items in a given `SCUList` (in bytes).
 *
 * @param[in] list `SCUList` to get the size of the items of.
 * @return The size of the items in the given `SCUList` (in bytes).
 */
#define scu_list_itemSize(list) scu_list_itemSizeInternal(list)

/**
 * @brief Determines if a given `SCUList` contains any items.
 *
 * @param[in] list `SCUList` to examine.
 * @return `true` if the given `SCUList` contains any items, otherwise `false`.
 */
#define scu_list_isEmpty(list) scu_list_isEmptyInternal(list)

/**
 * @brief Adds an item to the end of a given `SCUList`.
 *
 * @warning This operation may trigger a reallocation of the `SCUList`, assigning a new pointer to
 * the `list` parameter and invalidating any previous pointers to it in the process. Ensure that
 * any old pointers to the `SCUList` are updated accordingly.
 *
 * @param[in, out] list `SCUList` to add the item to.
 * @param[in]      item Item to add.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * otherwise `SCU_ERROR_NONE`.
 */
#define scu_list_add(list, item) \
    scu_list_addInternal((SCUList(void)*) &list, &(typeof(item)) { item })

/**
 * @brief Adds a contiguous sequence of items to the end of a given `SCUList`.
 *
 * @note If `count` is zero, `items` is ignored and may even be a `nullptr`.
 *
 * @warning This operation may trigger a reallocation of the `SCUList`, assigning a new pointer to
 * the `list` parameter and invalidating any previous pointers to it in the process. Ensure that
 * any old pointers to the `SCUList` are updated accordingly.
 *
 * The behavior is undefined if `count` is greater than zero and `items` does not point to a
 * contiguous sequence of at least `count * scu_list_itemSize()` bytes.
 *
 * @param[in, out] list  `SCUList` to add the contiguous sequence of items to.
 * @param[in]      items Pointer to a contiguous sequence of items to add.
 * @param[in]      count Number of items to add.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `count` is negative, `SCU_ERROR_OUT_OF_MEMORY` if an
 * out-of-memory condition occurred and `SCU_ERROR_NONE` otherwise.
 */
#define scu_list_addRange(list, items, count) \
    scu_list_addRangeInternal((SCUList(void)*) &list, items, count)

/**
 * @brief Inserts an item into a given `SCUList` at a specified index.
 *
 * @warning This operation may trigger a reallocation of the `SCUList`, assigning a new pointer to
 * the `list` parameter and invalidating any previous pointers to it in the process. Ensure that
 * any old pointers to the `SCUList` are updated accordingly.
 *
 * @param[in, out] list `SCUList` to insert the item into.
 * @param[in]      index Index to insert the item at.
 * @param[in]      item  Item to insert.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `index` is negative or greater than `scu_list_count()`,
 * `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred and `SCU_ERROR_NONE` otherwise.
 */
#define scu_list_insertAt(list, index, item) \
    scu_list_insertAtInternal((SCUList(void)*) &list, index, &(typeof(item)) { item })

/**
 * @brief Inserts a contiguous sequence of items into a given `SCUList` at a specified index.
 *
 * @note If `count` is zero, `items` is ignored and may even be a `nullptr`.
 *
 * @warning This operation may trigger a reallocation of the `SCUList`, assigning a new pointer to
 * the `list` parameter and invalidating any previous pointers to it in the process. Ensure that
 * any old pointers to the `SCUList` are updated accordingly.
 *
 * The behavior is undefined if `count` is greater than zero and `items` does not point to a
 * contiguous sequence of at least `count * scu_list_itemSize()` bytes.
 *
 * @param[in, out] list  `SCUList` to insert the contiguous sequence of items into.
 * @param[in]      index Index to insert the contiguous sequence of items at.
 * @param[in]      items Pointer to a contiguous sequence of items to insert.
 * @param[in]      count Number of items to insert.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `index` is negative or greater than `scu_list_count()`
 * or if `count` is negative, `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred and
 * `SCU_ERROR_NONE` otherwise.
 */
#define scu_list_insertRange(list, index, items, count) \
    scu_list_insertRangeInternal((SCUList(void)*) &list, index, items, count)

/**
 * @brief Removes an item from a given `SCUList` at a specified index.
 *
 * @param[in, out] list  `SCUList` to remove the item from.
 * @param[in]      index Index of the item to remove.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `index` is negative or greater than or equal to
 * `scu_list_count()`, otherwise `SCU_ERROR_NONE`.
 */
#define scu_list_removeAt(list, index) scu_list_removeAtInternal(list, index)

/**
 * @brief Removes a contiguous sequence of items from a given `SCUList` at a specified index.
 *
 * @param[in, out] list  `SCUList` to remove the contiguous sequence of items from.
 * @param[in]      index Index of the contiguous sequence of items to remove.
 * @param[in]      count Number of items to remove.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `index` or `count` is negative or if `index` and
 * `count` do not denote a valid contiguous sequence in the given `SCUList`,
 * otherwise `SCU_ERROR_NONE`.
 */
#define scu_list_removeRange(list, index, count) scu_list_removeRangeInternal(list, index, count)

/**
 * @brief Removes all items from a given `SCUList`.
 *
 * @param[in, out] list `SCUList` to remove all items from.
 */
#define scu_list_clear(list) scu_list_clearInternal(list)

/**
 * @brief Ensures that a given `SCUList` has at least a specified capacity.
 *
 * @warning This operation may trigger a reallocation of the `SCUList`, assigning a new pointer to
 * the `list` parameter and invalidating any previous pointers to it in the process. Ensure that
 * any old pointers to the `SCUList` are updated accordingly.
 *
 * @param[in, out] list     `SCUList` to ensure the capacity of.
 * @param[in]      capacity Minimum capacity to ensure.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `capacity` is negative, `SCU_ERROR_OUT_OF_MEMORY` if an
 * out-of-memory condition occurred and `SCU_ERROR_NONE` otherwise.
 */
#define scu_list_ensureCapacity(list, capacity) \
    scu_list_ensureCapacityInternal((SCUList(void)*) &list, capacity)

/**
 * @brief Reduces the capacity of a given `SCUList` to match its current number of items.
 *
 * @warning This operation may trigger a reallocation of the `SCUList`, assigning a new pointer to
 * the `list` parameter and invalidating any previous pointers to it in the process. Ensure that
 * any old pointers to the `SCUList` are updated accordingly.
 *
 * Trimming a large `SCUList` may have a significant runtime cost, while the reduction in memory
 * usage could be rather small in comparison. Consider checking `scu_list_capacity()` and
 * `scu_list_count()` to evaluate if trimming an overallocated `SCUList` is reasonable.
 *
 * @param[in, out] list `SCUList` to trim.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * otherwise `SCU_ERROR_NONE`.
 */
#define scu_list_trimToCount(list) scu_list_trimToCountInternal((SCUList(void)*) &list)

/**
 * @brief Deallocates a given `SCUList`.
 *
 * @note For convenience, `list` may be a `nullptr`.
 *
 * @warning Any use of the `SCUList` after it has been deallocated results in undefined behavior.
 *
 * @param[in, out] list `SCUList` to deallocate.
 */
#define scu_list_free(list) scu_list_freeInternal(list)

/**
 * @brief Allocates and initializes a new `SCUList` with a default capacity.
 *
 * @note This function is for internal use only. Use `scu_list_new()` instead.
 *
 * @warning The type `T` must not be a function pointer type or a type with an alignment
 * requirement stricter than [`max_align_t`](https://en.cppreference.com/w/c/types/max_align_t).
 *
 * An `SCUList` returned by this function is dynamically allocated and must be passed to
 * `scu_list_free()` to avoid a memory leak.
 *
 * @param[in] itemSize Size of the items to store in the `SCUList` (in bytes).
 * @return A pointer to a new initialized `SCUList` on success, otherwise a `nullptr`.
 */
SCUList(void) scu_list_newInternal(int64_t itemSize);

/**
 * @brief Allocates and initializes a new `SCUList` with a specified initial capacity.
 *
 * @note This function is for internal use only. Use `scu_list_withCapacity()` instead.
 *
 * @warning The type `T` must not be a function pointer type or a type with an alignment
 * requirement stricter than [`max_align_t`](https://en.cppreference.com/w/c/types/max_align_t).
 *
 * An `SCUList` returned by this function is dynamically allocated and must be passed to
 * `scu_list_free()` to avoid a memory leak.
 *
 * @param[in] capacity Initial capacity of the `SCUList`.
 * @param[in] itemSize Size of the items to store in the `SCUList` (in bytes).
 * @return A pointer to a new initialized `SCUList` on success, otherwise a `nullptr`.
 */
SCUList(void) scu_list_withCapacityInternal(int64_t capacity, int64_t itemSize);

/**
 * @brief Returns the number of items a given `SCUList` can store before a reallocation is
 * required.
 *
 * @note This function is for internal use only. Use `scu_list_capacity()` instead.
 *
 * @param[in] list `SCUList` to get the capacity of.
 * @return The number of items the given `SCUList` can store before a reallocation is required.
 */
int64_t scu_list_capacityInternal(const SCUList(void) list);

/**
 * @brief Returns the current number of items in a given `SCUList`.
 *
 * @note This function is for internal use only. Use `scu_list_count()` instead.
 *
 * @param[in] list `SCUList` to get the current number of items of.
 * @return The current number of items in the given `SCUList`.
 */
int64_t scu_list_countInternal(const SCUList(void) list);

/**
 * @brief Returns the size of the items in a given `SCUList` (in bytes).
 *
 * @note This function is for internal use only. Use `scu_list_itemSize()` instead.
 *
 * @param[in] list `SCUList` to get the size of the items of.
 * @return The size of the items in the given `SCUList` (in bytes).
 */
int64_t scu_list_itemSizeInternal(const SCUList(void) list);

/**
 * @brief Determines if a given `SCUList` contains any items.
 *
 * @note This function is for internal use only. Use `scu_list_isEmpty()` instead.
 *
 * @param[in] list `SCUList` to examine.
 * @return `true` if the given `SCUList` contains any items, otherwise `false`.
 */
bool scu_list_isEmptyInternal(const SCUList(void) list);

/**
 * @brief Adds an item to the end of a given `SCUList`.
 *
 * @note This function is for internal use only. Use `scu_list_add()` instead.
 *
 * @warning This operation may trigger a reallocation of the `SCUList`, assigning a new pointer to
 * the `list` parameter and invalidating any previous pointers to it in the process. Ensure that
 * any old pointers to the `SCUList` are updated accordingly.
 *
 * @param[in, out] list `SCUList` to add the item to.
 * @param[in]      item Item to add.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * otherwise `SCU_ERROR_NONE`.
 */
SCUError scu_list_addInternal(SCUList(void)* list, const void* item);

/**
 * @brief Adds a contiguous sequence of items to the end of a given `SCUList`.
 *
 * @note This function is for internal use only. Use `scu_list_addRange()` instead.
 *
 * If `count` is zero, `items` is ignored and may even be a `nullptr`.
 *
 * @warning This operation may trigger a reallocation of the `SCUList`, assigning a new pointer to
 * the `list` parameter and invalidating any previous pointers to it in the process. Ensure that
 * any old pointers to the `SCUList` are updated accordingly.
 *
 * The behavior is undefined if `count` is greater than zero and `items` does not point to a
 * contiguous sequence of at least `count * scu_list_itemSize()` bytes.
 *
 * @param[in, out] list  `SCUList` to add the contiguous sequence of items to.
 * @param[in]      items Pointer to a contiguous sequence of items to add.
 * @param[in]      count Number of items to add.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `count` is negative, `SCU_ERROR_OUT_OF_MEMORY` if an
 * out-of-memory condition occurred and `SCU_ERROR_NONE` otherwise.
 */
SCUError scu_list_addRangeInternal(SCUList(void)* list, const void* items, int64_t count);

/**
 * @brief Inserts an item into a given `SCUList` at a specified index.
 *
 * @note This function is for internal use only. Use `scu_list_insertAt()` instead.
 *
 * @warning This operation may trigger a reallocation of the `SCUList`, assigning a new pointer to
 * the `list` parameter and invalidating any previous pointers to it in the process. Ensure that
 * any old pointers to the `SCUList` are updated accordingly.
 *
 * @param[in, out] list `SCUList` to insert the item into.
 * @param[in]      index Index to insert the item at.
 * @param[in]      item  Item to insert.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `index` is negative or greater than `scu_list_count()`,
 * `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred and `SCU_ERROR_NONE` otherwise.
 */
SCUError scu_list_insertAtInternal(SCUList(void)* list, int64_t index, const void* item);

/**
 * @brief Inserts a contiguous sequence of items into a given `SCUList` at a specified index.
 *
 * @note This function is for internal use only. Use `scu_list_insertRange()` instead.
 *
 * If `count` is zero, `items` is ignored and may even be a `nullptr`.
 *
 * @warning This operation may trigger a reallocation of the `SCUList`, assigning a new pointer to
 * the `list` parameter and invalidating any previous pointers to it in the process. Ensure that
 * any old pointers to the `SCUList` are updated accordingly.
 *
 * The behavior is undefined if `count` is greater than zero and `items` does not point to a
 * contiguous sequence of at least `count * scu_list_itemSize()` bytes.
 *
 * @param[in, out] list  `SCUList` to insert the contiguous sequence of items into.
 * @param[in]      index Index to insert the contiguous sequence of items at.
 * @param[in]      items Pointer to a contiguous sequence of items to insert.
 * @param[in]      count Number of items to insert.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `index` is negative or greater than `scu_list_count()`
 * or if `count` is negative, `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred and
 * `SCU_ERROR_NONE` otherwise.
 */
SCUError scu_list_insertRangeInternal(
    SCUList(void)* list,
    int64_t index,
    const void* items,
    int64_t count
);

/**
 * @brief Removes an item from a given `SCUList` at a specified index.
 *
 * @note This function is for internal use only. Use `scu_list_removeAt()` instead.
 *
 * @param[in, out] list  `SCUList` to remove the item from.
 * @param[in]      index Index of the item to remove.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `index` is negative or greater than or equal to
 * `scu_list_count()`, otherwise `SCU_ERROR_NONE`.
 */
SCUError scu_list_removeAtInternal(SCUList(void) list, int64_t index);

/**
 * @brief Removes a contiguous sequence of items from a given `SCUList` at a specified index.
 *
 * @note This function is for internal use only. Use `scu_list_removeRange()` instead.
 *
 * @param[in, out] list  `SCUList` to remove the contiguous sequence of items from.
 * @param[in]      index Index of the contiguous sequence of items to remove.
 * @param[in]      count Number of items to remove.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `index` or `count` is negative or if `index` and
 * `count` do not denote a valid contiguous sequence in the given `SCUList`,
 * otherwise `SCU_ERROR_NONE`.
 */
SCUError scu_list_removeRangeInternal(SCUList(void) list, int64_t index, int64_t count);

/**
 * @brief Removes all items from a given `SCUList`.
 *
 * @note This function is for internal use only. Use `scu_list_clear()` instead.
 *
 * @param[in, out] list `SCUList` to remove all items from.
 */
void scu_list_clearInternal(SCUList(void) list);

/**
 * @brief Ensures that a given `SCUList` has at least a specified capacity.
 *
 * @note This function is for internal use only. Use `scu_list_ensureCapacity()` instead.
 *
 * @warning This operation may trigger a reallocation of the `SCUList`, assigning a new pointer to
 * the `list` parameter and invalidating any previous pointers to it in the process. Ensure that
 * any old pointers to the `SCUList` are updated accordingly.
 *
 * @param[in, out] list     `SCUList` to ensure the capacity of.
 * @param[in]      capacity Minimum capacity to ensure.
 * @return `SCU_ERROR_INVALID_ARGUMENT` if `capacity` is negative, `SCU_ERROR_OUT_OF_MEMORY` if an
 * out-of-memory condition occurred and `SCU_ERROR_NONE` otherwise.
 */
SCUError scu_list_ensureCapacityInternal(SCUList(void)* list, int64_t capacity);

/**
 * @brief Reduces the capacity of a given `SCUList` to match its current number of items.
 *
 * @note This function is for internal use only. Use `scu_list_trimToCount()` instead.
 *
 * @warning This operation may trigger a reallocation of the `SCUList`, assigning a new pointer to
 * the `list` parameter and invalidating any previous pointers to it in the process. Ensure that
 * any old pointers to the `SCUList` are updated accordingly.
 *
 * Trimming a large `SCUList` may have a significant runtime cost, while the reduction in memory
 * usage could be rather small in comparison. Consider checking `scu_list_capacity()` and
 * `scu_list_count()` to evaluate if trimming an overallocated `SCUList` is reasonable.
 *
 * @param[in, out] list `SCUList` to trim.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * otherwise `SCU_ERROR_NONE`.
 */
SCUError scu_list_trimToCountInternal(SCUList(void)* list);

/**
 * @brief Deallocates a given `SCUList`.
 *
 * @note This function is for internal use only. Use `scu_list_free()` instead.
 *
 * For convenience, `list` may be a `nullptr`.
 *
 * @warning Any use of the `SCUList` after it has been deallocated results in undefined behavior.
 *
 * @param[in, out] list `SCUList` to deallocate.
 */
void scu_list_freeInternal(SCUList(void) list);

#endif