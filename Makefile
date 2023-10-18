default_target : build

# Current directory (root).

CURRENT_DIR := .

.PHONY  :
.SILENT : 

build : 
	$(MAKE) -sf $(CURRENT_DIR)/src/impl/arch/Makefile.slave_1 \
	Fi_CURRENT_DIR=$(CURRENT_DIR)/src/impl/arch/