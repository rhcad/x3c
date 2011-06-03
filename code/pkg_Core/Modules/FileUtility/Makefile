ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface


all:
	$(CC) $(CFLAGS) -c  Cx_FileTransaction.cpp
	$(CC) $(CFLAGS) -c  Cx_TempFolder.cpp
	$(CC) $(CFLAGS) -c  Plugin.cpp
	$(CC) $(CFLAGS) -c  Module.cpp
	$(CC) $(C_FLAGS) -o $(PLUGINS_DIR)/libFileUtility.so *.o
clean:
	rm -rf *.so
	rm -rf *.o


