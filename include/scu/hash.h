#ifndef SCU_HASH_H
#define SCU_HASH_H

#include <stdint.h>

/**
 * @brief Returns a hash for a specified element.
 *
 * @param[in] elem A pointer to the element to hash.
 * @return A hash for the specified element.
 */
typedef uint64_t SCUHashFunc(const void* elem);

#endif