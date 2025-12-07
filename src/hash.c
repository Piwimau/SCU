#include "scu/assert.h"
#include "scu/hash.h"

uint64_t scu_hash_int8(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t v = (uint8_t) *(const int8_t*) value;
    return v * UINT64_C(0x9E3779B97F4A7C15);
}

uint64_t scu_hash_uint8(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t v = *(const uint8_t*) value;
    return v * UINT64_C(0x9E3779B97F4A7C15);
}

uint64_t scu_hash_int16(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t v = (uint16_t) *(const int16_t*) value;
    return v * UINT64_C(0x9E3779B97F4A7C15);
}

uint64_t scu_hash_uint16(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t v = *(const uint16_t*) value;
    return v * UINT64_C(0x9E3779B97F4A7C15);
}

uint64_t scu_hash_int32(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t v = (uint32_t) *(const int32_t*) value;
    v ^= v >> 16;
    v *= UINT64_C(0x85EBCA6B);
    v ^= v >> 13;
    v *= UINT64_C(0xC2B2AE35);
    v ^= v >> 16;
    return v;
}

uint64_t scu_hash_uint32(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t v = *(const uint32_t*) value;
    v ^= v >> 16;
    v *= UINT64_C(0x85EBCA6B);
    v ^= v >> 13;
    v *= UINT64_C(0xC2B2AE35);
    v ^= v >> 16;
    return v;
}

uint64_t scu_hash_int64(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t v = (uint64_t) *(const int64_t*) value;
    v ^= v >> 30;
    v *= UINT64_C(0xBF58476D1CE4E5B9);
    v ^= v >> 27;
    v *= UINT64_C(0x94D049BB133111EB);
    v ^= v >> 31;
    return v;
}

uint64_t scu_hash_uint64(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t v = *(const uint64_t*) value;
    v ^= v >> 30;
    v *= UINT64_C(0xBF58476D1CE4E5B9);
    v ^= v >> 27;
    v *= UINT64_C(0x94D049BB133111EB);
    v ^= v >> 31;
    return v;
}