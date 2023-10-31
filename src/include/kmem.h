#ifndef __ENIGMA_KMEM_H__
#define __ENIGMA_KMEM_H__

#include <kint.h>
#include <ktype.h>

extern data_t kmemset(data_t buf, u8_t value, u32_t size);
extern data_t kmemsetw(data_t buf, u16_t value, u32_t size);

#endif    // __ENIGMA_KMEM_H__