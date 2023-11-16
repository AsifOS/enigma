#ifndef _ENIGMA_GDT_H
#define _ENIGMA_GDT_H

#include <kint.h>
#include <ktype.h>

/* Each entry in the GDT. */
/* The GDT entry is one of the messiest shit. */

typedef struct __struct_gdt_entry_t {
    u16_t limit_low;            // Limit (bits 0-15)
    u16_t base_low;             // Base (bits 0-15)
    u8_t  base_high_lo;         // Base (bits 16-23)
    u8_t  access;               // The access byte
    u8_t  flags_x_limit;        // Flags and high 4-bits of limit
    u8_t  base_high_hi;         // Base (bits 24-31)

} __attribute__((packed)) gdt_entry_t;

typedef struct __struct_gdt_descriptor_t {
    u16_t  size;                // Size of the GDT
    data_t ptr;                 // Location of the table
} __attribute__((packed)) gdt_descriptor_t;

typedef enum __enum_gdt_access_e {
    GDT_ACCESS_CODE_READABLE         = 0x02,
    GDT_ACCESS_DATA_WRITABLE         = 0x02,

    GDT_ACCESS_CODE_CONFORMING       = 0x04,
    GDT_ACCESS_DATA_DIRECTION_NORMAL = 0x00,
    GDT_ACCESS_DATA_DIRECTION_DOWN   = 0x04,

    GDT_ACCESS_CODE_SEGMENT          = 0x18,
    GDT_ACCESS_DATA_SEGMENT          = 0x10,

    GDT_ACCESS_PRIVILEGE_RING0       = 0x00,
    GDT_ACCESS_PRIVILEGE_RING1       = 0x20,
    GDT_ACCESS_PRIVILEGE_RING2       = 0x40,
    GDT_ACCESS_PRIVILEGE_RING3       = 0x60,

    GDT_ACCESS_PRESENT               = 0x80
} gdt_access_e;

typedef enum __enum_gdt_flags_e {
    GDT_FLAGS_CODE_LONG      = 0x20,
    GDT_FLAGS_CODE_PROT      = 0x40,
    GDT_FLAGS_CODE_REAL      = 0x00,

    GDT_FLAGS_GRANULARITY_1B = 0x00,
    GDT_FLAGS_GRANULARITY_4K = 0x80
} gdt_flags_e;

#define GDT_LIMIT_LOW(limit)                (limit & 0xFFFF)
#define GDT_BASE_LOW(base)                  (base & 0xFFFF)
#define GDT_BASE_HIGH_LO(base)              ((base >> 0x10) & 0xFF)
#define GDT_FLAGS_LIMIT_HI(limit, flags)    (((flags) & 0xF0) | ((limit >> 0x10) & 0xF))
#define GDT_BASE_HIGH_HI(base)              ((base >> 0x18) & 0xFF)

#define GDT_ENTRY(base, limit, access, flags) {             \
    GDT_LIMIT_LOW(limit),                                   \
    GDT_BASE_LOW(base),                                     \
    GDT_BASE_HIGH_LO(base),                                 \
    access,                                                 \
    GDT_FLAGS_LIMIT_HI(limit, flags),                       \
    GDT_BASE_HIGH_HI(base)                                  \
}

/* Selector offset where our code segment will reside in the GDT. */

#define GDT_CODE_SEGMENT        0x08
#define GDT_DATA_SEGMENT        0x10

void gdt_init();

extern void gdt_load(data_t desc, u16_t code_seg, u16_t data_seg);

#endif     // _ENIGMA_GDT_H