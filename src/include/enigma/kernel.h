#ifndef _ENIGMA_KERNEL_H
#define _ENIGMA_KERNEL_H

#include <enigma/config.h>
#include <enigma/memory.h>
#include <ktype.h>

/* The information structure initially passed when the main kernel code
   is invoked. */

typedef struct kinfo {
    /* Memory mapping of the RAM. */

    kmmap_t mmap[ENIGMA_MAX_MMAP];
    u32_t   mmap_size;

    /* Base physical address where the image was loaded. */

    data_t  load_base_addr;

    /* Bootloader name the kernel got booted with. */

    u8_t    bl_name[ENIGMA_BOOTLOADER_NAME_MAX_LENGTH];
} kinfo_t;

/* The arch-independent kernel entry point. */

void main(kinfo_t *info);

#endif    // _ENIGMA_KERNEL_H
