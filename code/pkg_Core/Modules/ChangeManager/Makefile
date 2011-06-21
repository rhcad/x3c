ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface

ChangeObserver:
	$(CC) $(CFLAGS_SO) -c  Cx_ChangeManager.cpp
	$(CC) $(CFLAGS_SO) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libChangeManager.so *.o
clean:
	rm -rf ChangeObserver
	rm -rf *.so
	rm -rf *.o


