#include <enigma/kernel.h>
#include <ktype.h>

void enigma(kinfo_t *info) {
    /* Dispatch to kernel main. */

    // main(info);

    info += 0;

    unsigned short *vid_mem = (unsigned short*) 0xb8000;

    vid_mem[0] = 0x4f4f;
    vid_mem[1] = 0x4f4b;

    __asm__ volatile ("hlt");
}