# The simplest way to compile x3c on Linux or Unix is:
# 1. `cd' to the directory containing the file of 'Makefile'.
# 2. Type `make' to compile the package.
#    The program binaries files are outputed to 'code/bin/plugins/' or 'code\bin\tests'.
# 
# 3. You can remove the program object files from the source code
#    directory by typing `make clean'.
#

ROOTDIR = .
include $(ROOTDIR)/config.mk

.PHONY:	code clean

#==============================================================================
# The default build target.
#==============================================================================
all:	code
#==============================================================================

code:
	$(MAKE) -C code

#==============================================================================
# Clean up the targets built by 'make all'.
#==============================================================================
clean:	code_clean
code_clean:
	$(MAKE) -C code clean

