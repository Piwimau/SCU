#include "scu/assert.h"
#include "scu/equal.h"

bool scu_equal_int8(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const int8_t*) a == *(const int8_t*) b;
}

bool scu_equal_uint8(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const uint8_t*) a == *(const uint8_t*) b;
}

bool scu_equal_int16(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const int16_t*) a == *(const int16_t*) b;
}

bool scu_equal_uint16(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const uint16_t*) a == *(const uint16_t*) b;
}

bool scu_equal_int32(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const int32_t*) a == *(const int32_t*) b;
}

bool scu_equal_uint32(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const uint32_t*) a == *(const uint32_t*) b;
}

bool scu_equal_int64(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const int64_t*) a == *(const int64_t*) b;
}

bool scu_equal_uint64(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const uint64_t*) a == *(const uint64_t*) b;
}