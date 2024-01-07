#ifndef _ENIGMA_KTYPE_H
#define _ENIGMA_KTYPE_H

/* Use this to define RAW data. */

typedef void *data_t;

/* Use this to denote null pointer. */

#define nullptr    ((void*) 0)
#define null               (0)

/* Use this to define assembly routine. The default ABI is SysV. */

#define ASMCALL    extern __attribute__((sysv_abi))

#endif    // _ENIGMA_KTYPE_H
