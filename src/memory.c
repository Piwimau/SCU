#include <string.h>
#include "scu/assert.h"
#include "scu/memory.h"

void* scu_memchr(const void* block, unsigned char c, int64_t count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return nullptr;
    }
    SCU_ASSERT(block != nullptr);
    return memchr(block, c, (size_t) count);
}

void* scu_memrchr(const void* block, unsigned char c, int64_t count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return nullptr;
    }
    SCU_ASSERT(block != nullptr);
    const unsigned char* p = (const unsigned char*) block;
    void* last = nullptr;
    void* match = nullptr;
    while ((count > 0) && ((match = memchr(p, c, (size_t) count)) != nullptr)) {
        last = match;
        int64_t offset = (unsigned char*) match - p + 1;
        p += offset;
        count -= offset;
    }
    return last;
}

int scu_memcmp(const void* left, const void* right, int64_t count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return 0;
    }
    SCU_ASSERT(left != nullptr);
    SCU_ASSERT(right != nullptr);
    int cmp = memcmp(left, right, (size_t) count);
    return (cmp < 0) ? -1 : (cmp > 0) ? 1 : 0;
}

void* scu_memset(void* dest, unsigned char c, int64_t count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return dest;
    }
    SCU_ASSERT(dest != nullptr);
    return memset(dest, c, (size_t) count);
}

void* scu_memcpy(void* restrict dest, const void* restrict src, int64_t count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return dest;
    }
    SCU_ASSERT(dest != nullptr);
    SCU_ASSERT(src != nullptr);
    return memcpy(dest, src, (size_t) count);
}

void* scu_memccpy(
    void* restrict dest,
    const void* restrict src,
    unsigned char c,
    int64_t count
) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return nullptr;
    }
    SCU_ASSERT(dest != nullptr);
    SCU_ASSERT(src != nullptr);
    return memccpy(dest, src, c, (size_t) count);
}

void* scu_mempcpy(
    void* restrict dest,
    const void* restrict src,
    int64_t count
) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return dest;
    }
    SCU_ASSERT(dest != nullptr);
    SCU_ASSERT(src != nullptr);
    return (unsigned char*) memcpy(dest, src, (size_t) count) + count;
}

void* scu_memmove(void* dest, const void* src, int64_t count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return dest;
    }
    SCU_ASSERT(dest != nullptr);
    SCU_ASSERT(src != nullptr);
    return memmove(dest, src, (size_t) count);
}

void scu_memswap(void* restrict left, void* restrict right, int64_t count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return;
    }
    SCU_ASSERT(left != nullptr);
    SCU_ASSERT(right != nullptr);
    unsigned char* l = (unsigned char*) left;
    unsigned char* r = (unsigned char*) right;
    for (int64_t i = 0; i < count; i++) {
        unsigned char temp = l[i];
        l[i] = r[i];
        r[i] = temp;
    }
}