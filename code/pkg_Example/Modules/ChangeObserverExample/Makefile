ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Example/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Example/Modules/ChangeObserverExample

all:
	$(CC) $(CFLAGS) -c  Plugin.cpp
	$(CC) $(CFLAGS) -c  Cx_ObserverTest.cpp
	$(CC) $(CFLAGS) -c  Module.cpp
	$(CC) $(C_FLAGS) -o $(PLUGINS_DIR)/libChangeObserverExample.so *.o
clean:
	rm -rf *.so
	rm -rf *.o

