SCAN_TARGETS = scanner token
SCAN_CPPFLAGS := -I../../include -std=c++11 -Wall -Wextra
SCAN_DIST_DIR = ../../dist/scanner
SCAN_SRC_DIR = src\/scanner\/
SCAN_ERROR_LOG = ../../dist/scanner/errors.log
TOP_ERROR_LOG = ../../dist/errors.log

all:
	$(MAKE) $(SCAN_TARGETS)
	$(MAKE) check_error

$(SCAN_TARGETS):
	$(CXX) $(SCAN_CPPFLAGS) -c -o $(SCAN_DIST_DIR)/$@.o $@.cpp \
		2> $(SCAN_ERROR_LOG)

check_error:
	if [ -s $(SCAN_ERROR_LOG) ]; then \
		echo "Current directory: $(PWD)"; \
		cat $(SCAN_ERROR_LOG); \
		cat $(SCAN_ERROR_LOG) \
			| sed 's/^\([a-zA-Z_][a-zA-Z0-9_]*\.cpp\| [a-zA-Z_][a-zA-Z0-9_]*\.h\)/$(SCAN_SRC_DIR)\1/g' >> $(TOP_ERROR_LOG); \
	fi
