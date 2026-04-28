#ifndef SCU_HASH_MAP_H
#define SCU_HASH_MAP_H

#include "scu/common.h"
#include "scu/equal.h"
#include "scu/error.h"
#include "scu/hash.h"
#include "scu/types.h"

/** @brief Represents an unordered collection of key-value pairs. */
typedef struct ScuHashMap ScuHashMap;

/**
 * @brief Represents an iterator for a hash map.
 *
 * @warning The internal representation of the iterator is an implementation
 * detail and should not be relied upon. Most importantly, the behavior is
 * undefined if its fields are accessed directly.
 */
typedef struct ScuHashMapIter {

    /** @brief The hash map being iterated over. */
    ScuHashMap* hashMap;

    /** @brief The current index within the hash map. */
    Scuisize index;

} ScuHashMapIter;

/** @brief Represents an entry in a hash map. */
typedef struct ScuHashMapEntry {

    /** @brief The key of the entry. */
    void* key;

    /** @brief The value of the entry. */
    void* value;

} ScuHashMapEntry;

/**
 * @brief Allocates and initializes a new hash map with the specified key and
 * value sizes, hash and equality functions, and an unspecified default
 * capacity.
 *
 * @note This function dynamically allocates memory using `scu_malloc()` and
 * `scu_calloc()`.
 *
 * @warning The caller is responsible for deallocating the hash map with
 * `scu_hash_map_free()` when it is no longer needed.
 *
 * @param[in] keySize        The size of each key (in bytes).
 * @param[in] valueSize      The size of each value (in bytes).
 * @param[in] keyHashFunc    A function used for hashing keys.
 * @param[in] keyEqualFunc   A function used for comparing keys for equality.
 * @param[in] valueEqualFunc A function used for comparing values for equality.
 * @return A pointer to the new hash map, or `nullptr` on failure.
 */
[[nodiscard]]
ScuHashMap* scu_hash_map_new(
    Scuisize keySize,
    Scuisize valueSize,
    ScuHashFunc* keyHashFunc,
    ScuEqualFunc* keyEqualFunc,
    ScuEqualFunc* valueEqualFunc
);

/**
 * @brief Allocates and initializes a new hash map with the specified key and
 * value sizes, hash and equality functions, and initial capacity.
 *
 * @note This function dynamically allocates memory using `scu_malloc()` and
 * `scu_calloc()`.
 *
 * @warning The caller is responsible for deallocating the hash map with
 * `scu_hash_map_free()` when it is no longer needed.
 *
 * @param[in] keySize        The size of each key (in bytes).
 * @param[in] valueSize      The size of each value (in bytes).
 * @param[in] capacity       The initial capacity (in number of key-value
 *                           pairs).
 * @param[in] keyHashFunc    A function used for hashing keys.
 * @param[in] keyEqualFunc   A function used for comparing keys for equality.
 * @param[in] valueEqualFunc A function used for comparing values for equality.
 * @return A pointer to the new hash map, or `nullptr` on failure.
 */
[[nodiscard]]
ScuHashMap* scu_hash_map_new_with_capacity(
    Scuisize keySize,
    Scuisize valueSize,
    Scuisize capacity,
    ScuHashFunc* keyHashFunc,
    ScuEqualFunc* keyEqualFunc,
    ScuEqualFunc* valueEqualFunc
);

/**
 * @brief Creates a shallow copy of a specified hash map.
 *
 * @note This function dynamically allocates memory using `scu_malloc()`.
 *
 * @warning The caller is responsible for deallocating the cloned hash map with
 * `scu_hash_map_free()` when it is no longer needed.
 *
 * @param[in] hashMap The hash map to clone.
 * @return A pointer to the cloned hash map, or `nullptr` on failure.
 */
[[nodiscard]]
ScuHashMap* scu_hash_map_clone(const ScuHashMap* hashMap);

