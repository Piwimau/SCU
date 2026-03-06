#define SCU_SHORT_ALIASES

#include <math.h>
#include <string.h>
#include "scu/assert.h"
#include "scu/equal.h"
#include "scu/types.h"

bool scu_equal_bool(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const bool*) a == *(const bool*) b;
}

bool scu_equal_byte(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const byte*) a == *(const byte*) b;
}

bool scu_equal_i8(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const i8*) a == *(const i8*) b;
}

bool scu_equal_u8(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const u8*) a == *(const u8*) b;
}

bool scu_equal_i16(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const i16*) a == *(const i16*) b;
}

bool scu_equal_u16(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const u16*) a == *(const u16*) b;
}

bool scu_equal_i32(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const i32*) a == *(const i32*) b;
}

bool scu_equal_u32(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const u32*) a == *(const u32*) b;
}

bool scu_equal_i64(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const i64*) a == *(const i64*) b;
}

bool scu_equal_u64(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const u64*) a == *(const u64*) b;
}

bool scu_equal_iptr(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const iptr*) a == *(const iptr*) b;
}

bool scu_equal_uptr(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const uptr*) a == *(const uptr*) b;
}

bool scu_equal_isize(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const isize*) a == *(const isize*) b;
}

bool scu_equal_usize(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const usize*) a == *(const usize*) b;
}

bool scu_equal_f32(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    f32 l = *(const f32*) a;
    f32 r = *(const f32*) b;
    SCU_ASSERT(!isnan(l));
    SCU_ASSERT(!isnan(r));
    return l == r;
}

bool scu_equal_f64(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    f64 l = *(const f64*) a;
    f64 r = *(const f64*) b;
    SCU_ASSERT(!isnan(l));
    SCU_ASSERT(!isnan(r));
    return l == r;
}

bool scu_equal_char(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const char*) a == *(const char*) b;
}

bool scu_equal_char8(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const char8*) a == *(const char8*) b;
}

bool scu_equal_char16(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const char16*) a == *(const char16*) b;
}

bool scu_equal_char32(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    return *(const char32*) a == *(const char32*) b;
}

bool scu_equal_str(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    const char* l = *(const char* const*) a;
    const char* r = *(const char* const*) b;
    return strcmp(l, r) == 0;
}