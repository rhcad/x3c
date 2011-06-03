ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Example/Interface

all:
	$(CC) $(CFLAGS) -c  Cx_Example2.cpp
	$(CC) $(CFLAGS) -c  Plugin.cpp
	$(CC) $(CFLAGS) -c  Module.cpp
	$(CC) $(C_FLAGS) -o $(PLUGINS_DIR)/libMFCExtTempl.so *.o
clean:
	rm -rf *.so
	rm -rf *.o
