TARGETS = 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15

.PHONY: all clean $(TARGETS)

all:
	@$(MAKE) clean --no-print-directory
	@$(MAKE) $(TARGETS) --no-print-directory

$(TARGETS):
	@echo "Testing winzig_$@..."
	../../dist/winzigcc -ast programs/winzig_$@ > dist/run/winzig_$@.tree
	diff programs/winzig_$@.tree dist/run/winzig_$@.tree
	@echo ""

clean:
	@rm -rf dist
	@mkdir -p dist/run
