PARSE_TARGETS = parser
PARSE_CPPFLAGS := -I../../include -std=c++11 -Wall -Wextra
PARSE_DIST_DIR = ../../dist/parser
PARSE_SRC_DIR = src\/parser\/
PARSE_ERROR_LOG = ../../dist/parser/errors.log
TOP_ERROR_LOG = ../../dist/errors.log

all:
	$(MAKE) $(PARSE_TARGETS)
	$(MAKE) check_error

$(PARSE_TARGETS):
	-$(CXX) $(PARSE_CPPFLAGS) -c -o $(PARSE_DIST_DIR)/$@.o $@.cpp \
		2> $(PARSE_ERROR_LOG)

check_error:
	if [ -s $(PARSE_ERROR_LOG) ]; then \
		echo "Current directory: $(PWD)"; \
		cat $(PARSE_ERROR_LOG); \
		cat $(PARSE_ERROR_LOG) \
			| sed 's/^\([a-zA-Z_][a-zA-Z0-9_]*\.cpp\| [a-zA-Z_][a-zA-Z0-9_]*\.h\)/$(PARSE_SRC_DIR)\1/g' >> $(TOP_ERROR_LOG); \
	fi
	
