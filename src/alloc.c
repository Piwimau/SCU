#include <inttypes.h>
#include <stdatomic.h>
#include <stdlib.h>
#include "scu/alloc.h"
#include "scu/assert.h"
#include "scu/common.h"

/**
 * @brief Represents a header stored before each allocated block of memory.
 *
 * The header stores a pointer to the original allocator the block of memory was
 * allocated with, such that `scu_realloc()` and `scu_free()` use the correct
 * allocator even if a different global allocator is later set using
 * `scu_set_allocator()`.
 *
 * In debug builds, a magic number is stored in the header as well, to help
 * detect memory corruption.
 */
typedef struct SCUHeader {

    /** @brief The original allocator the block of memory was allocated with. */
    const SCUAllocator* allocator;

#ifndef NDEBUG
    /** @brief A magic number used to help detect memory corruption. */
    uint64_t magic;
#endif

    /**
     * @brief The actual payload (i.e., the block of memory returned to the
     * user).
     *
     * Note that this is a so-called flexible array member, which is aligned as
     * strictly as `max_align_t` to ensure proper alignment for any type with
     * fundamental alignment requirements.
     */
    alignas(max_align_t) unsigned char payload[];

} SCUHeader;

#ifndef NDEBUG

/** @brief A magic number used to help detect memory corruption. */
static constexpr uint64_t SCU_HEADER_MAGIC = 0xCAFEBABEDEADBEEFULL;

#endif

/**
 * @brief Allocates an uninitialized block of memory of at least `size`
 * contiguous bytes using the C standard `malloc()` function.
 *
 * @param[in, out] context Unused.
 * @param[in]      size    The requested size (in bytes).
 * @return A pointer to an uninitialized block of memory of at least `size`
 * contiguous bytes, or `nullptr` on failure.
 */
[[nodiscard]]
static void* scu_default_malloc([[maybe_unused]] void* context, int64_t size) {
    return malloc((size_t) size);
}

/**
 * @brief Allocates a zero-initialized block of memory of at least `count *
 * size` contiguous bytes using the C standard `calloc()` function.
 *
 * @param[in, out] context  Unused.
 * @param[in]      count    The requested number of elements.
 * @param[in]      size     The size of each element (in bytes).
 * @return A pointer to a zero-initialized block of memory of at least `count *
 * size` contiguous bytes, or `nullptr` on failure.
 */
[[nodiscard]]
static void* scu_default_calloc(
    [[maybe_unused]] void* context,
    int64_t count,
    int64_t size
) {
    return calloc((size_t) count, (size_t) size);
}

/**
 * @brief Reallocates a block of memory to at least `newSize` contiguous bytes
 * using the C standard `realloc()` function.
 *
 * @param[in, out] context Unused.
 * @param[in]      block   A pointer to a block of memory, or a `nullptr`.
 * @param[in]      newSize The new requested size (in bytes).
 * @return A pointer to the reallocated (and possibly moved) block of memory of
 * at least `newSize` contiguous bytes, or `nullptr` on failure.
 */
[[nodiscard]]
static void* scu_default_realloc(
    [[maybe_unused]] void* context,
    void* block,
    int64_t newSize
) {
    return realloc(block, (size_t) newSize);
}

/**
 * @brief Deallocates a block of memory using the C standard `free()` function.
 *
 * @param[in, out] context Unused.
 * @param[in]      block   A pointer to a block of memory to deallocate. If
 *                         equal to `nullptr`, this function does nothing.
 */
static void scu_default_free([[maybe_unused]] void* context, void* block) {
    free(block);
}

/** @brief The default allocator relying on the C standard library. */
static const SCUAllocator SCU_DEFAULT_ALLOCATOR = {
    .malloc = scu_default_malloc,
    .calloc = scu_default_calloc,
    .realloc = scu_default_realloc,
    .free = scu_default_free
};

