[BITS 32]
[SECTION .boot]

;; We are keeping 8KB as the kernel initial stack size.

%define STACK_SIZE 8192

;; Multiboot2 related defines.

%define MULTIBOOT_SEARCH                        32768        ; 32KB
%define MULTIBOOT_HEADER_ALIGN                  8

;; The magic number Multiboot2 compliant header should contain.

%define MULTIBOOT2_HEADER_MAGIC                 0xE85250D6

;; This should be in EAX after invoked by a bootloader.

%define MULTIBOOT2_BOOTLOADER_MAGIC             0x36D76289

;; Alignment of multiboot modules.

%define MULTIBOOT_MOD_ALIGN                     0x00001000

;; Alignment of the multiboot info structure.

%define MULTIBOOT_INFO_ALIGN                    0x00000008

;; Multiboot2 header tag types. They are the tags defined in the header.

%define MULTIBOOT_HEADER_TAG_END                                0
%define MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST                1
%define MULTIBOOT_HEADER_TAG_ADDRESS                            2
%define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS                      3
%define MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS                      4
%define MULTIBOOT_HEADER_TAG_FRAMEBUFFER                        5
%define MULTIBOOT_HEADER_TAG_MODULE_ALIGN                       6
%define MULTIBOOT_HEADER_TAG_EFI_BS                             7
%define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI32                8
%define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI64                9
%define MULTIBOOT_HEADER_TAG_RELOCATABLE                        10

;; Multiboot2 tag alignment.

%define MULTIBOOT_TAG_ALIGN                  8

;; Multiboot2 information structure tag types.

%define MULTIBOOT_TAG_TYPE_END               0
%define MULTIBOOT_TAG_TYPE_CMDLINE           1
%define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME  2
%define MULTIBOOT_TAG_TYPE_MODULE            3
%define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO     4
%define MULTIBOOT_TAG_TYPE_BOOTDEV           5
%define MULTIBOOT_TAG_TYPE_MMAP              6
%define MULTIBOOT_TAG_TYPE_VBE               7
%define MULTIBOOT_TAG_TYPE_FRAMEBUFFER       8
%define MULTIBOOT_TAG_TYPE_ELF_SECTIONS      9
%define MULTIBOOT_TAG_TYPE_APM               10
%define MULTIBOOT_TAG_TYPE_EFI32             11
%define MULTIBOOT_TAG_TYPE_EFI64             12
%define MULTIBOOT_TAG_TYPE_SMBIOS            13
%define MULTIBOOT_TAG_TYPE_ACPI_OLD          14
%define MULTIBOOT_TAG_TYPE_ACPI_NEW          15
%define MULTIBOOT_TAG_TYPE_NETWORK           16
%define MULTIBOOT_TAG_TYPE_EFI_MMAP          17
%define MULTIBOOT_TAG_TYPE_EFI_BS            18
%define MULTIBOOT_TAG_TYPE_EFI32_IH          19
%define MULTIBOOT_TAG_TYPE_EFI64_IH          20
%define MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR    21

;; Multiboot2 architecture.

%define MULTIBOOT_ARCHITECTURE_I386    0
%define MULTIBOOT_ARCHITECTURE_MIPS32  4

;; Optional field for header tag flags.

%define MULTIBOOT_HEADER_TAG_OPTIONAL  1

[EXTERN mb_main:function]
[EXTERN enigma:function]

[GLOBAL _boot:function]

_start: 
    jmp _boot

ALIGN 8
header_start:
    ;; Multiboot2 header magic.

    dd MULTIBOOT2_HEADER_MAGIC

    ;; Target architecture is i386.

    dd MULTIBOOT_ARCHITECTURE_I386

    ;; Header size.

    dd header_end - header_start

    ;; Checksum.

    dd - (MULTIBOOT2_HEADER_MAGIC + MULTIBOOT_ARCHITECTURE_I386 \
       + (header_end - header_start))

addr_tag_start:
    dw MULTIBOOT_HEADER_TAG_ADDRESS

    ;; The bootloader must be able to load images other than ELF formats.

    dw 0

    ;; Size of the tag.

    dd addr_tag_end - addr_tag_start
    
    ;; Header address.

    dd header_start

    ;; The load address of the text section. As our kernel is going to be 
    ;; raw binary blob, there will be no text, data or bss sections. Though
    ;; the linker will do the job of restructuring the sections and emit a 
    ;; clean binary blob.
    
    dd _start
    dd 0
    dd 0
addr_tag_end:

ALIGN 8
entry_addr_tag_start:
    dw MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS
    dw 0

    ;; Tag size.

    dd entry_addr_tag_end - entry_addr_tag_start

    ;; The entry point to jump to.

    dd _boot
entry_addr_tag_end:

ALIGN 8 
info_req_tag_start:
    dw MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST

    ;; Not optional.

    dw 0

    ;; Tag size.

    dd info_req_tag_end - info_req_tag_start

    ;; Requested info tags.

    dd MULTIBOOT_TAG_TYPE_MMAP
info_req_tag_end:

ALIGN 8
end_tag_start:
    ;; The end tag.

    dw MULTIBOOT_HEADER_TAG_END
    dw 0
    dd end_tag_end - end_tag_start
end_tag_end:
header_end:

_boot:
    ;; Initialize the kernel stack pointer.

    mov esp, stack_start

    ;; Reset the flags in EFLAGS register.

    push dword 0
    popfd

    ;; Call the multiboot C entry point.

    push ebx
    push eax
    call mb_main

    ;; If we get nothing in return from the function call, means we had issue.

    and eax, 0xFFFFFFFF
    jz _boot.error

    ;; Now call the abstracted boot entry point.

    push eax
    call enigma

    ;; If the call returns which isn't supposed to, indicates we faced 
    ;; some fatal issue. So, the next instruction will halt the system.

.error: 
    hlt

[SECTION .bss]

stack_end: 
    resb STACK_SIZE
stack_start: