#ifndef _ENIGMA_KMEM_H
#define _ENIGMA_KMEM_H

#include <kint.h>
#include <ktype.h>

/* Set a single value to all the bytes of a buffer. Fast. */

extern data_t kmemset(data_t buf, u8_t value, u32_t size);

/* Set 2-byte value across a buffer. Buffer address must be 2-byte aligned 
   to get optimal performance. */

extern data_t kmemsetw(data_t buf, u16_t value, u32_t size);

/* Set 4-byte value across a buffer. Buffer address must be 4-byte aligned 
   for optimal performance. */

extern data_t kmemsetd(data_t buf, u32_t value, u32_t size);

/* Zero out a buffer. Fast. */

data_t kmemsetz(data_t buf, u32_t size);

/* Copy bytes from source buffer to destination buffer. */

data_t kmemcpy(data_t dest, data_t src, u32_t size);

/* Copy string from source buffer to destination buffer. */

data_t kstrcpy(data_t dest, data_t src);

#endif    // _ENIGMA_KMEM_H