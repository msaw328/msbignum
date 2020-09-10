#include <string.h>

#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/arithmetic.h>

bignum_chunk_t a_data[2] = {
    0x55667788, 0x11223344
};

bignum_chunk_t n = 0x88224411;

bignum_chunk_t expected_result = 0x798f1449;

int main() {
    bignum_t a;
    bignum_chunk_t result = 0;
    bignum_fromdata(&a, a_data, 2);

    bignum_mod_chunk(&a, n, &result);

    if(result != expected_result) return 1;
}
