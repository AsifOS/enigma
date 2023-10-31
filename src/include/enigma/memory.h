#ifndef __ENIGMA_MEMORY_H__
#define __ENIGMA_MEMORY_H__

#include <kint.h>

/* Memory map types. */

#define KERNEL_MEMORY_MAP_AVAILABLE    1
#define KERNEL_MEMORY_MAP_RESERVED     2
#define KERNEL_MEMORY_MAP_ACPI         3
#define KENREL_MEMORY_MAP_DEFECTIVE    4
#define KERNEL_MEMORY_MAP_INVALID      0

typedef struct __struct_kmmap_t {
    u32_t type;
#ifdef __enigma_i386
    u32_t addr;
    u32_t size;
#endif    // __enigma_$$ARCH$$
} kmmap_t;

#endif