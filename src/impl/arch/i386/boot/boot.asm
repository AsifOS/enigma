[BITS 32]
[SECTION .boot]

[GLOBAL kinit]

kinit: 
    mov dword [0xb8000], 0x2f4b2f4f
    hlt