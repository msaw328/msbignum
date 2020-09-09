#ifndef _BIGNUM_API_CMP_H_
#define _BIGNUM_API_CMP_H_

// Comparisions between bignums

#include <msbignum/types.h>

// Returns 1 if a is bigger, -1 if b is bigger and 0 if theyre equal
int bignum_cmp(bignum_t* a, bignum_t* b);

// Utility macros for a greater-than, less-than and equal b
#define BIGNUM_GT(a, b) (bignum_cmp(a, b) == 1)
#define BIGNUM_LT(a, b) (bignum_cmp(a, b) == -1)
#define BIGNUM_EQ(a, b) (bignum_cmp(a, b) == 0)

#endif
