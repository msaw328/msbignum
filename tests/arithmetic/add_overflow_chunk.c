#include <string.h>

#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/arithmetic.h>

bignum_chunk_t data1[1] = {
    0xfffffffe
};

bignum_chunk_t data2[2] = {
    0x91c0a932, 0x9
};

bignum_chunk_t expected_result1[2] = {
    0x00000000, 0x00000001 // 0xfffffffe + 2
};

bignum_chunk_t expected_result2[2] = {
    0x91c0a93a, 0x9
};

int main() {
    bignum_t bn1, bn2, sum1, sum2;
    bignum_fromdata(&bn1, data1, 1);
    bignum_fromdata(&bn2, data2, 2);
    bignum_init(&sum1);
    bignum_init(&sum2);

    bignum_add_chunk(&bn1, 2, &sum1);

    if(memcmp(sum1.data, expected_result1, sizeof(bignum_chunk_t) * 2) != 0) return 1;

    bignum_add_chunk(&bn2, 8, &sum2);

    if(memcmp(sum2.data, expected_result2, sizeof(bignum_chunk_t) * 2) != 0) return 2;
}
