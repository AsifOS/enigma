#ifndef ENIGMA_MULTIBOOT2_H
#define ENIGMA_MULTIBOOT2_H

/*  How many bytes from the start of the file the header is searched. */

#define MULTIBOOT_SEARCH                        32768        // 32KB
#define MULTIBOOT_HEADER_ALIGN                  8

/*  The magic number Multiboot2 compliant header should contain. */

#define MULTIBOOT2_HEADER_MAGIC                 0xE85250D6

/*  This should be in EAX after invoked by a bootloader. */

#define MULTIBOOT2_BOOTLOADER_MAGIC             0x36D76289

/*  Alignment of multiboot modules. */

#define MULTIBOOT_MOD_ALIGN                     0x00001000

/*  Alignment of the multiboot info structure. */

#define MULTIBOOT_INFO_ALIGN                    0x00000008

/* Multiboot2 header tag types. They are the tags defined in the header. */

#define MULTIBOOT_HEADER_TAG_END                                0
#define MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST                1
#define MULTIBOOT_HEADER_TAG_ADDRESS                            2
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS                      3
#define MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS                      4
#define MULTIBOOT_HEADER_TAG_FRAMEBUFFER                        5
#define MULTIBOOT_HEADER_TAG_MODULE_ALIGN                       6
#define MULTIBOOT_HEADER_TAG_EFI_BS                             7
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI32                8
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI64                9
#define MULTIBOOT_HEADER_TAG_RELOCATABLE                        10

/* Multiboot2 tag alignment. */

#define MULTIBOOT_TAG_ALIGN                  8

/* Multiboot2 information structure tag types. */

#define MULTIBOOT_TAG_TYPE_END               0
#define MULTIBOOT_TAG_TYPE_CMDLINE           1
#define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME  2
#define MULTIBOOT_TAG_TYPE_MODULE            3
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO     4
#define MULTIBOOT_TAG_TYPE_BOOTDEV           5
#define MULTIBOOT_TAG_TYPE_MMAP              6
#define MULTIBOOT_TAG_TYPE_VBE               7
#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER       8
#define MULTIBOOT_TAG_TYPE_ELF_SECTIONS      9
#define MULTIBOOT_TAG_TYPE_APM               10
#define MULTIBOOT_TAG_TYPE_EFI32             11
#define MULTIBOOT_TAG_TYPE_EFI64             12
#define MULTIBOOT_TAG_TYPE_SMBIOS            13
#define MULTIBOOT_TAG_TYPE_ACPI_OLD          14
#define MULTIBOOT_TAG_TYPE_ACPI_NEW          15
#define MULTIBOOT_TAG_TYPE_NETWORK           16
#define MULTIBOOT_TAG_TYPE_EFI_MMAP          17
#define MULTIBOOT_TAG_TYPE_EFI_BS            18
#define MULTIBOOT_TAG_TYPE_EFI32_IH          19
#define MULTIBOOT_TAG_TYPE_EFI64_IH          20
#define MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR    21

/*  Multiboot2 architecture. */

#define MULTIBOOT_ARCHITECTURE_I386    0
#define MULTIBOOT_ARCHITECTURE_MIPS32  4

/* Optional field for header tag flags. */

#define MULTIBOOT_HEADER_TAG_OPTIONAL  1

#include <kint.h>

/* The Multiboot2 header structure. */

typedef struct __struct_mb_header_t {
    /* Multiboot2 magic. Can be kernel or bootloader magic depending on 
       the use case. */
    
    u32_t magic;

    /* ISA. */

    u32_t arch;

    /* The total header length (excluding tags). */

    u32_t length;

    /* Checksum. This field plus the previous fields of the header modulo 
       2 ^ 32 must equal to 0. */
    
    u32_t checksum;
} mb_header_t;

/* Multiboot2 header tag. */

/* Default header tag structure. */

typedef struct __struct_mb_header_tag_t {
    u16_t type;
    u16_t field;
    u32_t size;
} mb_header_tag_t;

typedef struct __struct_mb_header_tag_info_req_t {
    mb_header_tag_t tag;
    u32_t requests[0];
} mb_header_tag_info_req_t;

typedef struct __struct_mb_header_tag_address_t {
    mb_header_tag_t tag;
    u32_t header_addr;
    u32_t load_addr;
    u32_t load_end_addr;
    u32_t bss_end_addr;
} mb_header_tag_address_t;

typedef struct __struct_mb_header_tag_entry_address_t {
    mb_header_tag_t tag;
    u32_t entry_addr;
} mb_header_tag_entry_address_t;

typedef struct __struct_mb_header_tag_con_flags_t {
    mb_header_tag_t tag;
    u32_t con_flags;
} mb_header_tag_con_flags_t;

typedef struct __struct_mb_header_tag_fb_t {
    mb_header_tag_t tag;
    u32_t width;
    u32_t height;
    u32_t depth;
} mb_header_tag_fb_t;

typedef struct __struct_mb_header_tag_mod_align_t {
    mb_header_tag_t tag;
} mb_header_tag_mod_align_t;

typedef struct __struct_mb_header_tag_reloc_t {
    mb_header_tag_t tag;
    u32_t min_addr;
    u32_t max_addr;
    u32_t align;
    u32_t preference;
} mb_header_tag_reloc_t;

/* Multiboot2 information structure. */

typedef struct __struct_mbi_tag_t {
    u32_t type;
    u32_t size;
} mbi_tag_t;

typedef struct __struct_mbi_tag_string_t {
    mbi_tag_t tag;
    u8_t string[0];
} mbi_tag_string_t;

