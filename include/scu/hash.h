#ifndef SCU_HASH_H
#define SCU_HASH_H

#include "scu/types.h"

/**
 * @brief Returns a hash for a specified value.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
typedef SCUusize SCUHashFunc(const void* value);

/**
 * @brief Returns a hash for a specified `SCUbyte` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUbyte`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_byte(const void* value);

/**
 * @brief Returns a hash for a specified `SCUi8` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an `SCUi8`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_i8(const void* value);

/**
 * @brief Returns a hash for a specified `SCUu8` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an `SCUu8`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_u8(const void* value);

/**
 * @brief Returns a hash for a specified `SCUi16` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUi16`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_i16(const void* value);

/**
 * @brief Returns a hash for a specified `SCUu16` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUu16`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_u16(const void* value);

/**
 * @brief Returns a hash for a specified `SCUi32` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUi32`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_i32(const void* value);

/**
 * @brief Returns a hash for a specified `SCUu32` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUu32`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_u32(const void* value);

/**
 * @brief Returns a hash for a specified `SCUi64` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUi64`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_i64(const void* value);

/**
 * @brief Returns a hash for a specified `SCUu64` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUu64`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_u64(const void* value);

/**
 * @brief Returns a hash for a specified `SCUiptr` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUiptr`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_iptr(const void* value);

/**
 * @brief Returns a hash for a specified `SCUuptr` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUuptr`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_uptr(const void* value);

/**
 * @brief Returns a hash for a specified `SCUisize` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUisize`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_isize(const void* value);

/**
 * @brief Returns a hash for a specified `SCUusize` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUusize`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_usize(const void* value);

/**
 * @brief Returns a hash for a specified `SCUf32` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUf32`, or if `*value` is NaN.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_f32(const void* value);

/**
 * @brief Returns a hash for a specified `SCUf64` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUf64`, or if `*value` is NaN.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_f64(const void* value);

/**
 * @brief Returns a hash for a specified `char` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to a `char`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_char(const void* value);

/**
 * @brief Returns a hash for a specified `SCUchar8` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUchar8`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_char8(const void* value);

/**
 * @brief Returns a hash for a specified `SCUchar16` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUchar16`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_char16(const void* value);

/**
 * @brief Returns a hash for a specified `SCUchar32` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `SCUchar32`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
SCUusize scu_hash_char32(const void* value);

/**
 * @brief Returns a hash for a specified block of memory.
 *
 * @warning The behavior is undefined if `block` is not a pointer to a block of
 * memory at least `count` bytes.
 *
 * @param[in] block A pointer to the block of memory to hash.
 * @param[in] count The size of the block (in bytes).
 * @return A hash for the specified block of memory.
 */
SCUusize scu_hash_bytes(const void* block, SCUisize count);

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
SCUusize scu_hash_str(const void* value);

/**
 * @brief Combines a hash with a specified accumulator hash.
 *
 * @note This function is mainly useful for creating hash functions for complex
 * or aggregate data types (such as structs or arrays) by combining the hashes
 * of their individual members or elements into a single hash.
 *
 * For the initial call, zero may be passed as the seed, as shown in the
 * following example:
 *
 * ```c
 * typedef struct Vector {
 *     f32 x;
 *     f32 y;
 * } Vector;
 *
 * SCUusize hash_vector(const void* value) {
 *     SCU_ASSERT(value != nullptr);
 *     const Vector* vector = (const Vector*) value;
 *     SCUusize hash = 0;
 *     hash = scu_hash_combine(hash, scu_hash_f32(&vector->x));
 *     hash = scu_hash_combine(hash, scu_hash_f32(&vector->y));
 *     return hash;
 * }
 * ```
 *
 * @param[in] seed The accumulator hash.
 * @param[in] hash The hash to mix into the accumulator.
 * @return The combined hash.
 */
SCUusize scu_hash_combine(SCUusize seed, SCUusize hash);

#endif