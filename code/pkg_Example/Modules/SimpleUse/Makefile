ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Example/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Example/Modules/SimpleUse

all:
	$(CC) $(CFLAGS) -c  Main.cpp
	$(CC) $(C_FLAGS) -o $(UNITTESTS_DIR)/SimpleUse *.o
clean:
	rm -rf *.so
	rm -rf *.o

