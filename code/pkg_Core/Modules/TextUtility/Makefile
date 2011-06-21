ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface

all:
	$(CC) $(CFLAGS_SO) -c  Cx_ClipboardUtil.cpp
	$(CC) $(CFLAGS_SO) -c  Cx_GuidGenerator.cpp
	$(CC) $(CFLAGS_SO) -c  Cx_TextUtil.cpp
	$(CC) $(CFLAGS_SO) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libTextUtility.so *.o
clean:
	rm -rf *.so
	rm -rf *.o
