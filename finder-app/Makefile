# Default target to build the "writer" application
default: writer

# Target to build the "writer" application for native platform
writer: writer.c
	gcc -o writer writer.c

# Target to build the "writer" application for cross-compilation
ifdef CROSS_COMPILE
	writer: writer.c
		$(CROSS_COMPILE)gcc -o writer writer.c
else
	echo "CROSS_COMPILE is not defined"
endif

# Target to clean build artifacts
clean:
	rm -f writer

.PHONY: clean

