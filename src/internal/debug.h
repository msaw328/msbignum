#ifndef _BIGNUM_DEBUG_H_
#define _BIGNUM_DEBUG_H_

#include <stdio.h>
#include <stdint.h>

#include "msbignum/types.h"

#ifdef BIGNUM_DEBUG
    #define DEBUG_DUMP_BIGNUM(bignum_ptr, info_fmt, ...) \
        do { \
            fprintf(stderr, "%s(): " info_fmt "\n", __func__, __VA_ARGS__); \
            fflush(stderr); \
            fprintf(stderr, "allocated: %lu\n", (bignum_ptr)->allocated); \
            fflush(stderr); \
            fprintf(stderr, "data: "); \
            for(int j = (bignum_ptr)->allocated * sizeof(bignum_chunk_t) - 1; j >= 0; j--) { \
                fprintf(stderr, "%02x", ((uint8_t*) ((bignum_ptr)->data))[j]); \
            } \
            fflush(stderr); \
            fprintf(stderr, "%s\n", ""); \
            fflush(stderr); \
        } while (0);
#else
    #define DEBUG_DUMP_BIGNUM(bignum_ptr, info_fmt, ...) do {} while(0);
#endif

#endif
