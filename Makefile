TOP_SUBDIRS := scanner parser compiler main
TOP_CPPFLAGS := -Iinclude -Wall -Wextra -std=c++11
TOP_DIST_DIR := dist
TOP_SRC_DIR := src
ERROR_LOG := dist/errors.log
LINK_ERR__LOG := dist/link_err.log

.PHONY: all clean

all:
	$(MAKE) clean
	$(MAKE) $(TOP_SUBDIRS)
	-$(CXX) $(TOP_CPPFLAGS) \
		-o $(TOP_DIST_DIR)/winzigcc \
		$(TOP_DIST_DIR)/scanner/*.o \
		$(TOP_DIST_DIR)/parser/*.o \
		$(TOP_DIST_DIR)/compiler/*.o \
		$(TOP_DIST_DIR)/main/*.o \
		2> $(LINK_ERR__LOG)
	$(MAKE) check_errors

$(TOP_SUBDIRS):
	mkdir -p $(TOP_DIST_DIR)/$@
	$(MAKE) -C $(TOP_SRC_DIR)/$@ all

clean:
	rm -rf $(TOP_DIST_DIR)
	mkdir -p $(TOP_DIST_DIR)
	touch $(ERROR_LOG)

check_errors:
	@if [ -s $(ERROR_LOG) ] || [ -s $(LINK_ERR__LOG) ]; then \
		$(MAKE) print_error \
		&& exit 1; \
	else \
		$(MAKE) print_success; \
	fi

print_error:
	@echo "\n====================================================================================================\n"
	@echo "Build failed!"
	@if [ -s $(ERROR_LOG) ]; then \
		echo "\nCompilation errors----------------------------------------------------------------------------------\n"; \
		cat $(ERROR_LOG) | grep --color=always .; \
	fi
	@if [ -s $(LINK_ERR__LOG) ]; then \
		echo "\nLinker errors---------------------------------------------------------------------------------------\n"; \
		cat $(LINK_ERR__LOG) | grep --color=always .; \
	fi
	@echo "\n====================================================================================================\n"

print_success:
	@echo "\n====================================================================================================\n"
	@echo "Build successful!"
	@echo "\n====================================================================================================\n"
