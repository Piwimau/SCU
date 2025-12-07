#ifndef SCU_HASH_H
#define SCU_HASH_H

#include <stdint.h>

/**
 * @brief Returns a hash for a specified value.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
typedef uint64_t SCUHashFunc(const void* value);

/**
 * @brief Returns a hash for a specified `int8_t`.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `int8_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `int8_t`.
 */
uint64_t scu_hash_int8(const void* value);

/**
 * @brief Returns a hash for a specified `uint8_t`.
 *
 * @warning The behavior is undefined if `value` is not a pointer to a
 * `uint8_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `uint8_t`.
 */
uint64_t scu_hash_uint8(const void* value);

/**
 * @brief Returns a hash for a specified `int16_t`.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `int16_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `int16_t`.
 */
uint64_t scu_hash_int16(const void* value);

/**
 * @brief Returns a hash for a specified `uint16_t`.
 *
 * @warning The behavior is undefined if `value` is not a pointer to a
 * `uint16_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `uint16_t`.
 */
uint64_t scu_hash_uint16(const void* value);

/**
 * @brief Returns a hash for a specified `int32_t`.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `int32_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `int32_t`.
 */
uint64_t scu_hash_int32(const void* value);

/**
 * @brief Returns a hash for a specified `uint32_t`.
 *
 * @warning The behavior is undefined if `value` is not a pointer to a
 * `uint32_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `uint32_t`.
 */
uint64_t scu_hash_uint32(const void* value);

/**
 * @brief Returns a hash for a specified `int64_t`.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `int64_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `int64_t`.
 */
uint64_t scu_hash_int64(const void* value);

/**
 * @brief Returns a hash for a specified `uint64_t`.
 *
 * @warning The behavior is undefined if `value` is not a pointer to a
 * `uint64_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `uint64_t`.
 */
uint64_t scu_hash_uint64(const void* value);

#endif