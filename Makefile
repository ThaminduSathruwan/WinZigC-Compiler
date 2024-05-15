TOP_SUBDIRS := scanner parser compiler main
TOP_CPPFLAGS := -Iinclude -Wall -Wextra -std=c++11
TOP_DIST_DIR := dist
TOP_SRC_DIR := src
ERROR_LOG := dist/errors.log
LINK_ERR_LOG := dist/link_err.log
EXEC_LOG := dist/exec.log
OUTPUT := winzigcc

.PHONY: all clean debug

all:
	@echo "Cleaning up..."
	@$(MAKE) clean > /dev/null
	@touch $(EXEC_LOG)
	@echo "Compiling..."
	@$(MAKE) compile >> $(EXEC_LOG)
	@echo "Linking..."
	@$(MAKE) link >> $(EXEC_LOG)
	@./finish.sh

compile:
	$(MAKE) $(TOP_SUBDIRS)
	touch $(LINK_ERR_LOG)
	touch $(ERROR_LOG)

link:
	-$(CXX) $(TOP_CPPFLAGS) \
		-o $(TOP_DIST_DIR)/$(OUTPUT) \
		$(TOP_DIST_DIR)/*/*.o \
		2> $(LINK_ERR_LOG)
	$(MAKE) check_errors

$(TOP_SUBDIRS):
	mkdir -p $(TOP_DIST_DIR)/$@
	$(MAKE) -C $(TOP_SRC_DIR)/$@ all

clean:
	rm -rf $(TOP_DIST_DIR)
	mkdir -p $(TOP_DIST_DIR)
	touch $(ERROR_LOG)

check_errors:
	@if [ -s $(LINK_ERR_LOG) ]; then \
		cat $(LINK_ERR_LOG); \
	fi

debug:
	@export DEBUG=1; \
	$(MAKE) all | sed '/directory/d'; \
	unset DEBUG
