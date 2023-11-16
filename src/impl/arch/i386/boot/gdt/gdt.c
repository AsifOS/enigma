#include <gdt.h>

/* This is where we store our GDT. */

static gdt_entry_t g_gdt[] = {
    /* Null entry. */

    GDT_ENTRY(0, 0, 0, 0),

    /* Kernel 32-bit code segment. */

    GDT_ENTRY(0, 0xFFFFF, GDT_ACCESS_CODE_SEGMENT | GDT_ACCESS_CODE_READABLE 
        | GDT_ACCESS_PRIVILEGE_RING0 | GDT_ACCESS_PRESENT, 
        GDT_FLAGS_CODE_PROT | GDT_FLAGS_GRANULARITY_4K),
    
    /* Kernel 32-bi data segment. */

    GDT_ENTRY(0, 0xFFFFF, GDT_ACCESS_DATA_SEGMENT | GDT_ACCESS_DATA_WRITABLE
        | GDT_ACCESS_PRIVILEGE_RING0 | GDT_ACCESS_PRESENT, 
        GDT_FLAGS_CODE_PROT | GDT_FLAGS_GRANULARITY_4K)
};

static gdt_descriptor_t g_desc = { sizeof(g_gdt) - 1, &g_gdt };

void gdt_init() {
    /* Now load the GDT and set all the necessary segment registers. */

    gdt_load(&g_desc, GDT_CODE_SEGMENT, GDT_DATA_SEGMENT);
}