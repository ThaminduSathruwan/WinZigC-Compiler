COMP_TARGETS = compiler compilemgr
COMP_CPPFLAGS := -I../../include -std=c++11 -Wall -Wextra
COMP_DIST_DIR = ../../dist/compiler
COMP_SRC_DIR = src\/compiler\/
COMP_ERROR_LOG = ../../dist/compiler/errors.log
TOP_ERROR_LOG = ../../dist/errors.log

all:
	$(MAKE) $(COMP_TARGETS)
	$(MAKE) check_error

$(COMP_TARGETS):
	-$(CXX) $(COMP_CPPFLAGS) $(if $(DEBUG),-g) -c -o $(COMP_DIST_DIR)/$@.o $@.cpp \
		2>> $(COMP_ERROR_LOG)

check_error:
	if [ -s $(COMP_ERROR_LOG) ]; then \
		echo "Current directory: $(PWD)"; \
		cat $(COMP_ERROR_LOG); \
		cat $(COMP_ERROR_LOG) \
			| sed 's/^\([a-zA-Z_][a-zA-Z0-9_]*\.cpp\| [a-zA-Z_][a-zA-Z0-9_]*\.h\)/$(COMP_SRC_DIR)\1/g' >> $(TOP_ERROR_LOG); \
	fi
