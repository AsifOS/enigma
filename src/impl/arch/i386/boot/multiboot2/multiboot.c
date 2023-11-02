#include <enigma/kernel.h>
#include <multiboot2.h>
#include <kint.h>
#include <kmem.h>
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

/* Extract data from info. structure provided by the bootloader. */

static void mbi_extract(kinfo_t *info, mbi_tag_t *tag) {
    /* We are not interested in the header. */
    for(tag = (mbi_tag_t*) (tag + 8);
        tag -> type != MULTIBOOT_TAG_TYPE_END;
        /* The info. structure is 8-byte aligned, but not the given size. */
        tag += (tag -> size + 0x07) & ~0x07) 
    {
        switch(tag -> type) {
            case MULTIBOOT_TAG_TYPE_MMAP: {
                mbi_tag_mmap_t *mmap = (mbi_tag_mmap_t*) tag;

                for(mbi_mmap_entry_t *entry = mmap -> entries; 
                    (data_t) entry < (data_t) (tag + tag -> size);
                    entry += mmap -> entry_size) 
                {
                   __mb_error("Yeoo");
                    kmmap_t kmmap;

                    /* We are in 32-bit mode, where total addressing space 
                       is only 4GB. Map them as invalid. */
                    
                    if(entry -> addr >= 0xFFFFFFFF || 
                       entry -> len  >= 0xFFFFFFFF) 
                    {
                        kmmap.type = ENIGMA_MEMORY_REGION_INVALID;
                    } else kmmap.type = entry -> type;  /* 1:1 type mapping. */

                    /* Rest assured the 'addr' and 'size' fields are 
                       going to be 32-bit. */

                    kmmap.addr = (u32_t) entry -> addr;
                    kmmap.size = (u32_t) entry -> len;

                    /* Insert the map into the kernel info. */

                    if(info -> mmap_size < ENIGMA_MAX_MMAP) 
                        info -> mmap[info -> mmap_size++] = kmmap;
                }
            } break;
        }
    }
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

    /* Zero out the structure. */

    kmemsetw(&g_kinfo, 0, sizeof(g_kinfo));

    res = &g_kinfo;

    /* Extract the boot informations. */

    mbi_extract(res, (mbi_tag_t*) addr);

out: 
    return res;
}