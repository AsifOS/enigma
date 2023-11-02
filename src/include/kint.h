#ifndef _ENIGMA_KINT_H
#define _ENIGMA_KINT_H

#ifdef __enigma_i386
/* Signed type definitions. */

typedef signed long long i64_t;
typedef signed int       i32_t;
typedef signed short     i16_t;
typedef signed char      i8_t;

/* Unsigned type definitions. */

typedef unsigned long long u64_t;
typedef unsigned int       u32_t;
typedef unsigned short     u16_t;
typedef unsigned char      u8_t;
#endif    // __enigma_$$ARCH$$

#endif    // _ENIGMA_KINT_H