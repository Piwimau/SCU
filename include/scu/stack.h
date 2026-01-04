#ifndef SCU_STACK_H
#define SCU_STACK_H

#include "scu/error.h"
#include "scu/types.h"

/** @brief Represents a last-in-first-out (LIFO) collection of elements. */
typedef struct SCUStack SCUStack;

/**
 * @brief Represents an iterator for a stack.
 *
 * @warning The internal representation of the iterator is an implementation
 * detail and should not be relied upon. Most importantly, the behavior is
 * undefined if its fields are accessed directly.
 */
typedef struct SCUStackIter {

    /** @brief The stack being iterated over. */
    SCUStack* stack;

    /** @brief The current index within the stack. */
    SCUisize index;

} SCUStackIter;

/**
 * @brief Allocates and initializes a new stack with a specified element size
 * and an unspecified default capacity.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`.
 *
 * @warning The caller is responsible for deallocating the stack with
 * `scu_stack_free()` when it is no longer needed.
 *
 * @param[in] elemSize The size of each element (in bytes).
 * @return A pointer to the new stack, or `nullptr` on failure.
 */
[[nodiscard]]
SCUStack* scu_stack_new(SCUisize elemSize);

/**
 * @brief Allocates and initializes a new stack with a specified element size
 * and initial capacity.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`.
 *
 * @warning The caller is responsible for deallocating the stack with
 * `scu_stack_free()` when it is no longer needed.
 *
 * @param[in] elemSize The size of each element (in bytes).
 * @param[in] capacity The initial capacity (in number of elements).
 * @return A pointer to the new stack, or `nullptr` on failure.
 */
[[nodiscard]]
SCUStack* scu_stack_new_with_capacity(SCUisize elemSize, SCUisize capacity);

/**
 * @brief Creates a shallow copy of a specified stack.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`.
 *
 * @warning The caller is responsible for deallocating the cloned stack with
 * `scu_stack_free()` when it is no longer needed.
 *
 * @param[in] stack The stack to clone.
 * @return A pointer to the cloned stack, or `nullptr` on failure.
 */
[[nodiscard]]
SCUStack* scu_stack_clone(const SCUStack* stack);

/**
 * @brief Returns the capacity of a specified stack, i.e., the maximum number of
 * elements that can be stored before a reallocation is required.
 *
 * @note The capacity can be influenced to a certain extent using
 * `scu_stack_ensure_capacity()` and `scu_stack_trim_excess()`. See their
 * respective documentation for details.
 *
 * @param[in] stack The stack to examine.
 * @return The capacity of the specified stack.
 */
SCUisize scu_stack_capacity(const SCUStack* stack);

/**
 * @brief Returns the number of elements in a specified stack.
 *
 * @param[in] stack The stack to examine.
 * @return The number of elements in the specified stack.
 */
SCUisize scu_stack_count(const SCUStack* stack);

/**
 * @brief Ensures that a specified stack has at least a specified capacity.
 *
 * @note This function dynamically allocates memory using `scu_realloc()`.
 *
 * @param[in, out] stack    The stack to ensure the capacity of.
 * @param[in]      capacity The desired capacity (in number of elements).
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_stack_ensure_capacity(SCUStack* stack, SCUisize capacity);

/**
 * @brief Pushes a new element onto the top of a specified stack.
 *
 * @note This function dynamically allocates memory using `scu_realloc()`.
 *
 * @param[in, out] stack The stack to push the element onto.
 * @param[in]      elem  The element to push onto the stack.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_stack_push(SCUStack* restrict stack, const void* restrict elem);

/**
 * @brief Removes the top element from a specified stack.
 *
 * @warning The behavior is undefined if the stack is empty.
 *
 * @param[in, out] stack The stack to remove the top element from.
 * @param[out]     elem  The removed top element.
 */
void scu_stack_pop(SCUStack* restrict stack, void* restrict elem);

/**
 * @brief Tries to remove the top element from a specified stack.
 *
 * @param[in, out] stack The stack to remove the top element from.
 * @param[out]     elem  The removed top element if the stack was not empty,
 *                       otherwise unmodified.
 * @return `true` if the top element was successfully removed, otherwise
 * `false`.
 */
bool scu_stack_try_pop(SCUStack* restrict stack, void* restrict elem);

/**
 * @brief Retrieves the top element of a specified stack without removing it.
 *
 * @note This function is an implementation detail and not intended to be called
 * directly. Use the `scu_stack_peek()` macro instead.
 *
 * @warning The behavior is undefined if the stack is empty.
 *
 * @param[in]  stack The stack to examine.
 * @param[out] elem  A pointer to the top element of the stack.
 */
void scu_stack_peek_impl(const SCUStack* restrict stack, void** restrict elem);

/**
 * @brief Retrieves the top element of a specified stack without removing it.
 *
 * @warning The behavior is undefined if the stack is empty.
 *
 * @param[in]  stack The stack to examine.
 * @param[out] elem  A pointer to the top element of the stack.
 */
#define scu_stack_peek(stack, elem) scu_stack_peek_impl(stack, (void**) (elem))

