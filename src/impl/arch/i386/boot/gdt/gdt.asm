[BITS 32]
[SECTION .asm]

[GLOBAL gdt_load:function]

gdt_load: 
    push ebp
    mov ebp, esp

    ;; Load the descriptor.

    mov eax, [ebp + 0x08]
    lgdt [eax]

    ;; Reload code selector.
    
    mov eax, [ebp + 0x0C]
    push eax
    push gdt_load.selec_init

    retf        ; Now perform a far return to reload the selector.

.selec_init:

    ; Populate other selector registers with the data selector.

    mov ax, [ebp + 0x10]
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    leave
    ret
