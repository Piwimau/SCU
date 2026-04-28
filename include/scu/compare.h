#ifndef SCU_COMPARE_H
#define SCU_COMPARE_H

/**
 * @brief Compares two specified values.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
typedef int ScuCompareFunc(const void* a, const void* b);

/**
 * @brief Compares two specified `bool` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `bool`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is `false` and `*b` is `true`, zero if they
 * compare equal, or a positive value if `*a` is `true` and `*b` is `false`.
 */
int scu_compare_bool(const void* a, const void* b);

/**
 * @brief Compares two specified `bool` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `bool`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is `true` and `*b` is `false`, zero if they
 * compare equal, or a positive value if `*a` is `false` and `*b` is `true`.
 */
int scu_compare_bool_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scubyte` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scubyte`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_byte(const void* a, const void* b);

/**
 * @brief Compares two specified `Scubyte` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scubyte`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_byte_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scui8` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scui8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_i8(const void* a, const void* b);

/**
 * @brief Compares two specified `Scui8` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scui8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_i8_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuu8` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuu8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_u8(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuu8` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuu8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_u8_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scui16` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scui16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_i16(const void* a, const void* b);

/**
 * @brief Compares two specified `Scui16` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scui16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_i16_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuu16` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuu16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_u16(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuu16` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuu16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_u16_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scui32` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scui32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_i32(const void* a, const void* b);

/**
 * @brief Compares two specified `Scui32` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scui32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_i32_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuu32` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuu32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_u32(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuu32` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuu32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_u32_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scui64` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scui64`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_i64(const void* a, const void* b);

/**
 * @brief Compares two specified `Scui64` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scui64`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_i64_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuu64` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuu64`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_u64(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuu64` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuu64`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_u64_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuiptr` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuiptr`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_iptr(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuiptr` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuiptr`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_iptr_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuuptr` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuuptr`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_uptr(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuuptr` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuuptr`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_uptr_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuisize` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuisize`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_isize(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuisize` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuisize`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_isize_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuusize` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuusize`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_usize(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuusize` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuusize`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_usize_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuf32` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuf32`, or if either `*a` or `*b` is NaN.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_f32(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuf32` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuf32`, or if either `*a` or `*b` is NaN.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_f32_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuf64` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuf64`, or if either `*a` or `*b` is NaN.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_f64(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuf64` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuf64`, or if either `*a` or `*b` is NaN.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_f64_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `char` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `char`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_char(const void* a, const void* b);

/**
 * @brief Compares two specified `char` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `char`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_char_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuchar8` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuchar8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_char8(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuchar8` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuchar8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_char8_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuchar16` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuchar16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_char16(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuchar16` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuchar16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_char16_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuchar32` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuchar32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_char32(const void* a, const void* b);

/**
 * @brief Compares two specified `Scuchar32` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuchar32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_char32_rev(const void* a, const void* b);

/**
 * @brief Compares two specified null-terminated byte strings lexicographically.
 *
 * @note This function compares the strings solely based on their byte
 * representation. For strings that use a multi-byte character encoding (e.g.,
 * UTF-8), the return value may be misleading, for example if certain characters
 * considered equal can be represented by different byte sequences.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * pointer to a null-terminated byte string. Note that `a` and `b` must not be
 * direct pointers to the strings themselves, but pointers to pointers (i.e.,
 * `a` and `b` are interpreted as `const char* const*`).
 *
 * @param[in] a A pointer to a pointer to the first null-terminated byte string.
 * @param[in] b A pointer to a pointer to the second null-terminated byte
 *              string.
 * @return A negative value if `*a` appears before `*b` in lexicographical
 * order, zero if they compare equal, or a positive value if `*a` appears after
 * `*b`.
 */
int scu_compare_str(const void* a, const void* b);

/**
 * @brief Compares two specified null-terminated byte strings lexicographically
 * in reverse order.
 *
 * @note This function compares the strings solely based on their byte
 * representation. For strings that use a multi-byte character encoding (e.g.,
 * UTF-8), the return value may be misleading, for example if certain characters
 * considered equal can be represented by different byte sequences.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * pointer to a null-terminated byte string. Note that `a` and `b` must not be
 * direct pointers to the strings themselves, but pointers to pointers (i.e.,
 * `a` and `b` are interpreted as `const char* const*`).
 *
 * @param[in] a A pointer to a pointer to the first null-terminated byte string.
 * @param[in] b A pointer to a pointer to the second null-terminated byte
 *              string.
 * @return A negative value if `*a` appears after `*b` in lexicographical order,
 * zero if they compare equal, or a positive value if `*a` appears before `*b`.
 */
int scu_compare_str_rev(const void* a, const void* b);

#endif