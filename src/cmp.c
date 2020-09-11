#include <string.h>

#include "msbignum/types.h"

#include "internal/mem.h"

int bignum_cmp(bignum_t* a, bignum_t* b) {
    size_t a_used = __bignum_chunks_used(a);
    size_t b_used = __bignum_chunks_used(b);

    if(a_used > b_used) return 1;

    if(a_used < b_used) return -1;

    // else they have equal number of chunks, compare most significant chunk
    return memcmp(a->data, b->data, sizeof(bignum_chunk_t) * a_used);
}

int bignum_iszero(bignum_t* bn) {
    return __bignum_chunks_used(bn) == 0;
}
