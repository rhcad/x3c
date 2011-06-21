ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Example/Interface

all:
	$(CC) $(CFLAGS_SO) -c  Cx_Example.cpp
	$(CC) $(CFLAGS_SO) -c  Plugin.cpp
	$(CC) $(CFLAGS_SO) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libWin32DllTempl.so *.o
clean:
	rm -rf *.so
	rm -rf *.o
