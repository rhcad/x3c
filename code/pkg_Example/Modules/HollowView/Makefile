ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_AppUI/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Example/Interface

all:
	$(CC) $(CFLAGS) -c  CmdObserver.cpp
	$(CC) $(CFLAGS) -c  WndA.cpp
	$(CC) $(CFLAGS) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libHollowView.so *.o
clean:
	rm -rf *.so
	rm -rf *.o
