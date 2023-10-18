[BITS 32]
[SECTION .multiboot]

MBOOT2_HADER_MAGIC   equ 0xE85250D6        ; Magic number indicating Multiboot2
MBOOT2_ARCH          equ 0                 ; 32-bit i386 (Protected Mode)
MBOOT2_CHECKSUM      equ 0x100000000       ; Checksum magic number

header_start: 
    ; The Multiboo2 header.

    dd MBOOT2_HADER_MAGIC
    dd MBOOT2_ARCH
    dd (header_end - header_start)         ; Header length
    dd MBOOT2_CHECKSUM \
     - (MBOOT2_HADER_MAGIC \
     + MBOOT2_ARCH \
     + (header_end - header_start))        ; Checksum for validation
    
    ; Tags.

    dw 10                                  ; Relocatable tag
    dw 0
    dd 24
    dd 0x100000                            ; Min. address loadable
    dd 0x200000                            ; Max. address loadable
    dd 4096                                ; Single 4KB page alignment
    dd 1                                   ; Load image in lowest possible 
                                           ;    address

    dw 0
    dw 0
    dd 8                                   ; Termination tag

header_end:
