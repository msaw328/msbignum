#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "msbignum/types.h"

#include "internal/defaults.h"
#include "internal/debug.h"

void bignum_setzero(bignum_t* bn) {
    bn->data = malloc(BIGNUM_DEFAULT_CHUNKS * sizeof(bignum_chunk_t));

    memset(bn->data, 0, BIGNUM_DEFAULT_CHUNKS * sizeof(bignum_chunk_t));

    bn->allocated = BIGNUM_DEFAULT_CHUNKS;

    DEBUG_DUMP_BIGNUM(bn, "%s", "Bignum set to zero");
}

void bignum_setchunk(bignum_t* bn, bignum_chunk_t value) {
    bn->data = malloc(BIGNUM_DEFAULT_CHUNKS * sizeof(bignum_chunk_t));

    memset(bn->data, 0, BIGNUM_DEFAULT_CHUNKS * sizeof(bignum_chunk_t));

    bn->data[0] = value;

    bn->allocated = BIGNUM_DEFAULT_CHUNKS;

    DEBUG_DUMP_BIGNUM(bn, "Bignum set to %u", value);
}

void bignum_clone(bignum_t* src, bignum_t* dst) {
    dst->data = malloc(sizeof(bignum_chunk_t) * src->allocated);
    memcpy(dst->data, src->data, sizeof(bignum_chunk_t) * src->allocated);

    dst->allocated = src->allocated;

    DEBUG_DUMP_BIGNUM(dst, "%s", "Bignum cloned to dst");
}

void bignum_cleanup(bignum_t* bn) {
    free(bn->data);
    bn->allocated = 0;

    DEBUG_DUMP_BIGNUM(bn, "%s", "Bignum destroyed");
}
