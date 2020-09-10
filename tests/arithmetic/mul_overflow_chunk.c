#include <string.h>

#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/arithmetic.h>

bignum_chunk_t expected_result[2] = {
    0x00000001, 0xfffffffe // 0xffffffff to 2nd power
};

int main() {
    bignum_t a, product;
    bignum_fromchunk(&a, 0xffffffff);
    bignum_init(&product);

    bignum_mul_chunk(&a, 0xffffffff, &product);

    return memcmp(product.data, expected_result, sizeof(bignum_chunk_t) * 2);
}
