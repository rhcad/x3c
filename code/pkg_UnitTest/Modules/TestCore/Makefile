ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Example/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_UnitTest/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_UnitTest/Modules/Public

C_FLAGS  +=   -D_CONSOLE
C_FLAGS  +=   -L/usr/lib
C_FLAGS  +=   -L/usr/local/lib

all:
	$(CC) $(CFLAGS) -c  TestLogging.cpp
	$(CC) $(CFLAGS) -c  TestChangeObserver.cpp
	$(CC) $(CFLAGS) -c  TestLoadPlugin.cpp
	$(CC) $(CFLAGS) -c  TestStringTable.cpp
	$(CC) $(CFLAGS) -c  TestFileUtil.cpp
	$(CC) $(C_FLAGS) -o $(UNITTESTS_DIR)/TestCore.app *.o -ldl -lcppunit
clean:
	rm -rf *.so
	rm -rf *.o
