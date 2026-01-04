#define SCU_SHORT_ALIASES

#include <string.h>
#include "scu/assert.h"
#include "scu/compare.h"
#include "scu/types.h"

int scu_compare_byte(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    byte l = *(const byte*) a;
    byte r = *(const byte*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_byte_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    byte l = *(const byte*) a;
    byte r = *(const byte*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_i8(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    i8 l = *(const i8*) a;
    i8 r = *(const i8*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_i8_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    i8 l = *(const i8*) a;
    i8 r = *(const i8*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_u8(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    u8 l = *(const u8*) a;
    u8 r = *(const u8*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_u8_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    u8 l = *(const u8*) a;
    u8 r = *(const u8*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_i16(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    i16 l = *(const i16*) a;
    i16 r = *(const i16*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_i16_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    i16 l = *(const i16*) a;
    i16 r = *(const i16*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_u16(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    u16 l = *(const u16*) a;
    u16 r = *(const u16*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_u16_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    u16 l = *(const u16*) a;
    u16 r = *(const u16*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_i32(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    i32 l = *(const i32*) a;
    i32 r = *(const i32*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_i32_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    i32 l = *(const i32*) a;
    i32 r = *(const i32*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_u32(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    u32 l = *(const u32*) a;
    u32 r = *(const u32*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_u32_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    u32 l = *(const u32*) a;
    u32 r = *(const u32*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_i64(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    i64 l = *(const i64*) a;
    i64 r = *(const i64*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_i64_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    i64 l = *(const i64*) a;
    i64 r = *(const i64*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_u64(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    u64 l = *(const u64*) a;
    u64 r = *(const u64*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_u64_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    u64 l = *(const u64*) a;
    u64 r = *(const u64*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_iptr(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    iptr l = *(const iptr*) a;
    iptr r = *(const iptr*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_iptr_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    iptr l = *(const iptr*) a;
    iptr r = *(const iptr*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_uptr(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    uptr l = *(const uptr*) a;
    uptr r = *(const uptr*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_uptr_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    uptr l = *(const uptr*) a;
    uptr r = *(const uptr*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_isize(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    isize l = *(const isize*) a;
    isize r = *(const isize*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_isize_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    isize l = *(const isize*) a;
    isize r = *(const isize*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_usize(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    usize l = *(const usize*) a;
    usize r = *(const usize*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_usize_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    usize l = *(const usize*) a;
    usize r = *(const usize*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_f32(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    f32 l = *(const f32*) a;
    f32 r = *(const f32*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_f32_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    f32 l = *(const f32*) a;
    f32 r = *(const f32*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_f64(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    f64 l = *(const f64*) a;
    f64 r = *(const f64*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_f64_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    f64 l = *(const f64*) a;
    f64 r = *(const f64*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_char(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    char l = *(const char*) a;
    char r = *(const char*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_char_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    char l = *(const char*) a;
    char r = *(const char*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_char8(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    char8 l = *(const char8*) a;
    char8 r = *(const char8*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_char8_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    char8 l = *(const char8*) a;
    char8 r = *(const char8*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_char16(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    char16 l = *(const char16*) a;
    char16 r = *(const char16*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_char16_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    char16 l = *(const char16*) a;
    char16 r = *(const char16*) b;
    return (l > r) ? -1 : (l < r) ? 1 : 0;
}

int scu_compare_char32(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    char32 l = *(const char32*) a;
    char32 r = *(const char32*) b;
    return (l < r) ? -1 : (l > r) ? 1 : 0;
}

int scu_compare_char32_rev(const void* a, const void* b) {
    SCU_ASSERT(a != nullptr);
    SCU_ASSERT(b != nullptr);
    char32 l = *(const char32*) a;
    char32 r = *(const char32*) b;
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