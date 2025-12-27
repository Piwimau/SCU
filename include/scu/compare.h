#ifndef SCU_COMPARE_H
#define SCU_COMPARE_H

#include <stdint.h>

/**
 * @brief Compares two specified values.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they are equal,
 * or a positive value if `*a` is greater than `*b`.
 */
typedef int SCUCompareFunc(const void* a, const void* b);

/**
 * @brief Compares two specified `int8_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int8_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they are equal,
 * or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_int8(const void* a, const void* b);

/**
 * @brief Compares two specified `int8_t` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int8_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they are
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_int8_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `uint8_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint8_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they are equal,
 * or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_uint8(const void* a, const void* b);

/**
 * @brief Compares two specified `uint8_t` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint8_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they are
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_uint8_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `int16_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int16_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they are equal,
 * or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_int16(const void* a, const void* b);

/**
 * @brief Compares two specified `int16_t` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int16_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they are
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_int16_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `uint16_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint16_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they are equal,
 * or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_uint16(const void* a, const void* b);

/**
 * @brief Compares two specified `uint16_t` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint16_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they are
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_uint16_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `int32_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int32_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they are equal,
 * or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_int32(const void* a, const void* b);

/**
 * @brief Compares two specified `int32_t` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int32_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they are
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_int32_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `uint32_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint32_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they are equal,
 * or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_uint32(const void* a, const void* b);

/**
 * @brief Compares two specified `uint32_t` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint32_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they are
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_uint32_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `int64_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int64_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they are equal,
 * or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_int64(const void* a, const void* b);

/**
 * @brief Compares two specified `int64_t` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int64_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they are
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_int64_rev(const void* a, const void* b);

/**
 * @brief Compares two specified `uint64_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint64_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is less than `*b`, zero if they are equal,
 * or a positive value if `*a` is greater than `*b`.
 */
int scu_compare_uint64(const void* a, const void* b);

/**
 * @brief Compares two specified `uint64_t` values in reverse order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint64_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `*a` is greater than `*b`, zero if they are
 * equal, or a positive value if `*a` is less than `*b`.
 */
int scu_compare_uint64_rev(const void* a, const void* b);

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