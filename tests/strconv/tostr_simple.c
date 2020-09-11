#include <string.h>
#include <stdio.h>
#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/strconv.h>

bignum_chunk_t data1[4] = {
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
};

bignum_chunk_t data2[16] = {
    0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x11111111, 0x11111111, 0x11111111, 0x11111111,
    0x44444444, 0x44444444, 0x44444444, 0x44444444, 0x55555555, 0x55555555, 0x55555555, 0x55555555
};

char* expected_result1 = "340282366920938463463374607431768211455";
char* expected_result2 = "4469269309980865699858008332735282042490495139784371493960368545233911769104153851231412939705353208806059167029158533177099674616747869905589461493743615";

int base = 10;

int main() {
    bignum_t bn1, bn2;
    bignum_fromdata(&bn1, data1, 4);
    bignum_fromdata(&bn2, data2, 16);

    char buf1[40] = { 0 };

    bignum_tostr(&bn1, base, buf1);

    if(strncmp(buf1, expected_result1, 39) != 0) return 1;

    char buf2[156] = { 0 };

    bignum_tostr(&bn2, base, buf2);

    if(strncmp(buf2, expected_result2, 155) != 0) return 2;
}
