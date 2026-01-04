#define SCU_SHORT_ALIASES

#include <string.h>
#include "scu/assert.h"
#include "scu/memory.h"

void* scu_memchr(const void* block, byte c, isize count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return nullptr;
    }
    SCU_ASSERT(block != nullptr);
    return memchr(block, c, (usize) count);
}

void* scu_memrchr(const void* block, byte c, isize count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return nullptr;
    }
    SCU_ASSERT(block != nullptr);
    const byte* p = (const byte*) block;
    for (isize i = count - 1; i >= 0; i--) {
        if (p[i] == c) {
            return (void*) (p + i);
        }
    }
    return nullptr;
}

int scu_memcmp(const void* left, const void* right, isize count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return 0;
    }
    SCU_ASSERT(left != nullptr);
    SCU_ASSERT(right != nullptr);
    int cmp = memcmp(left, right, (usize) count);
    return (cmp < 0) ? -1 : (cmp > 0) ? 1 : 0;
}

void* scu_memset(void* dest, byte c, isize count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return dest;
    }
    SCU_ASSERT(dest != nullptr);
    return memset(dest, c, (usize) count);
}

void* scu_memcpy(void* restrict dest, const void* restrict src, isize count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return dest;
    }
    SCU_ASSERT(dest != nullptr);
    SCU_ASSERT(src != nullptr);
    return memcpy(dest, src, (usize) count);
}

void* scu_memccpy(
    void* restrict dest,
    const void* restrict src,
    byte c,
    isize count
) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return nullptr;
    }
    SCU_ASSERT(dest != nullptr);
    SCU_ASSERT(src != nullptr);
    return memccpy(dest, src, c, (usize) count);
}

void* scu_mempcpy(void* restrict dest, const void* restrict src, isize count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return dest;
    }
    SCU_ASSERT(dest != nullptr);
    SCU_ASSERT(src != nullptr);
    return (byte*) memcpy(dest, src, (usize) count) + count;
}

void* scu_memmove(void* dest, const void* src, isize count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return dest;
    }
    SCU_ASSERT(dest != nullptr);
    SCU_ASSERT(src != nullptr);
    return memmove(dest, src, (usize) count);
}

void scu_memswap(void* restrict left, void* restrict right, isize count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return;
    }
    SCU_ASSERT(left != nullptr);
    SCU_ASSERT(right != nullptr);
    byte* l = (byte*) left;
    byte* r = (byte*) right;
    for (isize i = 0; i < count; i++) {
        byte temp = l[i];
        l[i] = r[i];
        r[i] = temp;
    }
}