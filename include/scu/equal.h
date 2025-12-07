#ifndef SCU_EQUAL_H
#define SCU_EQUAL_H

/**
 * @brief Determines whether two specified values are equal.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `a` and `b` are equal, otherwise `false`.
 */
typedef bool SCUEqualFunc(const void* a, const void* b);

/**
 * @brief Determines whether two specified `int8_t` values are equal.
 *
 * @warning The behavior is undefined if either `a` or `b` is not a pointer to
 * an `int8_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `a` and `b` are equal, otherwise `false`.
 */
bool scu_equal_int8(const void* a, const void* b);

/**
 * @brief Determines whether two specified `uint8_t` values are equal.
 *
 * @warning The behavior is undefined if either `a` or `b` is not a pointer to
 * a `uint8_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `a` and `b` are equal, otherwise `false`.
 */
bool scu_equal_uint8(const void* a, const void* b);

/**
 * @brief Determines whether two specified `int16_t` values are equal.
 *
 * @warning The behavior is undefined if either `a` or `b` is not a pointer to
 * an `int16_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `a` and `b` are equal, otherwise `false`.
 */
bool scu_equal_int16(const void* a, const void* b);

/**
 * @brief Determines whether two specified `uint16_t` values are equal.
 *
 * @warning The behavior is undefined if either `a` or `b` is not a pointer to
 * a `uint16_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `a` and `b` are equal, otherwise `false`.
 */
bool scu_equal_uint16(const void* a, const void* b);

/**
 * @brief Determines whether two specified `int32_t` values are equal.
 *
 * @warning The behavior is undefined if either `a` or `b` is not a pointer to
 * an `int32_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `a` and `b` are equal, otherwise `false`.
 */
bool scu_equal_int32(const void* a, const void* b);

/**
 * @brief Determines whether two specified `uint32_t` values are equal.
 *
 * @warning The behavior is undefined if either `a` or `b` is not a pointer to
 * a `uint32_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `a` and `b` are equal, otherwise `false`.
 */
bool scu_equal_uint32(const void* a, const void* b);

/**
 * @brief Determines whether two specified `int64_t` values are equal.
 *
 * @warning The behavior is undefined if either `a` or `b` is not a pointer to
 * an `int64_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `a` and `b` are equal, otherwise `false`.
 */
bool scu_equal_int64(const void* a, const void* b);

/**
 * @brief Determines whether two specified `uint64_t` values are equal.
 *
 * @warning The behavior is undefined if either `a` or `b` is not a pointer to
 * a `uint64_t`.
 *
 * @param[in] a A pointer to the first value.
 * @param[in] b A pointer to the second value.
 * @return `true` if `a` and `b` are equal, otherwise `false`.
 */
bool scu_equal_uint64(const void* a, const void* b);

#endif