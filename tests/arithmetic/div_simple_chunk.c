#include <string.h>

#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/arithmetic.h>

// input
bignum_chunk_t data[3] = {
    0xffffffff, 0x11111111, 0xffffffff // some random number
};

bignum_chunk_t n = 0xffff1111;

// expected output
bignum_chunk_t expected_quotient[3] = {
    0xf0124555, 0x0000eeee, 0x1
};

bignum_chunk_t expected_remainder = 0x1d83c05a;

int main() {
    bignum_t a, quotient;
    bignum_chunk_t remainder;

    bignum_fromdata(&a, data, 3);
    bignum_init(&quotient);

    // test all usages
    bignum_div_chunk(&a, n, NULL, NULL);

    bignum_div_chunk(&a, n, &quotient, &remainder);
    
    if(memcmp(quotient.data, expected_quotient, sizeof(bignum_chunk_t) * 3) != 0 || remainder != expected_remainder)
        return 1;

    bignum_setzero(&quotient);

    bignum_div_chunk(&a, n, &quotient, NULL);

    if(memcmp(quotient.data, expected_quotient, sizeof(bignum_chunk_t) * 3) != 0)
        return 2;

    remainder = 0;

    bignum_div_chunk(&a, n, NULL, &remainder);

    if(remainder != expected_remainder)
        return 2;

    return 0;
}
