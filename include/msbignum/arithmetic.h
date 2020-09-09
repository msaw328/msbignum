#ifndef _BIGNUM_API_ARITHMETIC_H_
#define _BIGNUM_API_ARITHMETIC_H_

// Arithmetic operations on bignums

#include <msbignum/types.h>

// Add bignums
void bignum_add(bignum_t* a, bignum_t* b, bignum_t* result);

// Multiply bignums
void bignum_mul(bignum_t* a, bignum_t* b, bignum_t* result);

#endif
