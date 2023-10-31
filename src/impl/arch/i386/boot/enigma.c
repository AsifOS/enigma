#include <enigma/kernel.h>
#include <ktype.h>

void enigma(u32_t magic, data_t info) {
    /* Dispatch to kernel main. */

    // main(info);

    info += magic;

    unsigned short *vid_mem = (unsigned short*) 0xb8000;

    vid_mem[0] = 0x4f4f;
    vid_mem[1] = 0x4f4b;

    __asm__ volatile ("hlt");
}