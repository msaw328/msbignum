#ifndef _BIGNUM_MEM_H_
#define _BIGNUM_MEM_H_

#include <stddef.h>

#include "msbignum/types.h"

// Reallocs the internal data buffer, copies data to new location
void __bignum_realloc(bignum_t* bn, size_t nchunks);

// Returns number of of chunks used
size_t __bignum_chunks_used(bignum_t* bn);

#endif
