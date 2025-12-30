#include "scu/assert.h"
#include "scu/hash.h"

uint64_t scu_hash_int8(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t hash = (uint8_t) *(const int8_t*) value;
    return hash * UINT64_C(0x9E3779B97F4A7C15);
}

uint64_t scu_hash_uint8(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t hash = *(const uint8_t*) value;
    return hash * UINT64_C(0x9E3779B97F4A7C15);
}

uint64_t scu_hash_int16(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t hash = (uint16_t) *(const int16_t*) value;
    return hash * UINT64_C(0x9E3779B97F4A7C15);
}

uint64_t scu_hash_uint16(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t hash = *(const uint16_t*) value;
    return hash * UINT64_C(0x9E3779B97F4A7C15);
}

uint64_t scu_hash_int32(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t hash = (uint32_t) *(const int32_t*) value;
    hash ^= hash >> 16;
    hash *= UINT64_C(0x85EBCA6B);
    hash ^= hash >> 13;
    hash *= UINT64_C(0xC2B2AE35);
    hash ^= hash >> 16;
    return hash;
}

uint64_t scu_hash_uint32(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t hash = *(const uint32_t*) value;
    hash ^= hash >> 16;
    hash *= UINT64_C(0x85EBCA6B);
    hash ^= hash >> 13;
    hash *= UINT64_C(0xC2B2AE35);
    hash ^= hash >> 16;
    return hash;
}

uint64_t scu_hash_int64(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t hash = (uint64_t) *(const int64_t*) value;
    hash ^= hash >> 30;
    hash *= UINT64_C(0xBF58476D1CE4E5B9);
    hash ^= hash >> 27;
    hash *= UINT64_C(0x94D049BB133111EB);
    hash ^= hash >> 31;
    return hash;
}

uint64_t scu_hash_uint64(const void* value) {
    SCU_ASSERT(value != nullptr);
    uint64_t hash = *(const uint64_t*) value;
    hash ^= hash >> 30;
    hash *= UINT64_C(0xBF58476D1CE4E5B9);
    hash ^= hash >> 27;
    hash *= UINT64_C(0x94D049BB133111EB);
    hash ^= hash >> 31;
    return hash;
}

uint64_t scu_hash_str(const void* value) {
    SCU_ASSERT(value != nullptr);
    const unsigned char* s = *(const unsigned char* const*) value;
    uint64_t hash = UINT64_C(0xCBF29CE484222325);
    for (int64_t i = 0; s[i] != '\0'; i++) {
        hash ^= s[i];
        hash *= UINT64_C(0x00000100000001B3);
    }
    return hash;
}

uint64_t scu_hash_combine(uint64_t seed, uint64_t hash) {
    return seed ^ (hash + UINT64_C(0x9E3779B97F4A7C15) + (seed << 6)
        + (seed >> 2));
}