#ifndef SCU_QUEUE_H
#define SCU_QUEUE_H

#include "scu/common.h"
#include "scu/error.h"
#include "scu/types.h"

/** @brief Represents a first-in-first-out (FIFO) collection of elements. */
typedef struct SCUQueue SCUQueue;

/**
 * @brief Represents an iterator for a queue.
 *
 * @warning The internal representation of the iterator is an implementation
 * detail and should not be relied upon. Most importantly, the behavior is
 * undefined if its fields are accessed directly.
 */
typedef struct SCUQueueIter {

    /** @brief The queue being iterated over. */
    SCUQueue* queue;

    /** @brief The current index within the queue. */
    SCUisize index;

} SCUQueueIter;

/**
 * @brief Allocates and initializes a new queue with a specified element size
 * and an unspecified default capacity.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`.
 *
 * @warning The caller is responsible for deallocating the queue with
 * `scu_queue_free()` when it is no longer needed.
 *
 * @param[in] elemSize The size of each element (in bytes).
 * @return A pointer to the new queue, or `nullptr` on failure.
 */
[[nodiscard]]
SCUQueue* scu_queue_new(SCUisize elemSize);

/**
 * @brief Allocates and initializes a new queue with a specified element size
 * and initial capacity.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`.
 *
 * @warning The caller is responsible for deallocating the queue with
 * `scu_queue_free()` when it is no longer needed.
 *
 * @param[in] elemSize The size of each element (in bytes).
 * @param[in] capacity The initial capacity (in number of elements).
 * @return A pointer to the new queue, or `nullptr` on failure.
 */
[[nodiscard]]
SCUQueue* scu_queue_new_with_capacity(SCUisize elemSize, SCUisize capacity);

/**
 * @brief Creates a shallow copy of a specified queue.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`.
 *
 * @warning The caller is responsible for deallocating the cloned queue with
 * `scu_queue_free()` when it is no longer needed.
 *
 * @param[in] queue The queue to clone.
 * @return A pointer to the cloned queue, or `nullptr` on failure.
 */
[[nodiscard]]
SCUQueue* scu_queue_clone(const SCUQueue* queue);

/**
 * @brief Returns the capacity of a specified queue, i.e., the maximum number of
 * elements that can be stored before a reallocation is required.
 *
 * @note The capacity can be influenced to a certain extent using
 * `scu_queue_ensure_capacity()` and `scu_queue_trim_excess()`. See their
 * respective documentation for details.
 *
 * @param[in] queue The queue to examine.
 * @return The capacity of the specified queue.
 */
SCUisize scu_queue_capacity(const SCUQueue* queue);

/**
 * @brief Returns the number of elements stored in a specified queue.
 *
 * @param[in] queue The queue to examine.
 * @return The number of elements stored in the specified queue.
 */
SCUisize scu_queue_count(const SCUQueue* queue);

/**
 * @brief Ensures that a specified queue has at least a specified capacity.
 * 
 * @note This function dynamically allocates memory using `scu_malloc()`.
 *
 * @param[in, out] queue    The queue to ensure the capacity of.
 * @param[in]      capacity The desired capacity (in number of elements).
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_queue_ensure_capacity(SCUQueue* queue, SCUisize capacity);

/**
 * @brief Enqueues a new element into a specified queue.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`.
 *
 * @param[in, out] queue The queue to enqueue the element into.
 * @param[in]      elem  The element to enqueue.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_queue_enqueue(SCUQueue* restrict queue, const void* restrict elem);

/**
 * @brief Dequeues the element at the front of a specified queue.
 *
 * @warning The behavior is undefined if the queue is empty. Use
 * `scu_queue_try_dequeue()` to handle this case gracefully.
 *
 * @param[in, out] queue The queue to dequeue the element from.
 * @param[out]     elem  The dequeued element.
 */
void scu_queue_dequeue(SCUQueue* restrict queue, void* restrict elem);

/**
 * @brief Tries to dequeue the element at the front of a specified queue.
 *
 * @param[in, out] queue The queue to dequeue the element from.
 * @param[out]     elem  The dequeued element on success, otherwise unchanged.
 * @return `true` if an element was successfully dequeued, otherwise `false`.
 */
bool scu_queue_try_dequeue(SCUQueue* restrict queue, void* restrict elem);

/**
 * @brief Returns the element at the front of a specified queue without removing
 * it.
 *
 * @note This function is an implementation detail and not intended to be called
 * directly. Use the `scu_queue_peek()` macro instead.
 *
 * @warning The behavior is undefined if the queue is empty. Use
 * `scu_queue_try_peek()` to handle this case gracefully.
 *
 * @param[in]  queue The queue to examine.
 * @param[out] elem  A pointer to the element at the front of the queue.
 */
void scu_queue_peek_impl(const SCUQueue* restrict queue, void** restrict elem);

/**
 * @brief Returns the element at the front of a specified queue without removing
 * it.
 *
 * @warning The behavior is undefined if the queue is empty. Use
 * `scu_queue_try_peek()` to handle this case gracefully.
 *
 * @param[in]  queue The queue to examine.
 * @param[out] elem  A pointer to the element at the front of the queue.
 */
#define scu_queue_peek(queue, elem) scu_queue_peek_impl(queue, (void**) (elem))

