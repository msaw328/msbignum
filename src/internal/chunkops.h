#ifndef _BIGNUM_CHUNKOPS_H_
#define _BIGNUM_CHUNKOPS_H_

#include "msbignum/types.h"

// Extends normal chunk to safe size which guarantees no overflows
bignum_chunksafe_t __bignum_chunk_promote(bignum_chunk_t c);

// Get the normal chunk value from extended safe chunk
bignum_chunk_t __bignum_chunk_value_part(bignum_chunksafe_t cs);

// Get the carry value from extended safe chunk
bignum_chunk_t __bignum_chunk_carry_part(bignum_chunksafe_t cs);

#endif