/**
 * @brief Tries to retrieve the top element of a specified stack without
 * removing it.
 *
 * @note This function is an implementation detail and not intended to be called
 * directly. Use the `scu_stack_try_peek()` macro instead.
 *
 * @param[in]  stack The stack to examine.
 * @param[out] elem  A pointer to the top element of the stack on success,
 *                   otherwise a `nullptr`.
 * @return `true` if the top element was successfully retrieved, otherwise
 * `false`.
 */
bool scu_stack_try_peek_impl(
    const SCUStack* restrict stack,
    void** restrict elem
);

/**
 * @brief Tries to retrieve the top element of a specified stack without
 * removing it.
 *
 * @param[in]  stack The stack to examine.
 * @param[out] elem  A pointer to the top element of the stack on success,
 *                   otherwise a `nullptr`.
 * @return `true` if the top element was successfully retrieved, otherwise
 * `false`.
 */
#define scu_stack_try_peek(stack, elem)             \
    scu_stack_try_peek_impl(stack, (void**) (elem))

/**
 * @brief Removes all elements from a specified stack.
 *
 * @note Consider using `scu_stack_trim_excess()` if you wish to reduce the
 * memory usage of the stack after clearing it.
 *
 * @warning This function does not deallocate the stack itself nor the elements
 * contained within, it only resets the number of elements to zero. The caller
 * is responsible for deallocating the individual elements if they are pointers
 * to dynamically allocated objects and no other references to them exist.
 *
 * @param[in, out] stack The stack to clear.
 */
void scu_stack_clear(SCUStack* stack);

/**
 * @brief Trims the excess capacity of a specified stack to match its current
 * number of elements.
 *
 * @note This function dynamically allocates memory using `scu_realloc()`.
 *
 * @param[in, out] stack The stack to trim.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_stack_trim_excess(SCUStack* stack);

/**
 * @brief Returns an iterator for a specified stack.
 *
 * @note The iterator is initially positioned before the top element of the
 * stack (if any). This means that `scu_stack_iter_move_next()` must be called
 * before accessing the top and subsequent elements with
 * `scu_stack_iter_current()`.
 *
 * Note that the elements are iterated over in last-in-first-out (LIFO) order,
 * i.e., starting from the top element of the stack down to the bottom element.
 * This means that elements are retrieved in reverse order compared to how they
 * were added to the stack.
 *
 * @warning The behavior is undefined if the stack being iterated over is
 * modified (e.g., elements are added or removed) while the iterator is in use.
 *
 * @param[in] stack The stack to iterate over.
 * @return An iterator for the specified stack.
 */
SCUStackIter scu_stack_iter(const SCUStack* stack);

/**
 * @brief Advances a specified stack iterator to the next element.
 *
 * @param[in, out] iter The iterator to advance.
 * @return `true` if the iterator was successfully advanced to the next element,
 * otherwise `false` (i.e., the stack does not contain any more elements).
 */
bool scu_stack_iter_move_next(SCUStackIter* iter);

/**
 * @brief Returns the current element of a specified stack iterator.
 *
 * @param[in] iter The iterator to examine.
 * @return A pointer to the current element.
 */
void* scu_stack_iter_current(const SCUStackIter* iter);

/**
 * @brief Resets a specified stack iterator to its initial position.
 *
 * @note The iterator is initially positioned before the top element of the
 * stack (if any). This means that `scu_stack_iter_move_next()` must be called
 * before accessing the top and subsequent elements with
 * `scu_stack_iter_current()`.
 *
 * @param[in, out] iter The iterator to reset.
 */
void scu_stack_iter_reset(SCUStackIter* iter);

/**
 * @brief Deallocates a specified stack.
 *
 * @note If `stack` is a `nullptr`, this function does nothing.
 *
 * @warning This function only deallocates the memory occupied by the stack
 * itself, but not the elements contained within. The caller is responsible for
 * deallocating the individual elements if they are pointers to dynamically
 * allocated objects and no other references to them exist.
 *
 * The behavior is undefined if `stack` is used after it has been deallocated.
 *
 * @param[in, out] stack The stack to deallocate.
 */
void scu_stack_free(SCUStack* stack);

/**
 * @brief Iterates over each element in a specified stack.
 *
 * This macro expands to a for loop that iterates over each element in the
 * specified stack. During each iteration, the provided variable is assigned a
 * pointer to the current element.
 *
 * The following example demonstrates the basic usage of this macro:
 *
 * ```c
 * // T is the type of the elements stored in the stack.
 * SCUStack* stack = scu_stack_new(SCU_SIZEOF(T));
 * ...
 * T* elem;
 * SCU_STACK_FOREACH(elem, stack) {
 *     // Do something with *elem.
 * }
 * ```
 *
 * @note The variable `elem` must be declared manually before the loop. It must
 * be of a pointer type compatible with the stack's element type.
 *
 * @warning The behavior is undefined if the stack is modified (e.g., elements
 * are added or removed) while being iterated over.
 *
 * @param[out] elem  A pointer to the current element during each iteration.
 * @param[in]  stack The stack to iterate over.
 */
#define SCU_STACK_FOREACH(elem, stack)                                       \
    for (                                                                    \
        SCUStackIter SCU_XCONCAT(it, __LINE__) = scu_stack_iter(stack);      \
        scu_stack_iter_move_next(&SCU_XCONCAT(it, __LINE__))                 \
            && ((elem) = scu_stack_iter_current(&SCU_XCONCAT(it, __LINE__)), \
                true);                                                       \
    )

#endif