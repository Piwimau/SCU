#include <stddef.h>
#include <string.h>
#include <SCU/list.h>
#include <SCU/math.h>
#include <SCU/memory.h>

/** @brief Represents a header used to store important metadata for an `SCUList`. */
typedef struct SCUHeader {

    /** @brief Number of items the `SCUList` can store before a reallocation is required. */
    int64_t capacity;

    /** @brief Current number of items in the `SCUList`. */
    int64_t count;

    /** @brief Size of the items in the `SCUList` (in bytes). */
    int64_t itemSize;

    /**
     * @brief Items stored in the `SCUList`.
     *
     * @note This is a [flexible array member](https://en.cppreference.com/w/c/language/struct),
     * that allows us to store the `SCUHeader` and the items of the `SCUList` in a single block of
     * memory. This has two major advantages: We can hand out a pointer to the items to the user,
     * who can (more or less) treat it as any regular array and use the convenient indexing syntax
     * to access individual items. In addition, allocating a single block of memory is likely more
     * efficient, as it avoids the double indirection that would otherwise be required if the items
     * were stored in a separate `void*` allocation.
     *
     * Note that the `SCUHeader` is aligned with the same strict requirement as
     * [`max_align_t`](https://en.cppreference.com/w/c/types/max_align_t) to ensure proper
     * alignment of the items for any type with a fundamental alignment requirement. Without this
     * alignment, accessing items of types with a stricter alignment than `void*` (such as
     * `long double` on some platforms) could cause performance penalties or crashes due to
     * misaligned memory access.
     */
    alignas(max_align_t) unsigned char items[];

} SCUHeader;

/** @brief Initial capacity of an `SCUList`. */
static constexpr int64_t SCU_INITIAL_CAPACITY = 8;

/**
 * @brief Returns the `SCUHeader` of a given `SCUList`.
 *
 * @param[in] list `SCUList` to return the `SCUHeader` of.
 * @return The `SCUHeader` of the given `SCUList`.
 */
static inline SCUHeader* scu_list_header(const SCUList(void) list) {
    return ((SCUHeader*) list) - 1;
}

/**
 * @brief Returns a pointer to the item at a specified index in a given `SCUList`.
 *
 * @param[in] header `SCUHeader` of the `SCUList`.
 * @param[in] index  Index of the item to return a pointer to.
 * @return A pointer to the item at the specified index in ther given `SCUList`.
 */
static inline void* scu_list_itemAt(const SCUHeader* header, int64_t index) {
    return ((unsigned char*) header->items) + (index * header->itemSize);
}

SCUList(void) scu_list_newInternal(int64_t itemSize) {
    return scu_list_withCapacityInternal(SCU_INITIAL_CAPACITY, itemSize);
}

SCUList(void) scu_list_withCapacityInternal(int64_t capacity, int64_t itemSize) {
    if ((capacity < 0) || (itemSize <= 0)) {
        return nullptr;
    }
    SCUHeader* header = SCU_MALLOC(sizeof(SCUHeader) + (capacity * itemSize));
    if (header == nullptr) {
        return nullptr;
    }
    header->capacity = capacity;
    header->count = 0;
    header->itemSize = itemSize;
    return header->items;
}

int64_t scu_list_capacityInternal(const SCUList(void) list) {
    return scu_list_header(list)->capacity;
}

int64_t scu_list_countInternal(const SCUList(void) list) {
    return scu_list_header(list)->count;
}

int64_t scu_list_itemSizeInternal(const SCUList(void) list) {
    return scu_list_header(list)->itemSize;
}

bool scu_list_isEmptyInternal(const SCUList(void) list) {
    return scu_list_header(list)->count == 0;
}

SCUError scu_list_addInternal(SCUList(void)* list, const void* item) {
    SCUHeader* header = scu_list_header(*list);
    SCUError error = scu_list_ensureCapacityInternal(list, header->count + 1);
    if (error != SCU_ERROR_NONE) {
        return error;
    }
    // The list may have been moved around in memory due to a reallocation, we therefore need to
    // get the header a second time.
    header = scu_list_header(*list);
    memcpy(scu_list_itemAt(header, header->count), item, header->itemSize);
    header->count++;
    return SCU_ERROR_NONE;
}

SCUError scu_list_addRangeInternal(SCUList(void)* list, const void* items, int64_t count) {
    if (count < 0) {
        return SCU_ERROR_INVALID_ARGUMENT;
    }
    if (count > 0) {
        SCUHeader* header = scu_list_header(*list);
        SCUError error = scu_list_ensureCapacityInternal(list, header->count + count);
        if (error != SCU_ERROR_NONE) {
            return error;
        }
        // The list may have been moved around in memory due to a reallocation, we therefore need
        // to get the header a second time.
        header = scu_list_header(*list);
        memcpy(scu_list_itemAt(header, header->count), items, count * header->itemSize);
        header->count += count;
    }
    return SCU_ERROR_NONE;
}

