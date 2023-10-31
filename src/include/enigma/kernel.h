#ifndef __ENIGMA_H__
#define __ENIGMA_H__

#include <enigma/config.h>
#include <enigma/memory.h>

/* The information structure initially passed when the main kernel code
   is invoked. */

typedef struct kinfo_t {
    kmmap_t memmap[KERNEL_MAX_MEMMAP];
    u32_t   memmap_size;
} kinfo_t;

#endif    // __ENIGMA_H__