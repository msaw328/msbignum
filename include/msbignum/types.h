#ifndef _BIGNUM_API_TYPES_H_
#define _BIGNUM_API_TYPES_H_

// Types used by library - bignum itself as well as chunks it uses internally

#include <stdint.h>
#include <stddef.h>

// Type used for internal chunks of data (uint8_t, uint16_t, uint32_t etc)
typedef uint32_t bignum_chunk_t;

// Type used to safely perform operations that could overflow a normal chunk
// Should always have 2x the number of bits as bignum_chunk_t
typedef uint64_t bignum_chunksafe_t;

// The bignum datatype
struct bignum_t {
    bignum_chunk_t* data;   // pointer to raw data
    size_t allocated;       // number of chunks allocated
};
typedef struct bignum_t bignum_t;

#endif
