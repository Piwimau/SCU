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
 * @brief Determines whether two specified `int8_t` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int8_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_int8(const void* a, const void* b);

/**
 * @brief Determines whether two specified `uint8_t` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint8_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_uint8(const void* a, const void* b);

/**
 * @brief Determines whether two specified `int16_t` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int16_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_int16(const void* a, const void* b);

/**
 * @brief Determines whether two specified `uint16_t` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint16_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_uint16(const void* a, const void* b);

/**
 * @brief Determines whether two specified `int32_t` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int32_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_int32(const void* a, const void* b);

/**
 * @brief Determines whether two specified `uint32_t` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint32_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_uint32(const void* a, const void* b);

/**
 * @brief Determines whether two specified `int64_t` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int64_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_int64(const void* a, const void* b);

/**
 * @brief Determines whether two specified `uint64_t` values are equal.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint64_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `*a` and `*b` are equal, otherwise `false`.
 */
bool scu_equal_uint64(const void* a, const void* b);

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