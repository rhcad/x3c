ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Utility/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_UnitTest/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_UnitTest/Modules/Public

C_FLAGS  +=   -D_CONSOLE
C_FLAGS  +=   -L/usr/lib
C_FLAGS  +=   -L/usr/local/lib

all:
	$(CC) $(CFLAGS) -c  TestConfigDB.cpp
	$(CC) $(C_FLAGS) -o $(UNITTESTS_DIR)/TestUtility.app *.o -ldl -lcppunit
clean:
	rm -rf *.so
	rm -rf *.o
