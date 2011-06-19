ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Example/Interface

CFLAGS   +=   -D_CONSOLE

all:
	$(CC) $(CFLAGS) -c  Main.cpp
	$(CC) $(C_FLAGS) -o $(UNITTESTS_DIR)/SimpleUse.app *.o -ldl
clean:
	rm -rf *.so
	rm -rf *.o
