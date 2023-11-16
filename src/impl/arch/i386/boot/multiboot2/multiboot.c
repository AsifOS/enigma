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
    u16_t *vid_mem = (u16_t *) 0xB8000;

    while(*str) 
        *vid_mem++ = (u16_t) (0x4f << 8) | *str++;
}

/* Extract data from info. structure provided by the bootloader. */

static void mbi_extract(kinfo_t *info, mbi_tag_t *tag) {
    /* We are not interested in the header. */
    for(; tag -> type != MULTIBOOT_TAG_TYPE_END;
        /* The info. structure is 8-byte aligned, but not the given size. */
        tag = (mbi_tag_t *) ((u8_t *) tag + ((tag -> size + 0x07) & ~0x07)))
    {
        switch(tag -> type) {
            case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME: {
                mbi_tag_string_t *name = (mbi_tag_string_t *) tag;

                (void) kstrcpy(info -> bl_name, name -> string);
            } break;

            case MULTIBOOT_TAG_TYPE_MMAP: {
                mbi_tag_mmap_t *mmap = (mbi_tag_mmap_t *) tag;

                for(mbi_mmap_entry_t *entry = mmap -> entries; 
                    (u8_t *) entry < (u8_t *) tag + tag -> size;
                    entry = (mbi_mmap_entry_t *) ((u8_t *) entry + mmap -> entry_size)) 
                {
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

            case MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR: {
                mbi_tag_load_base_addr_t *addr = 
                    (mbi_tag_load_base_addr_t *) tag;
                
                /* Now we have the base address where the kernel image was 
                   loaded. */

                info -> load_base_addr = (data_t) addr -> load_base_addr;
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

    g_kinfo.load_base_addr = (data_t) 100;

    /* Zero out the structure. */

    (void) kmemsetz(&g_kinfo, sizeof(g_kinfo));

    res = &g_kinfo;

    /* Extract the boot informations. We are not interested in the header.*/

    mbi_extract(res, (mbi_tag_t *) (addr + 8));

out: 
    return res;
}