#ifndef SCU_EQUAL_H
#define SCU_EQUAL_H

/**
 * @brief Determines whether two specified values are equal.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
typedef bool ScuEqualFunc(const void* a, const void* b);

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
 * @brief Determines whether two specified `Scubyte` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scubyte`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_byte(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scui8` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scui8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_i8(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scuu8` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuu8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_u8(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scui16` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scui16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_i16(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scuu16` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuu16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_u16(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scui32` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scui32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_i32(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scuu32` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuu32`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_u32(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scui64` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scui64`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_i64(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scuu64` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuu64`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_u64(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scuiptr` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuiptr`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_iptr(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scuuptr` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuuptr`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_uptr(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scuisize` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuisize`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_isize(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scuusize` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuusize`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_usize(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scuf32` values are equal.
 *
 * @note This function considers two `Scuf32` values equal if they are exactly
 * equal according to the `==` operator. It is intended for use in collections
 * that require an equality function, but not as a general-purpose (approximate)
 * floating-point comparison function.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuf32`, or if either `*a` or `*b` is NaN.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_f32(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scuf64` values are equal.
 *
 * @note This function considers two `Scuf64` values equal if they are exactly
 * equal according to the `==` operator. It is intended for use in collections
 * that require an equality function, but not as a general-purpose (approximate)
 * floating-point comparison function.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuf64`, or if either `*a` or `*b` is NaN.
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
 * @brief Determines whether two specified `Scuchar8` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuchar8`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_char8(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scuchar16` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuchar16`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_char16(const void* a, const void* b);

/**
 * @brief Determines whether two specified `Scuchar32` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `Scuchar32`.
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