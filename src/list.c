#define SCU_SHORT_ALIASES

#include "scu/alloc.h"
#include "scu/array.h"
#include "scu/assert.h"
#include "scu/list.h"
#include "scu/memory.h"

/** @brief Represents a header stored before the actual data of the list. */
typedef struct SCUListHeader {

    /** @brief The size of each element (in bytes). */
    isize elemSize;

    /**
     * @brief The maximum number of elements that can be stored before a
     * reallocation is required.
     */
    isize capacity;

    /** @brief The current number of elements. */
    isize count;

    /**
     * @brief The actual data (i.e., the elements) stored after the header.
     *
     * @note This is a flexible array member, which is aligned as strictly as
     * `max_align_t` to ensure proper alignment for any type with fundamental
     * alignment requirements.
     */
    alignas(max_align_t) byte data[];

} SCUListHeader;

/** @brief The default capacity of a list. */
static constexpr isize SCU_DEFAULT_CAPACITY = 8;

/** @brief The growth factor for increasing the capacity of a list. */
static constexpr isize SCU_GROWTH_FACTOR = 2;

[[nodiscard]]
void* scu_list_new(isize elemSize) {
    return scu_list_new_with_capacity(elemSize, SCU_DEFAULT_CAPACITY);
}

[[nodiscard]]
void* scu_list_new_with_capacity(isize elemSize, isize capacity) {
    SCU_ASSERT(elemSize > 0);
    SCU_ASSERT(capacity >= 0);
    SCUListHeader* header = scu_malloc(
        SCU_SIZEOF(SCUListHeader) + (elemSize * capacity)
    );
    if (header == nullptr) {
        return nullptr;
    }
    header->elemSize = elemSize;
    header->capacity = capacity;
    header->count = 0;
    return header->data;
}

/**
 * @brief Returns a pointer to the header of a list given its data.
 *
 * @param[in] data A pointer to the actual data of the list.
 * @return A pointer to the header of the list.
 */
static inline SCUListHeader* scu_data_to_header(void* data) {
    SCU_ASSERT(data != nullptr);
    return (SCUListHeader*) ((byte*) data - SCU_SIZEOF(SCUListHeader));
}

/**
 * @brief Returns a pointer to the header of a list given its data.
 *
 * @param[in] data A pointer to the actual data of the list.
 * @return A pointer to the header of the list.
 */
static inline const SCUListHeader* scu_data_to_header_const(const void* data) {
    SCU_ASSERT(data != nullptr);
    return (const SCUListHeader*) (
        (const byte*) data - SCU_SIZEOF(SCUListHeader)
    );
}

[[nodiscard]]
void* scu_list_clone(const void* list) {
    const SCUListHeader* header = scu_data_to_header_const(list);
    SCUListHeader* newHeader = scu_malloc(
        SCU_SIZEOF(SCUListHeader) + (header->elemSize * header->capacity)
    );
    if (newHeader == nullptr) {
        return nullptr;
    }
    newHeader->elemSize = header->elemSize;
    newHeader->capacity = header->capacity;
    newHeader->count = header->count;
    scu_memcpy(newHeader->data, header->data, header->elemSize * header->count);
    return newHeader->data;
}

isize scu_list_capacity(const void* list) {
    const SCUListHeader* header = scu_data_to_header_const(list);
    return header->capacity;
}

isize scu_list_count(const void* list) {
    const SCUListHeader* header = scu_data_to_header_const(list);
    return header->count;
}

SCUError scu_list_ensure_capacity_impl(void** list, isize capacity) {
    SCU_ASSERT(list != nullptr);
    SCU_ASSERT(capacity >= 0);
    SCUListHeader* header = scu_data_to_header(*list);
    if (header->capacity < capacity) {
        isize newCapacity = (header->capacity > 0) ? header->capacity : 1;
        while (newCapacity < capacity) {
            newCapacity *= SCU_GROWTH_FACTOR;
        }
        SCUListHeader* newHeader = scu_realloc(
            header,
            SCU_SIZEOF(SCUListHeader) + (header->elemSize * newCapacity)
        );
        if (newHeader == nullptr) {
            return SCU_ERROR_OUT_OF_MEMORY;
        }
        newHeader->capacity = newCapacity;
        *list = newHeader->data;
    }
    return SCU_ERROR_NONE;
}

SCUError scu_list_add_impl(void** restrict list, const void* restrict elem) {
    SCU_ASSERT(list != nullptr);
    SCU_ASSERT(elem != nullptr);
    SCUListHeader* header = scu_data_to_header(*list);
    SCUError error = scu_list_ensure_capacity_impl(list, header->count + 1);
    if (error != SCU_ERROR_NONE) {
        return error;
    }
    // Get the header again, as the list may have been reallocated.
    header = scu_data_to_header(*list);
    scu_memcpy(
        header->data + (header->elemSize * header->count),
        elem,
        header->elemSize
    );
    header->count++;
    return SCU_ERROR_NONE;
}

SCUError scu_list_insert_at_impl(
    void** restrict list,
    isize index,
    const void* restrict elem
) {
    SCU_ASSERT(list != nullptr);
    SCUListHeader* header = scu_data_to_header(*list);
    SCU_ASSERT((index >= 0) && (index <= header->count));
    SCU_ASSERT(elem != nullptr);
    SCUError error = scu_list_ensure_capacity_impl(list, header->count + 1);
    if (error != SCU_ERROR_NONE) {
        return error;
    }
    // Get the header again, as the list may have been reallocated.
    header = scu_data_to_header(*list);
    scu_memmove(
        header->data + (header->elemSize * (index + 1)),
        header->data + (header->elemSize * index),
        header->elemSize * (header->count - index)
    );
    scu_memcpy(
        header->data + (header->elemSize * index),
        elem,
        header->elemSize
    );
    header->count++;
    return SCU_ERROR_NONE;
}

void scu_list_remove_at(void* list, isize index) {
    SCUListHeader* header = scu_data_to_header(list);
    SCU_ASSERT((index >= 0) && (index < header->count));
    scu_memmove(
        header->data + (header->elemSize * index),
        header->data + (header->elemSize * (index + 1)),
        header->elemSize * (header->count - index - 1)
    );
    header->count--;
}

void scu_list_clear(void* list) {
    SCUListHeader* header = scu_data_to_header(list);
    header->count = 0;
}

SCUError scu_list_trim_excess_impl(void** list) {
    SCU_ASSERT(list != nullptr);
    SCUListHeader* header = scu_data_to_header(*list);
    if (header->capacity > header->count) {
        SCUListHeader* newHeader = scu_realloc(
            header,
            SCU_SIZEOF(SCUListHeader) + (header->elemSize * header->count)
        );
        if (newHeader == nullptr) {
            return SCU_ERROR_OUT_OF_MEMORY;
        }
        newHeader->capacity = header->count;
        *list = newHeader->data;
    }
    return SCU_ERROR_NONE;
}

void scu_list_sort(void* list, SCUCompareFunc* cmpFunc) {
    SCU_ASSERT(cmpFunc != nullptr);
    SCUListHeader* header = scu_data_to_header(list);
    scu_array_sort(header->data, header->count, header->elemSize, cmpFunc);
}

void scu_list_free(void* list) {
    if (list != nullptr) {
        SCUListHeader* header = scu_data_to_header(list);
        header->capacity = 0;
        header->count = 0;
        scu_free(header);
    }
}