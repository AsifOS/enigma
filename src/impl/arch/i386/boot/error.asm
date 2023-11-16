[BITS 32]
[SECTION .asm]

[GLOBAL __boot_err:function]

VIDEO_MEM equ 0xB8000        ; VGA video memory

;; This is a very minimalist sub-routine to print error text to the screen 
;; at boot time, intended for boot time errors only.
;; 
;; Call using SysV calling convention.

__boot_err: 
    push ebp
    mov ebp, esp

    push esi

    mov esi, [ebp + 0x08]
    mov ecx, VIDEO_MEM

.loop: 
    lodsb

    ;; Now check for the NULL termination character.

    or al, 0
    jz __boot_err.done

    mov ah, 0x4f
    mov [ecx], ax
    add ecx, 2

    jmp __boot_err.loop

.done: 
    leave

    ret
