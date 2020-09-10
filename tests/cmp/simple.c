#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/cmp.h>

bignum_chunk_t data1[4] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff };
bignum_chunk_t data2[4] = { 0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffe };
bignum_chunk_t data3[3] = { 0xffffffff, 0xffffffff, 0xffffffff };
bignum_chunk_t data4[4] = { 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff };

int main() {
    bignum_t bn1, bn2, bn3, bn4;

    bignum_fromdata(&bn1, data1, 4);
    bignum_fromdata(&bn2, data2, 4);
    bignum_fromdata(&bn3, data3, 3);
    bignum_fromdata(&bn4, data4, 4);

    // comparing most significant chunk
    if(!BIGNUM_EQ(&bn1, &bn1)) return 1;
    if(!BIGNUM_GT(&bn1, &bn2)) return 2;
    if(!BIGNUM_LT(&bn2, &bn1)) return 3;

    // comparing chunks used
    if(!BIGNUM_GT(&bn2, &bn3)) return 4;
    if(!BIGNUM_LT(&bn3, &bn2)) return 5;

    // check if bignum_cmp() stops on most significant chunk
    if(BIGNUM_EQ(&bn1, &bn4)) return 6;
}
