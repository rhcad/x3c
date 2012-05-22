ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Utility/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_UnitTest/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_UnitTest/Modules/Public

CFLAGS   +=   -D_CONSOLE

C_FLAGS  +=   -L/usr/lib
C_FLAGS  +=   -L/usr/local/lib
C_FLAGS  +=   -L$(UNITTESTS_DIR)

all:
	$(CC) $(CFLAGS) -c  ../Public/BaseTest.cpp
	$(CC) $(CFLAGS) -c  ../Public/UnitTests.cpp
	$(CC) $(CFLAGS) -c  TestComHook.cpp
	$(CC) $(CFLAGS) -c  TestHookManager.cpp
	$(CC) $(C_FLAGS) -o $(UNITTESTS_DIR)/TestPlatform.app *.o $(LIBS) -lcppunit
clean:
	rm -rf *.so
	rm -rf *.o
