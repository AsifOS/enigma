[BITS 32]
[SECTION .asm]

[GLOBAL kmemset:function]
[GLOBAL kmemsetw:function]

;; C definition - data_t kmemset(data_t buf, u8_t value, u32_t size);

kmemset:
    push ebp
    mov ebp, esp

    ;; Store EDI.

    push edi

    mov ecx, [ebp + 0x10]        ; u32_t size
    mov  al, [ebp + 0x0C]        ; u8_t value
    mov edi, [ebp + 0x08]        ; data_t buf

    rep stosb

    ;; Return the buffer.

    mov eax, [ebp + 0x08]

    pop edi
    leave
    ret

;; C definition - data_t kmemsetw(data_t buf, u16_t value, u32_t size);

kmemsetw: 
    push ebp
    mov ebp, esp

    ;; Store EDI.

    push edi

    mov ecx, [ebp + 0x10]        ; u32_t size
    shr ecx, 2                   ; Divide it by 2.

    mov  ax, [ebp + 0x0C]        ; u16_t value
    mov edi, [ebp + 0x08]        ; data_t buf

    rep stosw

    ;; Return the buffer.

    mov eax, [ebp + 0x08]

    pop edi
    leave
    ret