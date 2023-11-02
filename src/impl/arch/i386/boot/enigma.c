#include <enigma/kernel.h>
#include <ktype.h>

void enigma(kinfo_t *info) {
    /* Dispatch to kernel main. */

    // main(info);

    info += 0;

    

    __asm__ volatile ("hlt");
}