#include <enigma/kernel.h>
#include <ktype.h>
#include <gdt.h>

void enigma(kinfo_t *info) {
    /* Set up the GDT. */

    gdt_init();
    
    /* Dispatch to kernel main. */

    main(info);
}