/**
 * @brief Returns the capacity of a specified hash map, i.e., the maximum number
 * of key-value pairs that can be stored before a reallocation is required.
 *
 * @note The capacity can be influenced to a certain extent using
 * `scu_hash_map_ensure_capacity()` and `scu_hash_map_trim_excess()`. See their
 * respective documentation for details.
 *
 * @param[in] hashMap The hash map to examine.
 * @return The capacity of the specified hash map.
 */
Scuisize scu_hash_map_capacity(const ScuHashMap* hashMap);

/**
 * @brief Returns the number of key-value pairs in a specified hash map.
 *
 * @param[in] hashMap The hash map to examine.
 * @return The number of key-value pairs in the specified hash map.
 */
Scuisize scu_hash_map_count(const ScuHashMap* hashMap);

/**
 * @brief Ensures that a specified hash map has at least a specified capacity.
 *
 * @note This function dynamically allocates memory using `scu_calloc()`.
 *
 * @param[in, out] hashMap  The hash map to ensure the capacity of.
 * @param[in]      capacity The desired capacity (in number of key-value pairs).
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
ScuError scu_hash_map_ensure_capacity(ScuHashMap* hashMap, Scuisize capacity);

/**
 * @brief Adds a new key-value pair to a specified hash map.
 *
 * @note This function dynamically allocates memory using `scu_malloc()` and
 * `scu_calloc()`.
 *
 * @warning The behavior is undefined if the key is already present in the hash
 * map. Use `scu_hash_map_try_add()` to handle this case gracefully.
 *
 * @param[in, out] hashMap The hash map to add the key-value pair to.
 * @param[in]      key     The key to add.
 * @param[in]      value   The value to associate with the key.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
ScuError scu_hash_map_add(
    ScuHashMap* restrict hashMap,
    const void* restrict key,
    const void* restrict value
);

/**
 * @brief Tries to add a new key-value pair to a specified hash map.
 *
 * @note This function dynamically allocates memory using `scu_malloc()` and
 * `scu_calloc()`.
 *
 * @param[in, out] hashMap The hash map to add the key-value pair to.
 * @param[in]      key     The key to add.
 * @param[in]      value   The value to associate with the key.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred,
 * `SCU_ERROR_ALREADY_PRESENT` if the key is already present in the hash map, or
 * `SCU_ERROR_NONE` on success.
 */
ScuError scu_hash_map_try_add(
    ScuHashMap* restrict hashMap,
    const void* restrict key,
    const void* restrict value
);

/**
 * @brief Gets the value associated with a key in a specified hash map.
 *
 * @warning The behavior is undefined if the key is not present in the hash map.
 * Use `scu_hash_map_try_get()` to handle this case gracefully.
 *
 * @param[in] hashMap The hash map to examine.
 * @param[in] key     The key to look up.
 * @return A pointer to the value associated with the specified key.
 */
void* scu_hash_map_get(const ScuHashMap* hashMap, const void* key);

/**
 * @brief Tries to get the value associated with a key in a specified hash map.
 *
 * @note This function is an implementation detail and not intended to be called
 * directly. Use the `scu_hash_map_try_get()` macro instead.
 *
 * @param[in]  hashMap The hash map to examine.
 * @param[in]  key     The key to look up.
 * @param[out] value   A pointer to the value associated with the specified key
 *                     on success, otherwise a `nullptr`.
 * @return `true` if the key was present in the hash map, otherwise `false`.
 */
bool scu_hash_map_try_get_impl(
    const ScuHashMap* restrict hashMap,
    const void* restrict key,
    void* restrict* restrict value
);

/**
 * @brief Tries to get the value associated with a key in a specified hash map.
 *
 * @param[in]  hashMap The hash map to examine.
 * @param[in]  key     The key to look up.
 * @param[out] value   A pointer to the value associated with the specified key
 *                     on success, otherwise a `nullptr`.
 * @return `true` if the key was present in the hash map, otherwise `false`.
 */
