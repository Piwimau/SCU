#include <limits.h>
#include <string.h>
#include "scu/alloc.h"
#include "scu/assert.h"
#include "scu/common.h"
#include "scu/math.h"
#include "scu/memory.h"
#include "scu/string.h"

int64_t scu_strlen(const char* s) {
    SCU_ASSERT(s != nullptr);
    return (int64_t) strlen(s);
}

int64_t scu_strnlen(const char* s, int64_t count) {
    const char* p = scu_memchr(s, '\0', count);
    return (p == nullptr) ? count : (p - s);
}

int32_t scu_strcmp(const char* left, const char* right) {
    SCU_ASSERT(left != nullptr);
    SCU_ASSERT(right != nullptr);
    int r = strcmp(left, right);
    return (r > 0) - (r < 0);
}

int32_t scu_strncmp(const char* left, const char* right, int64_t count) {
    SCU_ASSERT(count >= 0);
    if (count == 0) {
        return 0;
    }
    SCU_ASSERT(left != nullptr);
    SCU_ASSERT(right != nullptr);
    int r = strncmp(left, right, (size_t) count);
    return (r > 0) - (r < 0);
}

int64_t scu_str_index_of_byte(const char* s, char c) {
    SCU_ASSERT(s != nullptr);
    if (c == '\0') {
        return -1;
    }
    const char* p = strchr(s, c);
    return (p == nullptr) ? -1 : (p - s);
}

int64_t scu_str_index_of_str(const char* s, const char* other) {
    SCU_ASSERT(s != nullptr);
    SCU_ASSERT(other != nullptr);
    const char* p = strstr(s, other);
    return (p == nullptr) ? -1 : (p - s);
}

int64_t scu_str_last_index_of_byte(const char* s, char c) {
    SCU_ASSERT(s != nullptr);
    if (c == '\0') {
        return -1;
    }
    const char* p = strrchr(s, c);
    return (p == nullptr) ? -1 : (p - s);
}

int64_t scu_str_last_index_of_str(const char* s, const char* other) {
    SCU_ASSERT(s != nullptr);
    SCU_ASSERT(other != nullptr);
    if (other[0] == '\0') {
        return (int64_t) strlen(s);
    }
    const char* last = nullptr;
    const char* p = s;
    while ((p = strstr(p, other)) != nullptr) {
        last = p;
        p++;
    }
    return (last == nullptr) ? -1 : (last - s);
}

int64_t scu_str_index_of_any(const char* s, const char* anyOf) {
    SCU_ASSERT(s != nullptr);
    SCU_ASSERT(anyOf != nullptr);
    if (anyOf[0] == '\0') {
        return -1;
    }
    const char* p = strpbrk(s, anyOf);
    return (p == nullptr) ? -1 : (p - s);
}

int64_t scu_str_last_index_of_any(const char* s, const char* anyOf) {
    SCU_ASSERT(s != nullptr);
    SCU_ASSERT(anyOf != nullptr);
    if (anyOf[0] == '\0') {
        return -1;
    }
    const char* last = nullptr;
    const char* p = s;
    while ((p = strpbrk(p, anyOf)) != nullptr) {
        last = p;
        p++;
    }
    return (last == nullptr) ? -1 : (last - s);
}

int64_t scu_str_index_in_range(
    const char* s,
    char lowInclusive,
    char highInclusive
) {
    SCU_ASSERT(s != nullptr);
    unsigned char low = (unsigned char) lowInclusive;
    unsigned char high = (unsigned char) highInclusive;
    SCU_ASSERT(high >= low);
    for (int64_t i = 0; s[i] != '\0'; i++) {
        unsigned char c = (unsigned char) s[i];
        if ((c >= low) && (c <= high)) {
            return i;
        }
    }
    return -1;
}

