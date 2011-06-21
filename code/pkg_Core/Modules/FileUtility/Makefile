ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface


all:
	$(CC) $(CFLAGS_SO) -c  Cx_FileTransaction.cpp
	$(CC) $(CFLAGS_SO) -c  Cx_TempFolder.cpp
	$(CC) $(CFLAGS_SO) -c  Plugin.cpp
	$(CC) $(CFLAGS_SO) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libFileUtility.so *.o
clean:
	rm -rf *.so
	rm -rf *.o