#define scu_hash_map_try_get(hashMap, key, value)             \
    scu_hash_map_try_get_impl(hashMap, key, (void**) (value))

/**
 * @brief Associates a key with a new value in a specified hash map.
 *
 * @note This function dynamically allocates memory using `scu_malloc()` and
 * `scu_calloc()`.
 *
 * If the key is already present in the specified hash map, its associated value
 * is replaced with the new value. Otherwise, a new key-value pair is added to
 * the hash map with the specified key and value. Note that this function is
 * primarily intended for updating the values of existing keys, and is optimized
 * for this use case. If it is known that the key is (likely) not present in the
 * hash map, consider using `scu_hash_map_add()` or `scu_hash_map_try_add()`
 * instead, which may be more efficient in this case.
 *
 * @param[in, out] hashMap The hash map to set the value in.
 * @param[in]      key     The key to associate with the new value.
 * @param[in]      value   The new value to associate with the key.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
ScuError scu_hash_map_set(
    ScuHashMap* restrict hashMap,
    const void* restrict key,
    const void* restrict value
);

/**
 * @brief Determines whether a key is present in a specified hash map.
 *
 * @param[in] hashMap The hash map to examine.
 * @param[in] key     The key to search for.
 * @return `true` if the key is present in the hash map, otherwise `false`.
 */
bool scu_hash_map_contains_key(const ScuHashMap* hashMap, const void* key);

/**
 * @brief Determines whether a value is present in a specified hash map.
 *
 * @param[in] hashMap The hash map to examine.
 * @param[in] value   The value to search for.
 * @return `true` if the value is present in the hash map, otherwise `false`.
 */
bool scu_hash_map_contains_value(const ScuHashMap* hashMap, const void* value);

/**
 * @brief Removes a key-value pair with a specified key from a specified hash
 * map.
 *
 * @note Consider using `scu_hash_map_trim_excess()` if you wish to reduce the
 * memory usage of the hash map after removing key-value pairs.
 *
 * @warning This function does not deallocate the key or value, it only removes
 * the key-value pair from the hash map. The caller is responsible for
 * deallocating the removed key and value if they are pointers to dynamically
 * allocated objects and no other references to them exist.
 *
 * @param[in, out] hashMap The hash map to remove the key-value pair from.
 * @param[in]      key     The key of the key-value pair to remove.
 * @return `true` if the key-value pair with the specified key was present and
 * removed, otherwise `false`.
 */
bool scu_hash_map_remove(
    ScuHashMap* restrict hashMap,
    const void* restrict key
);

/**
 * @brief Removes all key-value pairs from a specified hash map.
 *
 * @note Consider using `scu_hash_map_trim_excess()` if you wish to reduce the
 * memory usage of the hash map after clearing it.
 *
 * @warning This function does not deallocate the hash map itself nor the
 * key-value pairs contained within, it only resets the number of key-value
 * pairs to zero. The caller is responsible for deallocating the individual keys
 * and values if they are pointers to dynamically allocated objects and no other
 * references to them exist.
 *
 * @param[in, out] hashMap The hash map to clear.
 */
void scu_hash_map_clear(ScuHashMap* hashMap);

/**
 * @brief Trims the excess capacity of a specified hash map to match its current
 * number of key-value pairs.
 *
 * @note This function dynamically allocates memory using `scu_calloc()`.
 *
 * @param[in, out] hashMap The hash map to trim.
 * @return `SCU_ERROR_OUT_OF_MEMORY` if an out-of-memory condition occurred, or
 * `SCU_ERROR_NONE` on success.
 */
ScuError scu_hash_map_trim_excess(ScuHashMap* hashMap);