SCUError scu_list_insertAtInternal(SCUList(void)* list, int64_t index, const void* item) {
    SCUHeader* header = scu_list_header(*list);
    if ((index < 0) || (index > header->count)) {
        return SCU_ERROR_INVALID_ARGUMENT;
    }
    SCUError error = scu_list_ensureCapacityInternal(list, header->count + 1);
    if (error != SCU_ERROR_NONE) {
        return error;
    }
    // The list may have been moved around in memory due to a reallocation, we therefore need to
    // get the header a second time.
    header = scu_list_header(*list);
    memmove(
        scu_list_itemAt(header, index + 1),
        scu_list_itemAt(header, index),
        (header->count - index) * header->itemSize
    );
    memcpy(scu_list_itemAt(header, index), item, header->itemSize);
    header->count++;
    return SCU_ERROR_NONE;
}

SCUError scu_list_insertRangeInternal(
    SCUList(void)* list,
    int64_t index,
    const void* items,
    int64_t count
) {
    SCUHeader* header = scu_list_header(*list);
    if ((index < 0) || (index > header->count) || (count < 0)) {
        return SCU_ERROR_INVALID_ARGUMENT;
    }
    if (count > 0) {
        SCUError error = scu_list_ensureCapacityInternal(list, header->count + count);
        if (error != SCU_ERROR_NONE) {
            return error;
        }
        // The list may have been moved around in memory due to a reallocation, we therefore need
        // to get the header a second time.
        header = scu_list_header(*list);
        memmove(
            scu_list_itemAt(header, index + count),
            scu_list_itemAt(header, index),
            (header->count - index) * header->itemSize
        );
        memcpy(scu_list_itemAt(header, index), items, count * header->itemSize);
        header->count += count;
    }
    return SCU_ERROR_NONE;
}

SCUError scu_list_removeAtInternal(SCUList(void) list, int64_t index) {
    SCUHeader* header = scu_list_header(list);
    if ((index < 0) || (index >= header->count)) {
        return SCU_ERROR_INVALID_ARGUMENT;
    }
    memmove(
        scu_list_itemAt(header, index),
        scu_list_itemAt(header, index + 1),
        (header->count - index - 1) * header->itemSize
    );
    header->count--;
    return SCU_ERROR_NONE;
}

SCUError scu_list_removeRangeInternal(SCUList(void) list, int64_t index, int64_t count) {
    SCUHeader* header = scu_list_header(list);
    if ((index < 0) || (count < 0) || ((index + count) > header->count)) {
        return SCU_ERROR_INVALID_ARGUMENT;
    }
    if (count > 0) {
        memmove(
            scu_list_itemAt(header, index),
            scu_list_itemAt(header, index + count),
            (header->count - index - count) * header->itemSize
        );
        header->count -= count;
    }
    return SCU_ERROR_NONE;
}

void scu_list_clearInternal(SCUList(void) list) {
    scu_list_header(list)->count = 0;
}

SCUError scu_list_ensureCapacityInternal(SCUList(void)* list, int64_t capacity) {
    if (capacity < 0) {
        return SCU_ERROR_INVALID_ARGUMENT;
    }
    SCUHeader* header = scu_list_header(*list);
    if (header->capacity < capacity) {
        int64_t newCapacity = SCU_MAX(header->capacity, SCU_INITIAL_CAPACITY);
        while (newCapacity < capacity) {
            // Resizing with a factor of 1.5 wastes less memory than simply doubling the capacity
            // and may actually allow us to reuse some blocks of memory.
            newCapacity = (newCapacity * 3 / 2) + 1;
        }
        SCUHeader* newHeader = SCU_REALLOC(
            header,
            sizeof(SCUHeader) + (newCapacity * header->itemSize)
        );
        if (newHeader == nullptr) {
            return SCU_ERROR_OUT_OF_MEMORY;
        }
        newHeader->capacity = newCapacity;
        *list = newHeader->items;
    }
    return SCU_ERROR_NONE;
}

SCUError scu_list_trimToCountInternal(SCUList(void)* list) {
    SCUHeader* header = scu_list_header(*list);
    if (header->capacity > header->count) {
        SCUHeader* newHeader = SCU_REALLOC(
            header,
            sizeof(SCUHeader) + (header->count * header->itemSize)
        );
        if (newHeader == nullptr) {
            return SCU_ERROR_OUT_OF_MEMORY;
        }
        newHeader->capacity = newHeader->count;
        *list = newHeader->items;
    }
    return SCU_ERROR_NONE;
}

void scu_list_freeInternal(SCUList(void) list) {
    if (list != nullptr) {
        SCU_FREE(scu_list_header(list));
    }
}