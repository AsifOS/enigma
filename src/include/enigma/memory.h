#ifndef _ENIGMA_MEMORY_H
#define _ENIGMA_MEMORY_H

#include <kint.h>

/* Memory map types. */

#define ENIGMA_MEMORY_REGION_AVAILABLE    1
#define ENIGMA_MEMORY_REGION_RESERVED     2
#define ENIGMA_MEMORY_REGION_ACPI_RECL    3
#define ENIGMA_MEMORY_REGION_DEFECTIVE    4
#define ENIGMA_MEMORY_REGION_NVS          5
#define ENIGMA_MEMORY_REGION_INVALID      0

typedef struct __struct_kmmap_t {
    u32_t type;
#ifdef __enigma_i386
    u32_t addr;
    u32_t size;
#endif    // __enigma_$$ARCH$$
} kmmap_t;

#endif    // _ENIGMA_MEMORY_H