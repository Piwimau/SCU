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
 * @brief Returns a hash for a specified `int8_t` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `int8_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `int8_t` value.
 */
uint64_t scu_hash_int8(const void* value);

/**
 * @brief Returns a hash for a specified `uint8_t` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to a
 * `uint8_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `uint8_t` value.
 */
uint64_t scu_hash_uint8(const void* value);

/**
 * @brief Returns a hash for a specified `int16_t` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `int16_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `int16_t` value.
 */
uint64_t scu_hash_int16(const void* value);

/**
 * @brief Returns a hash for a specified `uint16_t` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to a
 * `uint16_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `uint16_t` value.
 */
uint64_t scu_hash_uint16(const void* value);

/**
 * @brief Returns a hash for a specified `int32_t` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `int32_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `int32_t` value.
 */
uint64_t scu_hash_int32(const void* value);

/**
 * @brief Returns a hash for a specified `uint32_t` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to a
 * `uint32_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `uint32_t` value.
 */
uint64_t scu_hash_uint32(const void* value);

/**
 * @brief Returns a hash for a specified `int64_t` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `int64_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `int64_t` value.
 */
uint64_t scu_hash_int64(const void* value);

/**
 * @brief Returns a hash for a specified `uint64_t` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to a
 * `uint64_t`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified `uint64_t` value.
 */
uint64_t scu_hash_uint64(const void* value);

/**
 * @brief Returns a hash for a specified null-terminated byte string.
 *
 * @warning The behavior is undefined if `value` is not a pointer to a pointer
 * to a null-terminated byte string. Note that `value` must not be a direct
 * pointer to the string itself, but a pointer to a pointer (i.e., `value` is
 * interpreted as `const char* const*`).
 *
 * @param[in] value A pointer to a pointer to the null-terminated byte string to
 *                  hash.
 * @return A hash for the specified null-terminated byte string.
 */
uint64_t scu_hash_str(const void* value);

#endif