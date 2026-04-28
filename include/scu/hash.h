#ifndef SCU_HASH_H
#define SCU_HASH_H

#include "scu/types.h"

/**
 * @brief Returns a hash for a specified value.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
typedef Scuusize ScuHashFunc(const void* value);

/**
 * @brief Returns a hash for a specified `bool` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to a `bool`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_bool(const void* value);

/**
 * @brief Returns a hash for a specified `Scubyte` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scubyte`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_byte(const void* value);

/**
 * @brief Returns a hash for a specified `Scui8` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an `Scui8`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_i8(const void* value);

/**
 * @brief Returns a hash for a specified `Scuu8` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an `Scuu8`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_u8(const void* value);

/**
 * @brief Returns a hash for a specified `Scui16` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scui16`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_i16(const void* value);

/**
 * @brief Returns a hash for a specified `Scuu16` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scuu16`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_u16(const void* value);

/**
 * @brief Returns a hash for a specified `Scui32` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scui32`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_i32(const void* value);

/**
 * @brief Returns a hash for a specified `Scuu32` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scuu32`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_u32(const void* value);

/**
 * @brief Returns a hash for a specified `Scui64` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scui64`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_i64(const void* value);

/**
 * @brief Returns a hash for a specified `Scuu64` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scuu64`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_u64(const void* value);

/**
 * @brief Returns a hash for a specified `Scuiptr` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scuiptr`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_iptr(const void* value);

/**
 * @brief Returns a hash for a specified `Scuuptr` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scuuptr`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_uptr(const void* value);

/**
 * @brief Returns a hash for a specified `Scuisize` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scuisize`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_isize(const void* value);

/**
 * @brief Returns a hash for a specified `Scuusize` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scuusize`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_usize(const void* value);

/**
 * @brief Returns a hash for a specified `Scuf32` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scuf32`, or if `*value` is NaN.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_f32(const void* value);

/**
 * @brief Returns a hash for a specified `Scuf64` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scuf64`, or if `*value` is NaN.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_f64(const void* value);

/**
 * @brief Returns a hash for a specified `char` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to a `char`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_char(const void* value);

/**
 * @brief Returns a hash for a specified `Scuchar8` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scuchar8`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_char8(const void* value);

/**
 * @brief Returns a hash for a specified `Scuchar16` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scuchar16`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_char16(const void* value);

/**
 * @brief Returns a hash for a specified `Scuchar32` value.
 *
 * @warning The behavior is undefined if `value` is not a pointer to an
 * `Scuchar32`.
 *
 * @param[in] value A pointer to the value to hash.
 * @return A hash for the specified value.
 */
Scuusize scu_hash_char32(const void* value);

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
Scuusize scu_hash_bytes(const void* block, Scuisize count);

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
Scuusize scu_hash_str(const void* value);

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
 * Scuusize hash_vector(const void* value) {
 *     SCU_ASSERT(value != nullptr);
 *     const Vector* vector = (const Vector*) value;
 *     Scuusize hash = 0;
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
Scuusize scu_hash_combine(Scuusize seed, Scuusize hash);

#endif