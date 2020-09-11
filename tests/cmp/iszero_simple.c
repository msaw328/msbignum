#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/cmp.h>

bignum_chunk_t data1[4] = { 0x0, 0x0, 0x0, 0x1 };
bignum_chunk_t data2[4] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffe };
bignum_chunk_t data3[3] = { 0x0, 0x0, 0x0 };

int main() {
    bignum_t bn1, bn2, bn3;

    bignum_fromdata(&bn1, data1, 4);
    bignum_fromdata(&bn2, data2, 4);
    bignum_fromdata(&bn3, data3, 3);

    if(bignum_iszero(&bn1)) return 1;
    if(bignum_iszero(&bn2)) return 2;
    if(!bignum_iszero(&bn3)) return 3;
}
