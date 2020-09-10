#ifndef _BIGNUM_CHUNKOPS_H_
#define _BIGNUM_CHUNKOPS_H_

#include "msbignum/types.h"

// Extends normal chunk to safe size which guarantees no overflows
bignum_chunksafe_t __bignum_chunk_promote(bignum_chunk_t c);

// Extends normal chunk to safe size with additional borrowed upper 32 bits (subtraction, division)
bignum_chunksafe_t __bignum_chunk_promote_withborrow(bignum_chunk_t c, bignum_chunk_t borrow);

// Get the normal chunk value from extended safe chunk
bignum_chunk_t __bignum_chunk_value_part(bignum_chunksafe_t cs);

// Get the carry value from extended safe chunk
bignum_chunk_t __bignum_chunk_carry_part(bignum_chunksafe_t cs);

#endif
