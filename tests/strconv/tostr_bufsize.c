#include <stddef.h>

#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/strconv.h>

bignum_chunk_t data1[4] = {
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
};

bignum_chunk_t data2[8] = {
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
};

bignum_chunk_t data3[3] = {
    0x0, 0x0, 0x0
};

int base = 10;

size_t expected_length1 = 39;

size_t expected_length2 = 78;

size_t expected_length3 = 1;

int main() {
    bignum_t bn1, bn2, bn3;

    bignum_fromdata(&bn1, data1, 4);
    bignum_fromdata(&bn2, data2, 8);
    bignum_fromdata(&bn3, data3, 3);

    size_t length = bignum_tostr_bufsize(&bn1, base);

    if(length < expected_length1) return 1;

    if(length - expected_length1 > 3) return 2;

    length = bignum_tostr_bufsize(&bn2, base);

    if(length < expected_length2) return 3;

    if(length - expected_length2 > 3) return 4;

    length = bignum_tostr_bufsize(&bn3, base);

    if(length < expected_length3) return 5;

    if(length - expected_length3 > 3) return 6;
    
    return 0;
}