int64_t scu_str_last_index_in_range(
    const char* s,
    char lowInclusive,
    char highInclusive
) {
    SCU_ASSERT(s != nullptr);
    unsigned char low = (unsigned char) lowInclusive;
    unsigned char high = (unsigned char) highInclusive;
    SCU_ASSERT(high >= low);
    int64_t last = -1;
    for (int64_t i = 0; s[i] != '\0'; i++) {
        unsigned char c = (unsigned char) s[i];
        if ((c >= low) && (c <= high)) {
            last = i;
        }
    }
    return last;
}

bool scu_str_starts_with_byte(const char* s, char c) {
    SCU_ASSERT(s != nullptr);
    return (s[0] != '\0') && (s[0] == c);
}

bool scu_str_starts_with_str(const char* s, const char* prefix) {
    SCU_ASSERT(s != nullptr);
    SCU_ASSERT(prefix != nullptr);
    int64_t i = 0;
    while ((prefix[i] != '\0') && (s[i] == prefix[i])) {
        i++;
    }
    return prefix[i] == '\0';
}

bool scu_str_ends_with_byte(const char* s, char c) {
    SCU_ASSERT(s != nullptr);
    int64_t length = scu_strlen(s);
    return (length > 0) && (s[length - 1] == c);
}

bool scu_str_ends_with_str(const char* s, const char* suffix) {
    SCU_ASSERT(s != nullptr);
    SCU_ASSERT(suffix != nullptr);
    int64_t suffixLength = scu_strlen(suffix);
    if (suffixLength == 0) {
        return true;
    }
    int64_t length = scu_strlen(s);
    if (suffixLength > length) {
        return false;
    }
    return scu_strncmp(s + (length - suffixLength), suffix, suffixLength) == 0;
}

[[nodiscard]]
char* scu_strdup(const char* src) {
    int64_t length = scu_strlen(src);
    int64_t size = (length + 1) * SCU_SIZEOF(char);
    char* dest = scu_malloc(size);
    if (dest != nullptr) {
        scu_memcpy(dest, src, length * SCU_SIZEOF(char));
        dest[length] = '\0';
    }
    return dest;
}

[[nodiscard]]
char* scu_strndup(const char* src, int64_t count) {
    const char* p = scu_memchr(src, '\0', count);
    int64_t length = (p == nullptr) ? count : (p - src);
    int64_t size = (length + 1) * SCU_SIZEOF(char);
    char* dest = scu_malloc(size);
    if (dest != nullptr) {
        scu_memcpy(dest, src, length * SCU_SIZEOF(char));
        dest[length] = '\0';
    }
    return dest;
}

int64_t scu_strncpy(
    char* restrict dest,
    int64_t size,
    const char* restrict src,
    int64_t count
) {
    SCU_ASSERT(size >= 0);
    SCU_ASSERT(count >= 0);
    if (size == 0) {
        return 0;
    }
    SCU_ASSERT(dest != nullptr);
    if (count == 0) {
        dest[0] = '\0';
        return 0;
    }
    SCU_ASSERT(src != nullptr);
    int64_t n = SCU_MIN(size - 1, count);
    char* p = scu_memccpy(dest, src, '\0', n);
    if (p == nullptr) {
        dest[n] = '\0';
        return n;
    }
    return p - dest - 1;
}

int64_t scu_strncat(
    char* restrict dest,
    int64_t size,
    const char* restrict src,
    int64_t count
) {
    SCU_ASSERT(size >= 0);
    SCU_ASSERT(count >= 0);
    if ((size == 0) || (count == 0)) {
        return 0;
    }
    SCU_ASSERT(dest != nullptr);
    SCU_ASSERT(src != nullptr);
    int64_t length = scu_strlen(dest);
    SCU_ASSERT(length < size);
    int64_t n = SCU_MIN(size - length - 1, count);
    if (n == 0) {
        return 0;
    }
    char* p = scu_memccpy(dest + length, src, '\0', n);
    if (p == nullptr) {
        dest[length + n] = '\0';
        return n;
    }
    return p - (dest + length) - 1;
}