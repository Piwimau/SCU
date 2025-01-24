#ifndef SCU_MEMORY_H
#define SCU_MEMORY_H

#include <stdlib.h>

/**
 * @brief Allocates a block of uninitialized memory.
 *
 * @note If `size` is zero, the behavior is implementation-defined.
 *
 * @param[in] size Size of the block to allocate (in bytes).
 * @return A pointer to an uninitialized block of memory on success, or a `nullptr` if an
 * out-of-memory condition occurred.
 */
#define SCU_MALLOC(size) malloc(size)

/**
 * @brief Allocates a block of zero-initialized memory.
 *
 * @note If `size` is zero, the behavior is implementation-defined.
 *
 * @param[in] count Number of elements in the block.
 * @param[in] size  Size of each element (in bytes).
 * @return A pointer to a zero-initialized block of memory on success, or a `nullptr` if an
 * out-of-memory condition occurred.
 */
#define SCU_CALLOC(count, size) calloc(count, size)

/**
 * @brief Reallocates a block of memory previously allocated by `SCU_MALLOC()`, `SCU_CALLOC()` or
 * `SCU_REALLOC()`.
 *
 * @warning If `size` is zero, the behavior is undefined.
 *
 * If the reallocation fails due to an out-of-memory condition, the pointer to the original block of
 * memory remains valid and must be passed to `SCU_FREE()` to avoid a memory leak. Therefore, do not
 * assign the return value of `SCU_REALLOC()` directly to the original pointer, as this could result
 * in losing the reference to the original block of memory.
 *
 * If the reallocation succeeds, the pointer to the original block of memory is invalidated and must
 * not be used anymore (and especially not be passed to `SCU_FREE()`). If the block was expanded,
 * the content of any new locations in memory is undefined.
 *
 * @param[in] pointer Pointer to the block of memory to reallocate. It is allowed to be a `nullptr`,
 *                    in which case it behaves like calling `SCU_MALLOC()` with the given size.
 * @param[in] size    Size to reallocate the block to (in bytes).
 * @return A pointer to the reallocated block of memory on success, or a `nullptr` if an
 * out-of-memory condition occurred.
 */
#define SCU_REALLOC(pointer, size) realloc(pointer, size)

/**
 * @brief Deallocates a block of memory previously allocated by `SCU_MALLOC()`, `SCU_CALLOC()` or
 * `SCU_REALLOC()`.
 *
 * @note For convenience, `pointer` is allowed to be a `nullptr`.
 *
 * @warning The behavior is undefined if the block of memory pointed to by `pointer` was not
 * previously allocated by `SCU_MALLOC()`, `SCU_CALLOC()` or `SCU_REALLOC()`, or if it has already
 * been deallocated.
 *
 * @param[in] pointer Pointer to the block of memory to deallocate.
 */
#define SCU_FREE(pointer) free(pointer)

#endif