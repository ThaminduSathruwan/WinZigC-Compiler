MAIN_TARGETS = main
MAIN_CPPFLAGS := -I../../include -std=c++11 -Wall -Wextra
MAIN_DIST_DIR = ../../dist/main
MAIN_SRC_DIR = src\/main\/
MAIN_ERROR_LOG = ../../dist/main/errors.log
TOP_ERROR_LOG = ../../dist/errors.log

all:
	$(MAKE) $(MAIN_TARGETS)
	$(MAKE) check_error

$(MAIN_TARGETS):
	-$(CXX) $(MAIN_CPPFLAGS) -c -o $(MAIN_DIST_DIR)/$@.o $@.cpp \
		2> $(MAIN_ERROR_LOG)

check_error:
	if [ -s $(MAIN_ERROR_LOG) ]; then \
		echo "Current directory: $(PWD)"; \
		cat $(MAIN_ERROR_LOG); \
		cat $(MAIN_ERROR_LOG) \
			| sed 's/^\([a-zA-Z_][a-zA-Z0-9_]*\.cpp\| [a-zA-Z_][a-zA-Z0-9_]*\.h\)/$(MAIN_SRC_DIR)\1/g' >> $(TOP_ERROR_LOG); \
	fi
