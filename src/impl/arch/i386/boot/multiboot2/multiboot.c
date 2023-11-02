#include <enigma/kernel.h>
#include <multiboot2.h>
#include <kint.h>
#include <ktype.h>

/* This is where we store the kernel info. */

kinfo_t g_kinfo;

/* Prints a error message to the VGA output. It is okay to write it to the 
   VGA output as no other output mode is available at early boot time. */

static void __mb_error(const char *str) {
    u16_t *vid_mem = (u16_t*) 0xB8000;

    while(*str) 
        *vid_mem++ = (u16_t) (0x4f << 8) | *str++;
}

static void mbi_extract(kinfo_t *info, mbi_tag_t *tag) {
    info += 0;
    tag++;
}

kinfo_t *mb_main(u32_t magic, u32_t addr) {
    kinfo_t *res = nullptr;

    /* Check for Multiboot2 compliant bootloader. */

    if(magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        __mb_error("Kernel not invoked with a Multiboot2 "
                   "compliant bootloader. Abort!");
        
        goto out;
    }

    /* The info structure must be 8 byte aligned. */
    /* Check for last 3-bits. */

    if(addr & 0x07) {
        __mb_error("Multiboot2 information structure is not "
                   "8-byte aligned. Abort!");
        
        goto out;
    }

    res = &g_kinfo;

    /* Extract the boot informations. */

    mbi_extract(res, (mbi_tag_t*) addr);

out: 
    return res;
}