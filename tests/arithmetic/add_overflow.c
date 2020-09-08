#include <string.h>

#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/arithmetic.h>

bignum_chunk_t expected_result[2] = {
    0xfffffffe, 0x00000001 // 0xffffffff times two
};

int main() {
    bignum_t a, sum;
    bignum_setchunk(&a, 0xffffffff);
    bignum_setzero(&sum);

    bignum_add(&a, &a, &sum);

    return memcmp(sum.data, expected_result, sizeof(bignum_chunk_t) * 2);
}
