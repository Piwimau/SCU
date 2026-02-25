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
typedef int SCUCompareFunc(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUbyte` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUbyte`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_byte(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUbyte` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUbyte`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_byte_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUi8` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUi8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_i8(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUi8` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUi8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_i8_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUu8` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUu8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_u8(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUu8` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUu8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_u8_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUi16` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUi16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_i16(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUi16` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUi16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_i16_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUu16` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUu16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_u16(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUu16` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUu16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_u16_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUi32` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUi32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_i32(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUi32` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUi32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_i32_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUu32` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUu32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_u32(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUu32` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUu32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_u32_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUi64` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUi64`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_i64(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUi64` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUi64`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_i64_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUu64` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUu64`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_u64(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUu64` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUu64`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_u64_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUiptr` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUiptr`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_iptr(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUiptr` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUiptr`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_iptr_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUuptr` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUuptr`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_uptr(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUuptr` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUuptr`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_uptr_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUisize` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUisize`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_isize(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUisize` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUisize`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_isize_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUusize` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUusize`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_usize(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUusize` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUusize`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_usize_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUf32` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUf32`, or if either `*a` or `*b` is NaN.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_f32(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUf32` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUf32`, or if either `*a` or `*b` is NaN.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_f32_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUf64` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUf64`, or if either `*a` or `*b` is NaN.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_f64(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUf64` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUf64`, or if either `*a` or `*b` is NaN.
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
 * @brief Compares two specified `SCUchar8` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUchar8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_char8(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUchar8` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUchar8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_char8_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUchar16` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUchar16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_char16(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUchar16` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUchar16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they compare
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_char16_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUchar32` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUchar32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they compare
 * equal, or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_char32(const void* a, const void* b);

/**
 * @brief Compares two specified `SCUchar32` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUchar32`.
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