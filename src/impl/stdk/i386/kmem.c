#include <kmem.h>
#include <kint.h>

data_t kmemsetz(data_t buf, u32_t size) {
    u8_t *dest = buf;

    /* If the size is less than 4 bytes, use regular memset. */

    if(size < 4) {
        kmemset(dest, 0, size);

        goto out;
    }

    /* The size we need to memset in order to get a 4-byte aligned addr. */

    u32_t pad = ((size + 0x03) & ~0x03) - size;

    /* Now pad the buffer to get a 4-byte aligned addr. */

    if(pad) {
        kmemset(dest, 0, pad);
        dest += pad;
        size -= pad;
    }

    /* Now memset 4 bytes at a time. */

    kmemsetd(dest, 0, size);

out: 
    return buf;
}