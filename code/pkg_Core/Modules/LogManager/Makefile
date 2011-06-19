ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface


all:
	$(CC) $(CFLAGS) -c  Cx_LogManager.cpp
	$(CC) $(CFLAGS) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libLogManager.so *.o
clean:
	rm -rf *.so
	rm -rf *.o


