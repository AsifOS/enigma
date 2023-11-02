#ifndef _ENIGMA_KERNEL_H
#define _ENIGMA_KERNEL_H

#include <enigma/config.h>
#include <enigma/memory.h>

/* The information structure initially passed when the main kernel code
   is invoked. */

typedef struct kinfo_t {
    kmmap_t mmap[ENIGMA_MAX_MMAP];
    u32_t   mmap_size;
} kinfo_t;

#endif    // _ENIGMA_KERNEL__H