#include <string.h>
#include "scu/assert.h"
#include "scu/compare.h"

int scu_compare_int8(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    int8_t l = *(const int8_t*) a;
    int8_t r = *(const int8_t*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_int8_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    int8_t l = *(const int8_t*) a;
    int8_t r = *(const int8_t*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_uint8(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    uint8_t l = *(const uint8_t*) a;
    uint8_t r = *(const uint8_t*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_uint8_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    uint8_t l = *(const uint8_t*) a;
    uint8_t r = *(const uint8_t*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_int16(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    int16_t l = *(const int16_t*) a;
    int16_t r = *(const int16_t*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_int16_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    int16_t l = *(const int16_t*) a;
    int16_t r = *(const int16_t*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_uint16(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    uint16_t l = *(const uint16_t*) a;
    uint16_t r = *(const uint16_t*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_uint16_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    uint16_t l = *(const uint16_t*) a;
    uint16_t r = *(const uint16_t*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_int32(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    int32_t l = *(const int32_t*) a;
    int32_t r = *(const int32_t*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_int32_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    int32_t l = *(const int32_t*) a;
    int32_t r = *(const int32_t*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_uint32(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    uint32_t l = *(const uint32_t*) a;
    uint32_t r = *(const uint32_t*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_uint32_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    uint32_t l = *(const uint32_t*) a;
    uint32_t r = *(const uint32_t*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_int64(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    int64_t l = *(const int64_t*) a;
    int64_t r = *(const int64_t*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_int64_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    int64_t l = *(const int64_t*) a;
    int64_t r = *(const int64_t*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_uint64(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    uint64_t l = *(const uint64_t*) a;
    uint64_t r = *(const uint64_t*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_uint64_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    uint64_t l = *(const uint64_t*) a;
    uint64_t r = *(const uint64_t*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_str(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    const char* l = *(const char* const*) a;
    const char* r = *(const char* const*) b;
    int cmp = strcmp(l, r);
    return (cmp < 0) ? -1 : (cmp > 0) ? 1 : 0;
}

int scu_compare_str_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    const char* l = *(const char* const*) a;
    const char* r = *(const char* const*) b;
    int cmp = strcmp(l, r);
    return (cmp > 0) ? -1 : (cmp < 0) ? 1 : 0;
}