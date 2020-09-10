#ifndef _BIGNUM_API_BASE_H_
#define _BIGNUM_API_BASE_H_

// Basic bignum functions - creation, deletion

#include <stddef.h>
#include <msbignum/types.h>

// Functions that Init allocate memory and set bignum->allocated accordingly
// Before calling Init functions you should bignum_cleanup()

// Functions that don't init only manipulate value of data
// You don't have to bignum_cleanup() before calling them

// Init bignum to 0
void bignum_init(bignum_t* bn);

// Init bignum to chunk value
void bignum_fromchunk(bignum_t* bn, bignum_chunk_t value);

// Init bignum from raw data (copies data, len is number of chunks not number of bytes)
void bignum_fromdata(bignum_t* bn, bignum_chunk_t* data, size_t len);

// Init bignum from another bignum
void bignum_clone(bignum_t* src, bignum_t* dst);

// Don't init, set value of bignum to 0
void bignum_setzero(bignum_t* bn);

// Don't init, set value of bignum to chunk value
void bignum_setchunk(bignum_t* bn, bignum_chunk_t value);

// Cleans up bignum data - bignum is unusable after calling this!
void bignum_cleanup(bignum_t* bn);

#endif
