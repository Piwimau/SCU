#ifndef SCU_COMPARE_H
#define SCU_COMPARE_H

#include <stdint.h>

/**
 * @brief Compares two specified values.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is less than `b`, zero if they are equal, or
 * a positive value if `a` is greater than `b`.
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
 * @return A negative value if `a` is less than `b`, zero if they are equal, or
 * a positive value if `a` is greater than `b`.
 */
int scu_compare_int8(const void* a, const void* b);

/**
 * @brief Compares two specified `int8_t` values in descending order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int8_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is greater than `b`, zero if they are equal,
 * or a positive value if `a` is less than `b`.
 */
int scu_compare_int8_desc(const void* a, const void* b);

/**
 * @brief Compares two specified `uint8_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint8_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is less than `b`, zero if they are equal, or
 * a positive value if `a` is greater than `b`.
 */
int scu_compare_uint8(const void* a, const void* b);

/**
 * @brief Compares two specified `uint8_t` values in descending order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint8_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is greater than `b`, zero if they are equal,
 * or a positive value if `a` is less than `b`.
 */
int scu_compare_uint8_desc(const void* a, const void* b);

/**
 * @brief Compares two specified `int16_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int16_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is less than `b`, zero if they are equal, or
 * a positive value if `a` is greater than `b`.
 */
int scu_compare_int16(const void* a, const void* b);

/**
 * @brief Compares two specified `int16_t` values in descending order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int16_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is greater than `b`, zero if they are equal,
 * or a positive value if `a` is less than `b`.
 */
int scu_compare_int16_desc(const void* a, const void* b);

/**
 * @brief Compares two specified `uint16_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint16_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is less than `b`, zero if they are equal, or
 * a positive value if `a` is greater than `b`.
 */
int scu_compare_uint16(const void* a, const void* b);

/**
 * @brief Compares two specified `uint16_t` values in descending order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint16_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is greater than `b`, zero if they are equal,
 * or a positive value if `a` is less than `b`.
 */
int scu_compare_uint16_desc(const void* a, const void* b);

/**
 * @brief Compares two specified `int32_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int32_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is less than `b`, zero if they are equal, or
 * a positive value if `a` is greater than `b`.
 */
int scu_compare_int32(const void* a, const void* b);

/**
 * @brief Compares two specified `int32_t` values in descending order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int32_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is greater than `b`, zero if they are equal,
 * or a positive value if `a` is less than `b`.
 */
int scu_compare_int32_desc(const void* a, const void* b);

/**
 * @brief Compares two specified `uint32_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint32_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is less than `b`, zero if they are equal, or
 * a positive value if `a` is greater than `b`.
 */
int scu_compare_uint32(const void* a, const void* b);

/**
 * @brief Compares two specified `uint32_t` values in descending order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint32_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is greater than `b`, zero if they are equal,
 * or a positive value if `a` is less than `b`.
 */
int scu_compare_uint32_desc(const void* a, const void* b);

/**
 * @brief Compares two specified `int64_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int64_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is less than `b`, zero if they are equal, or
 * a positive value if `a` is greater than `b`.
 */
int scu_compare_int64(const void* a, const void* b);

/**
 * @brief Compares two specified `int64_t` values in descending order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to an
 * `int64_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is greater than `b`, zero if they are equal,
 * or a positive value if `a` is less than `b`.
 */
int scu_compare_int64_desc(const void* a, const void* b);

/**
 * @brief Compares two specified `uint64_t` values.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint64_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is less than `b`, zero if they are equal, or
 * a positive value if `a` is greater than `b`.
 */
int scu_compare_uint64(const void* a, const void* b);

/**
 * @brief Compares two specified `uint64_t` values in descending order.
 *
 * @warning The behavior is undefined if `a` or `b` is not a pointer to a
 * `uint64_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return A negative value if `a` is greater than `b`, zero if they are equal,
 * or a positive value if `a` is less than `b`.
 */
int scu_compare_uint64_desc(const void* a, const void* b);

#endif