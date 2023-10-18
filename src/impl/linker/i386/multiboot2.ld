/**
 * Linkerscript if using Multiboot2 specification for boot.
 */

/** The entry point to the kernel. */

ENTRY(kinit)

/** Output format. */

OUTPUT_FORMAT(elf32-i386)

/** Sections. */

SECTIONS {
    /* We are going to load our kernel after 1MB of memory, which is in 
       address 0x100000 . */
    
    . = 1M;

    /** .boot section where we keep our boot specific codes, in our case
        the multiboot2 header. */

    .boot : ALIGN(4K) {
        *(.multiboot)
        *(.boot)
    }

    /* .text section holding pure C code. */

    .text : ALIGN(4K) {
        *(.text)
    }

    /* .rodata section to store read-only data. */

    .rodata : ALIGN(4K) {
        *(.rodata)
    }

    /* .data section for initialized data. */

    .data : ALIGN(4K) {
        *(.data)
    }

    /* .bss section for uninitialized data. */

    .bss : ALIGN(4K) {
        *(.bss)
    }

    /** Finally .asm section to store all our assembly code. */

    .asm : ALIGN(4K) {
        *(.asm)
    }
}