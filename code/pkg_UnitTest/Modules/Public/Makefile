ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_AppUI/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Example/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Example/Modules/HollowViewApp
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_UnitTest/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_UnitTest/Modules/Public

all:
	$(CC) $(CFLAGS) -c  BaseTest.cpp
	$(CC) $(CFLAGS) -c  UnitTests.cpp
	$(CC) $(C_FLAGS) -o $(PLUGINS_DIR)/libPublic.so *.o
clean:
	rm -rf *.so
	rm -rf *.o