typedef struct __struct_mb_tag_mod_t {
    mbi_tag_t tag;
    u32_t mod_start;
    u32_t mod_end;
    u8_t  cmdline[0];
} mb_tag_mod_t;

typedef struct __struct_mbi_tag_basic_meminfo_t {
    mbi_tag_t tag;
    u32_t mem_lower;
    u32_t mem_upper;
} mbi_tag_basic_meminfo_t;

typedef struct __struct_mbi_tag_bootdev_t {
    mbi_tag_t tag;
    u32_t biosdev;
    u32_t slice;
    u32_t part;
} mbi_tag_bootdev_t;

/* Memory map entry type. */

#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE       3
#define MULTIBOOT_MEMORY_NVS                    4
#define MULTIBOOT_MEMORY_BADRAM                 5

/* Memory map entry structure. */

typedef struct __struct_mbi_mmap_entry_t {
    u64_t addr;
    u64_t len;
    u32_t type;
    u32_t reserved;
} mbi_mmap_entry_t;

typedef struct __struct_mbi_tag_mmap_t {
    mbi_tag_t tag;
    u32_t entry_size;
    u32_t entry_version;
    mbi_mmap_entry_t entries[0];  
} mbi_tag_mmap_t;

typedef struct __struct_mbi_vbe_info_block_t {
    u8_t external_specification[512];
} mbi_vbe_info_block_t;

typedef struct __struct_mbi_vbe_mode_info_block_t {
    u8_t external_specification[256];
} mbi_vbe_mode_info_block_t;

typedef struct __struct_mbi_tag_vbe_t {
    mbi_tag_t tag;

    u16_t vbe_mode;
    u16_t vbe_interface_seg;
    u16_t vbe_interface_off;
    u16_t vbe_interface_len;

    mbi_vbe_info_block_t vbe_control_info;
    mbi_vbe_mode_info_block_t vbe_mode_info;
} mbi_tag_vbe_t;

/* Framebuffer common tag structure. */

#define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED      0
#define MULTIBOOT_FRAMEBUFFER_TYPE_RGB          1
#define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT     2

typedef struct __struct_mbi_tag_fb_comm_t {
    mbi_tag_t tag;

    u64_t framebuffer_addr;
    u32_t framebuffer_pitch;
    u32_t framebuffer_width;
    u32_t framebuffer_height;
    u8_t  framebuffer_bpp;
    u8_t  framebuffer_type;
    u16_t reserved;
} mbi_tag_fb_comm_t;

typedef struct __struct_mb_color_t {
    u8_t red;
    u8_t green;
    u8_t blue;
} mb_color_t;

typedef struct __struct_mbi_tag_fb_t {
  mbi_tag_fb_comm_t common;

    union {
        struct {
            u16_t framebuffer_palette_num_colors;
            mb_color_t framebuffer_palette[0];
        };

        struct {
            u8_t framebuffer_red_field_position;
            u8_t framebuffer_red_mask_size;
            u8_t framebuffer_green_field_position;
            u8_t framebuffer_green_mask_size;
            u8_t framebuffer_blue_field_position;
            u8_t framebuffer_blue_mask_size;
        };
    };
} mbi_tag_fb_t;

typedef struct __struct_mbi_tag_elf_sect_t {
    mbi_tag_t tag;
    u32_t num;
    u32_t entsize;
    u32_t shndx;
    u8_t sections[0];
} mbi_tag_elf_sect_t;

typedef struct __struct_mbi_tag_apm_t {
    mbi_tag_t tag;
    u16_t version;
    u16_t cseg;
    u32_t offset;
    u16_t cseg_16;
    u16_t dseg;
    u16_t flags;
    u16_t cseg_len;
    u16_t cseg_16_len;
    u16_t dseg_len;
} mbi_tag_apm_t;

typedef struct __struct_mbi_tag_efi32_t {
    mbi_tag_t tag;
    u32_t pointer;
} mbi_tag_efi32_t;

typedef struct __struct_mbi_tag_efi64_t {
    mbi_tag_t tag;
    u64_t pointer;
} mbi_tag_efi64_t;

typedef struct __struct_mbi_tag_smbios_t {
    mbi_tag_t tag;
    u8_t major;
    u8_t minor;
    u8_t reserved[6];
    u8_t tables[0];
} mbi_tag_smbios_t;

typedef struct __struct_mbi_tag_old_acpi_t {
    mbi_tag_t tag;
    u8_t rsdp[0];
} mbi_tag_old_acpi_t;

typedef struct __struct_mbi_tag_new_acpi_t {
    mbi_tag_t tag;
    u8_t rsdp[0];
} mbi_tag_new_acpi_t;

typedef struct __struct_mbi_tag_network_t {
    mbi_tag_t tag;
    u8_t dhcpack[0];
} mbi_tag_network_t;

typedef struct __struct_mbi_tag_efi_mmap_t {
    mbi_tag_t tag;
    u32_t descr_size;
    u32_t descr_vers;
    u8_t efi_mmap[0];
} mbi_tag_efi_mmap_t;

typedef struct __struct_mbi_tag_efi32_ih_t {
    mbi_tag_t tag;
    u32_t pointer;
} mbi_tag_efi32_ih_t;

typedef struct __struct_mbi_tag_efi64_ih_t {
    mbi_tag_t tag;
    u64_t pointer;
} mbi_tag_efi64_ih_t;

typedef struct __struct_mbi_tag_load_base_addr_t {
    mbi_tag_t tag;
    u32_t load_base_addr;
} mbi_tag_load_base_addr_t;

#endif    /* ENIGMA_MULTIBOOT2_H */