/** @brief The global allocator (initially set to the default one). */
static const SCUAllocator* _Atomic scuGlobalAllocator = &SCU_DEFAULT_ALLOCATOR;

const SCUAllocator* scu_get_allocator() {
    return atomic_load_explicit(&scuGlobalAllocator, memory_order_acquire);
}

void scu_set_allocator(const SCUAllocator* allocator) {
    atomic_store_explicit(
        &scuGlobalAllocator,
        (allocator != nullptr) ? allocator : &SCU_DEFAULT_ALLOCATOR,
        memory_order_release
    );
}

/**
 * @brief Returns a pointer to the actual payload given the header of a block of
 * memory.
 *
 * @param[in] header A pointer to the header of the block of memory.
 * @return A pointer to the actual payload.
 */
static inline void* scu_header_to_payload(SCUHeader* header) {
    SCU_ASSERT(header != nullptr);
    SCU_ASSERT(
        header->magic == SCU_HEADER_MAGIC,
        "Detected invalid header (header = %p, magic = 0x%016" PRIX64
        ", expected = 0x%016" PRIX64 ").",
        header,
        header->magic,
        SCU_HEADER_MAGIC
    );
    return header->payload;
}

/**
 * @brief Returns a pointer to the header of a block of memory given its
 * payload.
 *
 * @param[in] payload A pointer to the actual payload.
 * @return A pointer to the header of the block of memory.
 */
static inline SCUHeader* scu_payload_to_header(void* payload) {
    SCU_ASSERT(payload != nullptr);
    SCUHeader* header = (SCUHeader*) (
        (unsigned char*) payload - SCU_SIZEOF(SCUHeader)
    );
    SCU_ASSERT(
        header->magic == SCU_HEADER_MAGIC,
        "Detected invalid header (header = %p, magic = 0x%016" PRIX64
        ", expected = 0x%016" PRIX64 ").",
        header,
        header->magic,
        SCU_HEADER_MAGIC
    );
    return header;
}

[[nodiscard]]
void* scu_malloc(int64_t size) {
    SCU_ASSERT(size >= 0);
    const SCUAllocator* allocator = scu_get_allocator();
    SCUHeader* header = allocator->malloc(
        allocator->context,
        SCU_SIZEOF(SCUHeader) + size
    );
    if (header == nullptr) {
        return nullptr;
    }
    header->allocator = allocator;
#ifndef NDEBUG
    header->magic = SCU_HEADER_MAGIC;
#endif
    return scu_header_to_payload(header);
}

[[nodiscard]]
void* scu_calloc(int64_t count, int64_t size) {
    SCU_ASSERT(count >= 0);
    SCU_ASSERT(size >= 0);
    const SCUAllocator* allocator = scu_get_allocator();
    SCUHeader* header = allocator->calloc(
        allocator->context,
        1,
        SCU_SIZEOF(SCUHeader) + (count * size)
    );
    if (header == nullptr) {
        return nullptr;
    }
    header->allocator = allocator;
#ifndef NDEBUG
    header->magic = SCU_HEADER_MAGIC;
#endif
    return scu_header_to_payload(header);
}

[[nodiscard]]
void* scu_realloc(void* block, int64_t newSize) {
    SCU_ASSERT(newSize >= 0);
    if (block == nullptr) {
        return scu_malloc(newSize);
    }
    SCUHeader* oldHeader = scu_payload_to_header(block);
    const SCUAllocator* allocator = oldHeader->allocator;
    SCUHeader* newHeader = allocator->realloc(
        allocator->context,
        oldHeader,
        SCU_SIZEOF(SCUHeader) + newSize
    );
    return (newHeader == nullptr) ? nullptr : scu_header_to_payload(newHeader);
}

void scu_free(void* block) {
    if (block != nullptr) {
        SCUHeader* header = scu_payload_to_header(block);
        const SCUAllocator* allocator = header->allocator;
        allocator->free(allocator->context, header);
    }
}