/**
 * @brief Returns an iterator for a specified hash map.
 *
 * @note The iterator is initially positioned before the first key-value pair of
 * the hash map (if any). This means that `scu_hash_map_iter_move_next()` must
 * be called before accessing the first and subsequent key-value pairs with
 * `scu_hash_map_iter_current()`.
 *
 * @warning The behavior is undefined if the hash map being iterated over is
 * modified (e.g., key-value pairs are added or removed) while the iterator is
 * in use.
 *
 * @param[in] hashMap The hash map to iterate over.
 * @return An iterator for the specified hash map.
 */
ScuHashMapIter scu_hash_map_iter(const ScuHashMap* hashMap);

/**
 * @brief Advances a specified hash map iterator to the next key-value pair.
 *
 * @param[in, out] iter The iterator to advance.
 * @return `true` if the iterator was successfully advanced to the next
 * key-value pair, otherwise `false` (i.e., the hash map does not contain any
 * more key-value pairs).
 */
bool scu_hash_map_iter_move_next(ScuHashMapIter* iter);

/**
 * @brief Returns the current key-value pair of a specified hash map iterator.
 *
 * @param[in] iter The iterator to examine.
 * @return An entry representing the current key-value pair of the iterator.
 */
ScuHashMapEntry scu_hash_map_iter_current(const ScuHashMapIter* iter);

/**
 * @brief Resets a specified hash map iterator to its initial position.
 *
 * @note The iterator is initially positioned before the first key-value pair of
 * the hash map (if any). This means that `scu_hash_map_iter_move_next()` must
 * be called before accessing the first and subsequent key-value pairs with
 * `scu_hash_map_iter_current()`.
 *
 * @param[in, out] iter The iterator to reset.
 */
void scu_hash_map_iter_reset(ScuHashMapIter* iter);

/**
 * @brief Deallocates a specified hash map.
 *
 * @note If `hashMap` is a `nullptr`, this function does nothing.
 *
 * @warning This function only deallocates the memory occupied by the hash map
 * itself, but not the key-value pairs contained within. The caller is
 * responsible for deallocating the individual keys and values if they are
 * pointers to dynamically allocated objects and no other references to them
 * exist.
 *
 * The behavior is undefined if the hash map is used after it has been
 * deallocated.
 *
 * @param[in, out] hashMap The hash map to deallocate.
 */
void scu_hash_map_free(ScuHashMap* hashMap);

/**
 * @brief Iterates over each key-value pair in a specified hash map.
 *
 * This macro expands to a for loop that iterates over each key-value pair in
 * the specified hash map. During each iteration, the provided variable is
 * assigned an entry representing the current key-value pair.
 *
 * The following example demonstrates the basic usage of this macro:
 *
 * ```c
 * // K and V are the types of the keys and values stored in the hash map.
 * ScuHashMap* map = scu_hash_map_new(SCU_SIZEOF(K), SCU_SIZEOF(V), ...);
 * ...
 * ScuHashMapEntry entry;
 * SCU_HASH_MAP_FOREACH(entry, map) {
 *     // Do something with the key and value.
 *     K* key = entry.key;
 *     V* value = entry.value;
 * }
 * ```
 *
 * @note The variable `entry` must be declared manually before the loop. It must
 * be of type `ScuHashMapEntry`.
 *
 * @warning The behavior is undefined if the hash map is modified (e.g.,
 * key-value pairs are added or removed) while being iterated over.
 *
 * @param[out] entry   An entry representing the current key-value pair.
 * @param[in]  hashMap The hash map to iterate over.
 */
#define SCU_HASH_MAP_FOREACH(entry, hashMap)                                     \
    for (                                                                        \
        ScuHashMapIter SCU_XCONCAT(it, __LINE__) = scu_hash_map_iter(hashMap);   \
        scu_hash_map_iter_move_next(&SCU_XCONCAT(it, __LINE__))                  \
            && (                                                                 \
                (entry) = scu_hash_map_iter_current(&SCU_XCONCAT(it, __LINE__)), \
                true                                                             \
            );                                                                   \
    )

#endif