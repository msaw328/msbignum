#include <string.h>

#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/strconv.h>

char* string = "112233445566778899887766554433221122334455667788998877665544332211";

bignum_chunk_t expected_result1[6] = {
    0x9a397fc4, 0xfd6af1c6, 0xb5e4f151, 0xbb8cf4e9, 0xeeb192ee, 0x000002ff
};

size_t n1 = 52;

bignum_chunk_t expected_result2[7] = {
    0x6e8763b3, 0xfa3a33a0, 0x82c1452a, 0xb5214f94, 0xeb208328, 0x6dd93c06, 0x0110d30b
};

size_t n2 = 0;

int base = 10;

int main() {
    bignum_t bn1, bn2;
    bignum_init(&bn1);
    bignum_init(&bn2);

    bignum_setstr(&bn1, base, string, n1);

    if(memcmp(bn1.data, expected_result1, sizeof(bignum_chunk_t) * 6) != 0) return 1;

    bignum_setstr(&bn2, base, string, n2);

    if(memcmp(bn2.data, expected_result2, sizeof(bignum_chunk_t) * 7) != 0) return 2;
}
