#ifndef SCU_EQUAL_H
#define SCU_EQUAL_H

/**
 * @brief Determines whether two specified values are equal.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
typedef bool SCUEqualFunc(const void* a, const void* b);

/**
 * @brief Determines whether two specified `bool` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `bool`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_bool(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUbyte` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUbyte`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_byte(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUi8` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUi8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_i8(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUu8` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUu8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_u8(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUi16` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUi16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_i16(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUu16` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUu16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_u16(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUi32` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUi32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_i32(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUu32` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUu32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_u32(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUi64` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUi64`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_i64(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUu64` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUu64`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_u64(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUiptr` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUiptr`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_iptr(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUuptr` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUuptr`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_uptr(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUisize` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUisize`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_isize(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUusize` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUusize`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_usize(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUf32` values are equal.
 *
 * @note This function considers two `SCUf32` values equal if they are exactly
 * equal according to the `==` operator. It is intended for use in collections
 * that require an equality function, but not as a general-purpose (approximate)
 * floating-point comparison function.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUf32`, or if either `*a` or `*b` is NaN.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_f32(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUf64` values are equal.
 *
 * @note This function considers two `SCUf64` values equal if they are exactly
 * equal according to the `==` operator. It is intended for use in collections
 * that require an equality function, but not as a general-purpose (approximate)
 * floating-point comparison function.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUf64`, or if either `*a` or `*b` is NaN.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_f64(const void* a, const void* b);

/**
 * @brief Determines whether two specified `char` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `char`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_char(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUchar8` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUchar8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_char8(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUchar16` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUchar16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_char16(const void* a, const void* b);

/**
 * @brief Determines whether two specified `SCUchar32` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `SCUchar32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_char32(const void* a, const void* b);

/**
 * @brief Determines whether two specified null-terminated byte strings are
 * equal.
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
 * @return `true` if the null-terminated byte strings pointed to by `*a` and
 * `*b` are equal, otherwise `false`.
 */
bool scu_equal_str(const void* a, const void* b);

#endif