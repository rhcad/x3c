ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Platform/Interface

SWIG        +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
SWIG        +=   -outdir $(SWIGOUT_DIR)

all:
	-@mkdir $(SWIGOUT_DIR)
	$(SWIG) x3core.i
	$(CC) $(CFLAGS_SO) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(SWIGOUT_DIR)/_x3core$(SWIGOUT_EXT) *.o
clean:
	rm -rf *.so
	rm -rf *.o
	rm -rf x3core_wrap.cxx
