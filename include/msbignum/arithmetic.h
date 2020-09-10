#ifndef _BIGNUM_API_ARITHMETIC_H_
#define _BIGNUM_API_ARITHMETIC_H_

// Arithmetic operations on bignums

#include <msbignum/types.h>

// Add bignums
void bignum_add(bignum_t* a, bignum_t* b, bignum_t* result);

// Add a chunk to a bignum
void bignum_add_chunk(bignum_t* a, bignum_chunk_t b, bignum_t* result);

// Multiply bignums
void bignum_mul(bignum_t* a, bignum_t* b, bignum_t* result);

// Multiply bignum by a chunk
void bignum_mul_chunk(bignum_t* a, bignum_chunk_t b, bignum_t* result);

// Divide bignum a by chunk n, each of quotient and remainder may be NULL and then is not returned, if both are NULL function returns immediately
void bignum_div_chunk(bignum_t* a, bignum_chunk_t n, bignum_t* quotient, bignum_chunk_t* remainder);

// Reduce bignum a modulo n, optimized for when n is small enough to fit into a chunk
void bignum_mod_chunk(bignum_t* a, bignum_chunk_t n, bignum_chunk_t* result);

// TODO:now just implement strconv

#endif
