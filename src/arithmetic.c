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

    size_t result_chunks_needed = a_used + 1; // +1 in case overflow happens

    if(b_used > a_used)
        result_chunks_needed = b_used + 1;

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

void bignum_add_chunk(bignum_t* a, bignum_chunk_t b, bignum_t* result) {
    // make sure result is big enough to hold data
    size_t result_chunks_needed = __bignum_chunks_used(a) + 1; // +1 in case overflow happens
    
    if(result->allocated < result_chunks_needed)
        __bignum_realloc(result, result_chunks_needed);
    
    // add stuff (we use b variable as carry)
    size_t i = 0;
    bignum_chunksafe_t op_result;
    while(b > 0) {
        op_result = __bignum_chunk_promote(a->data[i]);
        op_result = op_result + __bignum_chunk_promote(b);

        result->data[i] = __bignum_chunk_value_part(op_result);
        b = __bignum_chunk_carry_part(op_result);

        i++;
    }
    for(;i < a->allocated; i++) {
        result->data[i] = a->data[i];
    }

    DEBUG_DUMP_BIGNUM(result, "%s", "Bignum after add chunk");
}

void bignum_mul(bignum_t* a, bignum_t* b, bignum_t* result) {
    // make sure result is big enough to hold data
    size_t a_used = __bignum_chunks_used(a);
    size_t b_used = __bignum_chunks_used(b);
    size_t result_allocated = result->allocated;

    size_t result_chunks_needed = a_used + b_used;

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

            while(carry > 0 && result_index + 1 < result_allocated) {
                result_index++;

                sum = __bignum_chunk_promote(result->data[result_index]) + __bignum_chunk_promote(carry);

                result->data[result_index] = __bignum_chunk_value_part(sum);
                carry = __bignum_chunk_carry_part(sum);
            }
        }
    }

    DEBUG_DUMP_BIGNUM(result, "%s", "Bignum after mul");
}

void bignum_mul_chunk(bignum_t* a, bignum_chunk_t b, bignum_t* result) {
    // make sure result is big enough to hold data
    size_t a_used = __bignum_chunks_used(a);
    size_t result_chunks_needed = a_used + 1;

    if(result->allocated < result_chunks_needed)
        __bignum_realloc(result, result_chunks_needed);

    for(size_t i = 0; i < a_used; i++) {
        size_t result_index = i;

        bignum_chunksafe_t product = __bignum_chunk_promote(a->data[i]) * __bignum_chunk_promote(b);
        bignum_chunksafe_t sum = __bignum_chunk_promote(result->data[result_index]) + product;

        result->data[result_index] = __bignum_chunk_value_part(sum);

        bignum_chunk_t carry = __bignum_chunk_carry_part(sum);

        while(carry > 0 && result_index + 1 < result->allocated) {
            result_index++;

            sum = __bignum_chunk_promote(result->data[result_index]) + __bignum_chunk_promote(carry);

            result->data[result_index] = __bignum_chunk_value_part(sum);
            carry = __bignum_chunk_carry_part(sum);
        }
    }

    DEBUG_DUMP_BIGNUM(result, "%s", "Bignum after mul chunk");
}

void bignum_mod_chunk(bignum_t* a, bignum_chunk_t n, bignum_chunk_t* result) {
    bignum_chunksafe_t multiplier = 1;
    bignum_chunksafe_t result_safe = 0;
    bignum_chunksafe_t mul_step = (((bignum_chunksafe_t) BIGNUM_MAX_CHUNK) + 1) % n;

    for(unsigned int i = 0; i < a->allocated; i++) {
        bignum_chunk_t chunk = a->data[i];

        result_safe += (multiplier * chunk) % n;

        multiplier = (multiplier * mul_step) % n;
    }

    *result = __bignum_chunk_value_part(result_safe);
}

void bignum_div_chunk(bignum_t* a, bignum_chunk_t n, bignum_t* quotient, bignum_chunk_t* remainder) {
    if(quotient == NULL && remainder == NULL) return;

    // make sure quotient is big enough to hold data
    size_t a_used = __bignum_chunks_used(a);
    size_t quotient_chunks_needed = a_used;

    if(quotient != NULL && quotient->allocated < quotient_chunks_needed)
        __bignum_realloc(quotient, quotient_chunks_needed);

    // since n is 1 chunk in size it means remainder wont be bigger than 1 chunk
    // so as long as there's ANY memory allocated for remainder->data then we're ok no need to check

    bignum_chunksafe_t safe_n = __bignum_chunk_promote(n);
    bignum_chunk_t borrow = 0;

    // long division
    for(int i = a_used - 1; i >= 0; i--) { // start from last chunk (digit)
        bignum_chunksafe_t chunk_with_borrow = __bignum_chunk_promote_withborrow(a->data[i], borrow);
        
        if(quotient != NULL)
            quotient->data[i] = __bignum_chunk_value_part(chunk_with_borrow / safe_n);
        
        borrow = __bignum_chunk_value_part(chunk_with_borrow % safe_n);
    }

    if(quotient != NULL) {
        DEBUG_DUMP_BIGNUM(quotient, "%s", "Quotient after div chunk");
    }

    if(remainder != NULL)
        *remainder = borrow;
}
