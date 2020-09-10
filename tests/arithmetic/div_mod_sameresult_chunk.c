#include <string.h>

#include <msbignum/types.h>
#include <msbignum/base.h>
#include <msbignum/arithmetic.h>

// bignum_div_chunk() should return same remainder as bignum_mod_chunk()

bignum_chunk_t a_data[3] = {
    0x11443322, 0x22334411, 0xffffffff
};

bignum_chunk_t n = 0x88224411;

int main() {
    bignum_t a;
    bignum_chunk_t result_mod = 0;
    bignum_chunk_t result_div = 0;

    bignum_fromdata(&a, a_data, 2);

    bignum_mod_chunk(&a, n, &result_mod);
    bignum_div_chunk(&a, n, NULL, &result_div);

    if(result_div != result_mod) return 1;
}
