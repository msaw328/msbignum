#include <string.h>

#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/arithmetic.h>

bignum_chunk_t expected_result[2] = {
    0x00000000, 0x00000001 // 0xfffffffe + 2
};

int main() {
    bignum_t a, sum;
    bignum_fromchunk(&a, 0xfffffffe);
    bignum_init(&sum);

    bignum_add_chunk(&a, 2, &sum);

    return memcmp(sum.data, expected_result, sizeof(bignum_chunk_t) * 2);
}
