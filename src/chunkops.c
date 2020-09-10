#include "msbignum/types.h"
#include "internal/defaults.h"

#define BITSHIFT (sizeof(bignum_chunk_t) * 8)

bignum_chunksafe_t __bignum_chunk_promote(bignum_chunk_t c) {
    return (bignum_chunksafe_t) c;
}

bignum_chunksafe_t __bignum_chunk_promote_withborrow(bignum_chunk_t c, bignum_chunk_t borrow) {
    return (((bignum_chunksafe_t) borrow) << BITSHIFT) | (bignum_chunksafe_t) c;
}

bignum_chunk_t __bignum_chunk_value_part(bignum_chunksafe_t cs) {
    return (bignum_chunk_t) (cs & BIGNUM_MAX_CHUNK);
}

bignum_chunk_t __bignum_chunk_carry_part(bignum_chunksafe_t cs) {
    cs = cs >> BITSHIFT;
    return (bignum_chunk_t) (cs & BIGNUM_MAX_CHUNK);
}
