#pragma once
#include "ethash.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

static inline uint8_t ethash_h256_get(ethash_h256_t const* hash, unsigned int i)
{
	return hash->b[i];
}

static inline void ethash_h256_set(ethash_h256_t* hash, unsigned int i, uint8_t v)
{
	hash->b[i] = v;
}

static inline void ethash_h256_reset(ethash_h256_t* hash)
{
	memset(hash, 0, 32);
}

// Returns if hash is less than or equal to boundary (2^256/difficulty)
static inline bool ethash_check_difficulty(
	ethash_h256_t const* hash,
	ethash_h256_t const* boundary
)
{
	// Boundary is big endian
	for (int i = 0; i < 32; i++) {
		if (ethash_h256_get(hash, i) == ethash_h256_get(boundary, i)) {
			continue;
		}
		return ethash_h256_get(hash, i) < ethash_h256_get(boundary, i);
	}
	return true;
}

/**
 *  Difficulty quick check for POW preverification
 *
 * @param header_hash      The hash of the header
 * @param nonce            The block's nonce
 * @param mix_hash         The mix digest hash
 * @param boundary         The boundary is defined as (2^256 / difficulty)
 * @return                 true for succesful pre-verification and false otherwise
 */
bool ethash_quick_check_difficulty(
	ethash_h256_t const* header_hash,
	uint64_t const nonce,
	ethash_h256_t const* mix_hash,
	ethash_h256_t const* boundary
);

/**
 * Allocate and initialize a new ethash_light handler. Internal version
 *
 * @param cache_size    The size of the cache in bytes
 * @param seed          Block seedhash to be used during the computation of the
 *                      cache nodes
 * @return              Newly allocated ethash_light handler or NULL in case of
 *                      ERRNOMEM or invalid parameters used for @ref ethash_compute_cache_nodes()
 */
ethash_light_ptr ethash_light_new_internal(uint64_t cache_size, ethash_h256_t const* seed);

/**
 * Calculate the light client data. Internal version.
 *
 * @param light          The light client handler
 * @param full_size      The size of the full data in bytes.
 * @param header_hash    The header hash to pack into the mix
 * @param nonce          The nonce to pack into the mix
 * @return               The resulting hash.
 */
ethash_return_value_t ethash_light_compute_internal(
	ethash_light_ptr light,
	uint64_t full_size,
	ethash_h256_t const header_hash,
	uint64_t nonce
);

struct ethash_full {
	FILE* file;
	uint64_t file_size;
	ethash_node_t* data;
};

/**
 * Allocate and initialize a new ethash_full handler. Internal version.
 *
 * @param dirname        The directory in which to put the DAG file.
 * @param seedhash       The seed hash of the block. Used in the DAG file naming.
 * @param full_size      The size of the full data in bytes.
 * @param cache          A cache object to use that was allocated with @ref ethash_cache_new().
 *                       Iff this function succeeds the ethash_full_t will take memory
 *                       memory ownership of the cache and free it at deletion. If
 *                       not then the user still has to handle freeing of the cache himself.
 * @param callback       A callback function with signature of @ref ethash_callback_t
 *                       It accepts an unsigned with which a progress of DAG calculation
 *                       can be displayed. If all goes well the callback should return 0.
 *                       If a non-zero value is returned then DAG generation will stop.
 * @return               Newly allocated ethash_full handler or NULL in case of
 *                       ERRNOMEM or invalid parameters used for @ref ethash_compute_full_data()
 */
//ethash_full_t ethash_full_new_internal(
void ethash_full_new_internal(
	char const* dirname,
	ethash_h256_t const seed_hash,
	uint64_t full_size,
	ethash_light_ptr const light,
	ethash_callback_t callback
);

void ethash_calculate_dag_item(
	ethash_node_t* const ret,
	uint32_t node_index,
	ethash_light_ptr const cache
);

void ethash_quick_hash(
	ethash_h256_t* return_hash,
	ethash_h256_t const* header_hash,
	const uint64_t nonce,
	ethash_h256_t const* mix_hash
);

uint64_t ethash_get_datasize(uint64_t const block_number);
uint64_t ethash_get_cachesize(uint64_t const block_number);

/**
 * Compute the memory data for a full node's memory
 *
 * @param mem         A pointer to an ethash full's memory
 * @param full_size   The size of the full data in bytes
 * @param cache       A cache object to use in the calculation
 * @param callback    The callback function. Check @ref ethash_full_new() for details.
 * @return            true if all went fine and false for invalid parameters
 */
bool ethash_compute_full_data(
	void* mem,
	uint64_t full_size,
	ethash_light_ptr const light,
	ethash_callback_t callback
);

#ifdef __cplusplus
}
#endif
