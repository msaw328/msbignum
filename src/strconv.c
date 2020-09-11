#include <stddef.h>
#include <string.h>

#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/cmp.h>
#include <msbignum/arithmetic.h>

#include "internal/mem.h"

// value - numerical value of a digit
// digit - character representing it
char __digits[] = "0123456789abcdef";
#define __DIGIT_FROM_VAL(val) (__digits[val])

int __val_from_digit(char digit) {
    if('0' <= digit && digit <= '9') return digit - '0';

    if('a' <= digit && digit <= 'f') return digit - 'a' + 10;

    if('A' <= digit && digit <= 'F') return digit - 'A' + 10;

    if(digit == '\0') return '\0';

    return 0;
}

// array of conversion ratios from chunkbase to other bases
// index 0 is for base 2, 1 for 3 etc
double __to_base[15] = {
    32.0,
    20.189752114286637,
    16.0,
    13.781649858348578,
    12.37928983150533,
    11.39862998745671,
    10.666666666666668,
    10.094876057143319,
    9.632959861247397,
    9.25007444217241,
    8.926174260836154,
    8.647620941674232,
    8.404785121190194,
    8.190656793914096,
    8.0
};

// array of conversion ratios from other bases to chunkbase
// index 0 is for base 2, 1 for 3 etc
double __from_base[15] = {
    0.03125,
    0.049530078147536134,
    0.0625,
    0.07256025296523007,
    0.08078007814753613,
    0.08772984131430013,
    0.09375,
    0.09906015629507227,
    0.10381025296523008,
    0.10810723808241555,
    0.11203007814753614,
    0.11563874119190913,
    0.11897984131430012,
    0.12209033111276621,
    0.125
};

#define IS_BASE_OK(base) (base >= 2 && base <= 16)

#define TOSTR_RATIO(base) (__to_base[base - 2])
#define SETSTR_RATIO(base) (__from_base[base - 2])

size_t bignum_tostr_bufsize(bignum_t* bn, int base) {
    if(!IS_BASE_OK(base)) return 0;

    size_t used = __bignum_chunks_used(bn);

    return (size_t) (((double) used) * TOSTR_RATIO(base) + 1.0) + 1; // one +1 is from the formula, the other is for null byte at the end of string
}

// http://www.numberworld.org/y-cruncher/internals/radix-conversion.html
void bignum_tostr(bignum_t* bn, int base, char* buf) {
    if(!IS_BASE_OK(base)) return;

    if(bignum_iszero(bn)) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    bignum_t tmp1, tmp2;
    bignum_t *src = &tmp1, *dst = &tmp2;

    bignum_chunk_t last_value = 0;

    bignum_chunk_t base_chunk = (bignum_chunk_t) base;

    bignum_clone(bn, &tmp1);
    bignum_init(&tmp2);

    size_t i = 0;
    while(!bignum_iszero(src)) {
        bignum_div_chunk(src, base_chunk, dst, &last_value);

        buf[i] = __DIGIT_FROM_VAL(last_value);
        i++;

        // swap pointers
        bignum_t* temp_ptr = src;
        src = dst;
        dst = temp_ptr;
        
        bignum_setzero(dst);
    }

    size_t half_of_buf = i / 2;

    // digits are in reverse, swap them
    for(size_t j = 0; j < half_of_buf; j++) {
        char tmp_digit = buf[j];
        buf[j] = buf[i - j - 1];
        buf[i - j - 1] = tmp_digit;
    }

    bignum_cleanup(&tmp1);
    bignum_cleanup(&tmp2);
}

// http://www.numberworld.org/y-cruncher/internals/radix-conversion.html
void bignum_setstr(bignum_t* bn, int base, char* str, size_t n) {
    if(!IS_BASE_OK(base)) return;

    // make sure data is big enough

    // if null byte is earlier than n, change n, but only if n != 0, otherwise ignore n
    if(n > 0)
        n = strnlen(str, n);
    else
        n = strlen(str);

    // from python script:
    //
    // def approx_blocks(n, modifier):
    //    return int((n * modifier) + 1)

    size_t chunks_needed = (size_t) (((double) n) * SETSTR_RATIO(base) + 1.0) + 1;
    __bignum_realloc(bn, chunks_needed);

    bignum_t tmp1, tmp2;
    bignum_init(&tmp1);
    bignum_init(&tmp2);
    __bignum_realloc(&tmp1, chunks_needed);
    __bignum_realloc(&tmp2, chunks_needed);

    bignum_t *src = &tmp1, *dst = &tmp2;

    bignum_chunk_t base_chunk = (bignum_chunk_t) base;

    // now do the magic
    size_t i = 0;
    bignum_chunk_t value = (bignum_chunk_t) __val_from_digit(str[i]);
    bignum_setchunk(src, value);

    i++;

    for(;i < n; i++) {
        bignum_t* temp_ptr;

        bignum_setzero(dst);
        bignum_mul_chunk(src, base_chunk, dst);

        // swap
        temp_ptr = src;
        src = dst;
        if(i + 1 == n) // if last iteration, set dst to bn (result)
            dst = bn;
        else
            dst = temp_ptr; // else just swap normally

        value = (bignum_chunk_t) __val_from_digit(str[i]);

        bignum_setzero(dst);
        bignum_add_chunk(src, value, dst);

        // swap again
        temp_ptr = src;
        src = dst;
        dst = temp_ptr;
    }

    bignum_cleanup(&tmp1);
    bignum_cleanup(&tmp2);
}
