[BITS 32]
[SECTION .asm]

[GLOBAL kmemset:function]
[GLOBAL kmemsetw:function]
[GLOBAL kmemsetd:function]
[GLOBAL kmemcpy:function]
[GLOBAL kstrcpy:function]

;; C prototype - data_t kmemset(data_t buf, u8_t value, u32_t size);

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

;; C prototype - data_t kmemsetw(data_t buf, u16_t value, u32_t size);

kmemsetw: 
    push ebp
    mov ebp, esp

    ;; Store EDI.

    push edi

    mov ecx, [ebp + 0x10]        ; u32_t size
    shr ecx, 0x01                ; Divide it by 2.

    mov  ax, [ebp + 0x0C]        ; u16_t value
    mov edi, [ebp + 0x08]        ; data_t buf

    rep stosw

    ;; Return the buffer.

    mov eax, [ebp + 0x08]

    pop edi
    leave
    ret

;; C prototype - data_t kmemsetd(data_t buf, u32_t value, u32_t size);

kmemsetd: 
    push ebp
    mov ebp, esp

    ;; Store EDI.

    push edi

    mov ecx, [ebp + 0x10]        ; u32_t size
    shr ecx, 0x02                ; Divide it by 2.

    mov eax, [ebp + 0x0C]        ; u32_t value
    mov edi, [ebp + 0x08]        ; data_t buf

    rep stosd

    ;; Return the buffer.

    mov eax, [ebp + 0x08]

    pop edi
    leave
    ret

;; C prototype = data_t kmemcpy(data_t dest, data_t src, u32_t size);

kmemcpy:
    push ebp
    mov ebp, esp

    push esi

    mov ecx, [ebp + 0x10]        ; u32_t size
    mov esi, [ebp + 0x0C]        ; data_t src
    mov edx, [ebp + 0x08]        ; data_t dest

.loop: 
    lodsb
    mov [edx], al

    inc edx
    
    loop kmemcpy.loop

    ;; Return the buffer.

    mov eax, [ebp + 0x08]

    pop esi
    leave
    ret

;; C prototype - data_t kstrcpy(data_t dest, data_t src);

kstrcpy: 
    push ebp
    mov ebp, esp

    push esi

    mov esi, [ebp + 0x0C]        ; data_t src
    mov edx, [ebp + 0x08]        ; data_t dest

.loop: 
    lodsb
    and al, 0xFF
    jz kstrcpy.done

    mov [edx], al
    inc edx
    
    jmp kstrcpy.loop

.done:
    ;; Return the buffer.

    mov eax, [ebp + 0x08]

    pop esi
    leave
    ret