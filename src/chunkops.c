#include "msbignum/types.h"
#include "internal/defaults.h"

bignum_chunksafe_t __bignum_chunk_promote(bignum_chunk_t c) {
    return (bignum_chunksafe_t) c;
}

bignum_chunk_t __bignum_chunk_value_part(bignum_chunksafe_t cs) {
    return (bignum_chunk_t) (cs & BIGNUM_MAX_CHUNK);
}

bignum_chunk_t __bignum_chunk_carry_part(bignum_chunksafe_t cs) {
    cs = cs >> (sizeof(bignum_chunk_t) * 8);
    return (bignum_chunk_t) (cs & BIGNUM_MAX_CHUNK);
}
