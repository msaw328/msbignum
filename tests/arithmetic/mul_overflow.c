#include <string.h>

#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/arithmetic.h>

bignum_chunk_t expected_result[2] = {
    0x00000001, 0xfffffffe // 0xffffffff to 2nd power
};

int main() {
    bignum_t a, product;
    bignum_setchunk(&a, 0xffffffff);
    bignum_setzero(&product);

    bignum_mul(&a, &a, &product);

    return memcmp(product.data, expected_result, sizeof(bignum_chunk_t) * 2);
}
