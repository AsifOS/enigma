default_target : rock_and_roll

# Include the build config.

include buildconf
include config

# Current directory (root).

CURRENT_DIR := .
		
LINKER_DIR    := $(CURRENT_DIR)/src/impl/linker/$(ARCH)
LINKER_SCRIPT := $(LINKER_DIR)/default.ld
KERNEL_EXT    := .bin

.PHONY  :
.SILENT : 

rock_and_roll : message build_dir start_job
	$(Bu_LD) -n -T $(LINKER_SCRIPT) $(wildcard $(Bu_OBJ_DIR)/*.asm.obj) \
	$(wildcard $(Bu_OBJ_DIR)/*.c.obj) -o $(Bu_OUTPUT_DIR)/kernel$(KERNEL_EXT)

	echo -e "\nSuccessfully created '$(Bu_OUTPUT_DIR)/kernel$(KERNEL_EXT)'\n"

# Create a Multiboot2 compliant boot image (If applicable).

ifeq ($(MULTIBOOT2_BOOT), yes)
	mkdir -p $(Bu_OUTPUT_DIR)/multiboot2_sysroot/{boot/grub/,AsifOS}
	cp $(CURRENT_DIR)/misc/multiboot2/grub.cfg \
	$(Bu_OUTPUT_DIR)/multiboot2_sysroot/boot/grub/
	cp $(Bu_OUTPUT_DIR)/kernel$(KERNEL_EXT) \
	$(Bu_OUTPUT_DIR)/multiboot2_sysroot/AsifOS/kernel$(KERNEL_EXT)

	grub-mkrescue -o $(Bu_OUTPUT_DIR)/asifos.iso \
	$(Bu_OUTPUT_DIR)/multiboot2_sysroot

	echo "Created Multiboot2 compliant image file '$(Bu_OUTPUT_DIR)/asifos.iso'"
endif

	echo "All OK!"

start_job : 
	$(MAKE) -sf $(CURRENT_DIR)/src/impl/Makefile.1 \
	Fi_CURRENT_DIR=$(CURRENT_DIR)/src/impl \
	Fi_VERSION=$(VERSION) Fi_ARCH=$(ARCH)

build_dir : 
	mkdir -p $(Bu_CREATE)

clean : 
	rm -rf build

message :
	echo -e    "\n"
	echo -e    "    =|                    =|      =|=|    =|=|=|      =|=|=|    "
	echo -e    "  =|  =|                        =|      =|      =|  =|      =|  "
	echo -e    "  =|  =|      =|=|=|=|  =|=|  =|=|=|=|  =|      =|  =|          "
	echo -e    "=|      =|  =|            =|    =|      =|      =|    =|=|=|    "
	echo -e    "=|=|=|=|=|    =|=|=|      =|    =|      =|      =|          =|  "
	echo -e    "=|      =|          =|    =|    =|      =|      =|  =|      =|  "
	echo -e    "=|      =|  =|=|=|=|      =|    =|        =|=|=|      =|=|=|    \n\n"