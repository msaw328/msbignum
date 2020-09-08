#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "msbignum/types.h"

#include "internal/debug.h"

void __bignum_realloc(bignum_t* bn, size_t nchunks) {
    size_t nbytes = sizeof(bignum_chunk_t) * nchunks;
    size_t abytes = sizeof(bignum_chunk_t) * bn->allocated;

    bignum_chunk_t* new_data = malloc(nbytes);

    size_t move_bytes = nbytes;
    if(nbytes > abytes)
        move_bytes = abytes;

    memcpy(new_data, bn->data, move_bytes);

    free(bn->data);
    bn->data = new_data;
    bn->allocated = nchunks;

    DEBUG_DUMP_BIGNUM(bn, "%s", "Bignum after REALLOC");
}

size_t __bignum_chunks_used(bignum_t* bn) {
    size_t counter = 0;
    for(unsigned int i = 0; i < bn->allocated; i++) {
        if(bn->data[i] != 0)
            counter = i + 1;
    }

    return counter;
}
