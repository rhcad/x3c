ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface

ChangeObserver:
	$(CC) $(CFLAGS) -c  Cx_ChangeManager.cpp
	$(CC) $(CFLAGS) -c  Module.cpp
	$(CC) $(C_FLAGS) -o $(PLUGINS_DIR)/libChangeManager.so *.o
clean:
	rm -rf ChangeObserver
	rm -rf *.so
	rm -rf *.o


