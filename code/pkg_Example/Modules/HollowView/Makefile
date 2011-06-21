ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_AppUI/Interface
CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Example/Interface

all:
	$(CC) $(CFLAGS_SO) -c  CmdObserver.cpp
	$(CC) $(CFLAGS_SO) -c  WndA.cpp
	$(CC) $(CFLAGS_SO) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libHollowView.so *.o
clean:
	rm -rf *.so
	rm -rf *.o
