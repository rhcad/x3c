ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Example/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_UnitTest/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_UnitTest/Modules/Public

CFLAGS   +=   -D_CONSOLE

C_FLAGS  +=   -L/usr/lib
C_FLAGS  +=   -L/usr/local/lib
C_FLAGS  +=   -L$(UNITTESTS_DIR)

all:
	$(CC) $(CFLAGS) -c  ../Public/BaseTest.cpp
	$(CC) $(CFLAGS) -c  ../Public/UnitTests.cpp
	$(CC) $(CFLAGS) -c  TestLogging.cpp
	$(CC) $(CFLAGS) -c  TestChangeObserver.cpp
	$(CC) $(CFLAGS) -c  TestLoadPlugin.cpp
	$(CC) $(CFLAGS) -c  TestStringTable.cpp
	$(CC) $(CFLAGS) -c  TestFileUtil.cpp
	$(CC) $(CFLAGS) -c  TestTextUtil.cpp
	$(CC) $(C_FLAGS) -o $(UNITTESTS_DIR)/TestCore.app *.o $(LIBS) -lcppunit
clean:
	rm -rf *.so
	rm -rf *.o
