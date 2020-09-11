#ifndef _BIGNUM_API_STRCONV_H_
#define _BIGNUM_API_STRCONV_H_

// Conversion between bignum and strings

#include <stddef.h>

#include <msbignum/types.h>

// Returns the size of a char buffer necessary to hold string representation
// of bignum pointed to by bn in a given numeric base, this accounts for
// digits as well as null byte at the end. It may be off by few bytes, as it is
// an approximation. bn has to point to an initialized bignum and base has to be
// in range 2 to 16 inclusive
size_t bignum_tostr_bufsize(bignum_t* bn, int base);

// Converts bignum pointed by bn int oa string and stores it in buffer pointed to by buf
// buffer should have size determined by calling bignum_tostr_bufsize() or bigger
void bignum_tostr(bignum_t* bn, int base, char* buf);

// Sets value of bignum from string in given base, does not allocate memory, bignum should be
// initialized already (for example using bignum_init() or any other function from base.h)
// Stops reading string at n first digits or when encountering a null byte
// If n is set to 0 then stops only at null byte
void bignum_setstr(bignum_t* bn, int base, char* buf, size_t n);

#endif
