#include <enigma/kernel.h>

void main(kinfo_t *info) {
    info += 0;
    __asm__ volatile ("hlt");
}