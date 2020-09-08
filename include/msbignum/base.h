#ifndef _BIGNUM_API_BASE_H_
#define _BIGNUM_API_BASE_H_

// Basic bignum functions - creation, deletion

#include "msbignum/types.h"

// Init bignum to value 0
void bignum_setzero(bignum_t* bn);

// Init bignum to chunk value
void bignum_setchunk(bignum_t* bn, bignum_chunk_t value);

// Init bignum from another bignum
void bignum_clone(bignum_t* src, bignum_t* dst);

// Cleans up bignum data - bignum is unusable after calling this!
void bignum_cleanup(bignum_t* bn);

#endif