/**
 * @brief Tries to return the element at the front of a specified queue without
 * removing it.
 *
 * @note This function is an implementation detail and not intended to be called
 * directly. Use the `scu_queue_try_peek()` macro instead.
 *
 * @param[in]  queue The queue to examine.
 * @param[out] elem  A pointer to the element at the front of the queue on
 *                   success, otherwise a `nullptr`.
 * @return `true` if an element was successfully retrieved, otherwise `false`.
 */
bool scu_queue_try_peek_impl(
    const SCUQueue* restrict queue,
    void** restrict elem
);

/**
 * @brief Tries to return the element at the front of a specified queue without
 * removing it.
 *
 * @param[in]  queue The queue to examine.
 * @param[out] elem  A pointer to the element at the front of the queue on
 *                   success, otherwise a `nullptr`.
 * @return `true` if an element was successfully retrieved, otherwise `false`.
 */
#define scu_queue_try_peek(queue, elem)             \
    scu_queue_try_peek_impl(queue, (void**) (elem))

/**
 * @brief Removes all elements from a specified queue.
 *
 * @note Consider using `scu_queue_trim_excess()` if you wish to reduce the
 * memory usage of the queue after clearing it.
 *
 * @warning This function does not deallocate the queue itself nor the elements
 * contained within, it only resets the number of elements to zero. The caller
 * is responsible for deallocating the individual elements if they are pointers
 * to dynamically allocated objects and no other references to them exist.
 *
 * @param[in, out] queue The queue to clear.
 */
void scu_queue_clear(SCUQueue* queue);

/**
 * @brief Trims the excess capacity of a specified queue to match its current
 * number of elements.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`.
 *
 * @param[in, out] queue The queue to trim.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
SCUError scu_queue_trim_excess(SCUQueue* queue);

/**
 * @brief Returns an iterator for a specified queue.
 *
 * @note The iterator is initially positioned before the first element of the
 * queue (if any). This means that `scu_queue_iter_move_next()` must be called
 * before accessing the first and subsequent elements with
 * `scu_queue_iter_current()`.
 *
 * The elements are returned in the order they would be dequeued, i.e., starting
 * from the front of the queue all the way to the back.
 *
 * @warning The behavior is undefined if the queue is modified (e.g., elements
 * are enqueued or dequeued) while the iterator is in use.
 *
 * @param[in] queue The queue to iterate over.
 * @return An iterator for the specified queue.
 */
SCUQueueIter scu_queue_iter(const SCUQueue* queue);

/**
 * @brief Advances a specified queue iterator to the next element.
 *
 * @param[in, out] iter The iterator to advance.
 * @return `true` if the iterator was successfully advanced to the next element,
 * otherwise `false` (i.e., the queue does not contain any more elements).
 */
bool scu_queue_iter_move_next(SCUQueueIter* iter);

/**
 * @brief Returns the current element of a specified queue iterator.
 *
 * @param[in] iter The iterator to examine.
 * @return The current element of the iterator.
 */
void* scu_queue_iter_current(const SCUQueueIter* iter);

/**
 * @brief Resets a specified queue iterator to its initial position.
 *
 * @note The iterator is initially positioned before the first element of the
 * queue (if any). This means that `scu_queue_iter_move_next()` must be called
 * before accessing the first and subsequent elements with
 * `scu_queue_iter_current()`.
 *
 * @param[in, out] iter The iterator to reset.
 */
void scu_queue_iter_reset(SCUQueueIter* iter);

/**
 * @brief Deallocates a specified queue.
 *
 * @note If `queue` is a `nullptr`, this function does nothing.
 *
 * @warning This function only deallocates the memory occupied by the queue
 * itself, but not the elements contained within. The caller is responsible for
 * deallocating the individual elements if they are pointers to dynamically
 * allocated objects and no other references to them exist.
 *
 * The behavior is undefined if the queue is used after it has been deallocated.
 *
 * @param[in] queue The queue to deallocate.
 */
void scu_queue_free(SCUQueue* queue);

/**
 * @brief Iterates over each element in a specified queue.
 *
 * This macro expands to a for loop that iterates over each element in the
 * specified queue. During each iteration, the provided variable is assigned a
 * pointer to the current element.
 *
 * The following example demonstrates the basic usage of this macro:
 *
 * ```c
 * // T is the type of the elements stored in the queue.
 * SCUQueue* queue = scu_queue_new(sizeof(T));
 * ...
 * T* elem;
 * SCU_QUEUE_FOREACH(elem, queue) {
 *     // Do something with *elem.
 * }
 * ```
 *
 * @note The variable `elem` must be declared manually before the loop. It must
 * be of a pointer type compatible with the queue's element type.
 *
 * The elements are returned in the order they would be dequeued, i.e., starting
 * from the front of the queue all the way to the back.
 *
 * @warning The behavior is undefined if the queue is modified (e.g., elements
 * are enqueued or dequeued) while being iterated over.
 *
 * @param[out] elem  A pointer to the current element during each iteration.
 * @param[in]  queue The queue to iterate over.
 */
#define SCU_QUEUE_FOREACH(elem, queue)                                       \
    for (                                                                    \
        SCUQueueIter SCU_XCONCAT(it, __LINE__) = scu_queue_iter(queue);      \
        scu_queue_iter_move_next(&SCU_XCONCAT(it, __LINE__))                 \
            && (                                                             \
                (elem) = scu_queue_iter_current(&SCU_XCONCAT(it, __LINE__)), \
                true                                                         \
            );                                                               \
    )

#endif