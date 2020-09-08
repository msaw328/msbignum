#ifndef _BIGINT_DEFAULTS_H_
#define _BIGINT_DEFAULTS_H_

#include "msbignum/types.h"

// Number of chunks that gets allocated for data when constructing using immediate value
// Example: 4 chunks, bignum_chunk_t equal to uint32_t -> 4 * 4 bytes = 16 bytes (128 bit integers)
#define BIGNUM_DEFAULT_CHUNKS 4

// Default number of chunks appended when overflow happens and excess to add when multiplying
#define BIGNUM_DEFAULT_EXCESS 1

// Max value of a chunk
#define BIGNUM_MAX_CHUNK (~((bignum_chunk_t) 0))

#endif
