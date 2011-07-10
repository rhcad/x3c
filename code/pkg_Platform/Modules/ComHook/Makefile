ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Platform/Interface

all:
	$(CC) $(CFLAGS_SO) -c  ApiHook.cpp
	$(CC) $(CFLAGS_SO) -c  ComCreator.cpp
	$(CC) $(CFLAGS_SO) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libComHook.so *.o
clean:
	rm -rf *.so
	rm -rf *.o
