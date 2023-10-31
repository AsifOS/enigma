#ifndef ENIGMA_CONFIG_H
#define ENIGMA_CONFIG_H

/* Maximum length of the string of Multiboot command line variables. Must
   be 8-byte aligned. */

#define MULTIBOOT_COMMAND_LINE_LENGTH     128

/* Maximum length of the string associated with Multiboot boot module. */

#define MULTIBOOT_MODULE_STRING_LENGTH    64

#endif    // ENIGMA_CONFIG_H