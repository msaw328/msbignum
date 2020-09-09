#include "msbignum/types.h"

#include "internal/mem.h"

int bignum_cmp(bignum_t* a, bignum_t* b) {
    size_t a_used = __bignum_chunks_used(a);
    size_t b_used = __bignum_chunks_used(b);

    if(a_used > b_used) return 1;

    if(a_used < b_used) return -1;

    // else they have equal number of chunks, compare most significant chunk
    bignum_chunk_t a_msc = a->data[a_used - 1];
    bignum_chunk_t b_msc = b->data[a_used - 1];

    if(a_msc > b_msc) return 1;

    if(a_msc < b_msc) return -1;

    return 0;
}
