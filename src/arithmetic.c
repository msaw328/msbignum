#include "msbignum/types.h"

#include "internal/mem.h"
#include "internal/defaults.h"
#include "internal/debug.h"
#include "internal/chunkops.h"

void bignum_add(bignum_t* a, bignum_t* b, bignum_t* result) {
    // make sure result is big enough to hold data
    size_t a_used = __bignum_chunks_used(a);
    size_t b_used = __bignum_chunks_used(b);
    size_t result_allocated = result->allocated;

    size_t result_chunks_needed = a_used + BIGNUM_DEFAULT_EXCESS;

    if(b_used > a_used)
        result_chunks_needed = b_used + BIGNUM_DEFAULT_EXCESS;

    if(result_allocated < result_chunks_needed)
        __bignum_realloc(result, result_chunks_needed);

    // add stuff
    bignum_chunk_t carry = 0;

    for(size_t i = 0; i < result_chunks_needed; i++) {
        bignum_chunksafe_t accumulator = __bignum_chunk_promote(a->data[i]);
        bignum_chunksafe_t addition = __bignum_chunk_promote(b->data[i]);

        accumulator = accumulator + addition + __bignum_chunk_promote(carry);

        result->data[i] = __bignum_chunk_value_part(accumulator);
        carry = __bignum_chunk_carry_part(accumulator);
    }

    DEBUG_DUMP_BIGNUM(result, "%s", "Bignum after add");
}

void bignum_mul(bignum_t* a, bignum_t* b, bignum_t* result) {
    // make sure result is big enough to hold data
    size_t a_used = __bignum_chunks_used(a);
    size_t b_used = __bignum_chunks_used(b);
    size_t result_allocated = result->allocated;

    size_t result_chunks_needed = a_used + b_used + BIGNUM_DEFAULT_EXCESS;

    if(result_allocated < result_chunks_needed)
        __bignum_realloc(result, result_chunks_needed);

    // multiply
    for(size_t i = 0; i < a_used; i++) {
        for(size_t j = 0; j < b_used; j++) {
            size_t result_index = i + j;

            bignum_chunksafe_t product = __bignum_chunk_promote(a->data[i]) * __bignum_chunk_promote(b->data[j]);
            bignum_chunksafe_t sum = __bignum_chunk_promote(result->data[result_index]) + product;

            result->data[result_index] = __bignum_chunk_value_part(sum);

            bignum_chunk_t carry = __bignum_chunk_carry_part(sum);

            while(carry > 0 && result_index < result_allocated) {
                result_index++;

                sum = __bignum_chunk_promote(result->data[result_index]) + __bignum_chunk_promote(carry);

                result->data[result_index] = __bignum_chunk_value_part(sum);
                carry = __bignum_chunk_carry_part(sum);
            }
        }
    }

    DEBUG_DUMP_BIGNUM(result, "%s", "Bignum after mul");
}
