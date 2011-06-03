ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface

all:
	$(CC) $(CFLAGS) -c  Cx_ClipboardUtil.cpp
	$(CC) $(CFLAGS) -c  Cx_GuidGenerator.cpp
	$(CC) $(CFLAGS) -c  Cx_TextUtil.cpp
	$(CC) $(CFLAGS) -c  Module.cpp
	$(CC) $(C_FLAGS) -o $(PLUGINS_DIR)/libTextUtility.so *.o
clean:
	rm -rf *.so
	rm -rf *.o


