CPPFLAGS := -I../../../include -std=c++11 -Wall -Wextra
TESTS := test_1 test_2

all:
	$(MAKE) clean --no-print-directory
	$(MAKE) $(TESTS) --no-print-directory

$(TESTS):
	@echo ""
	@echo "Testing $@..."
	$(CXX) $(CPPFLAGS) -g -c -o dist/$@.o $@.cpp
	$(CXX) $(CPPFLAGS) -g -o dist/$@ ../../../dist/parser/*.o ../../../dist/scanner/*.o dist/$@.o
	./dist/$@ > dist/run/$@.out
	diff -u $@.tree dist/run/$@.out

clean:
	rm -rf dist
	mkdir -p dist/run
