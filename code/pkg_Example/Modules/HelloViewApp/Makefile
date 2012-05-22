ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_AppUI/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Example/Interface

all:
	$(CC) $(CFLAGS) -c  ChildView.cpp
	$(CC) $(CFLAGS) -c  HelloViewApp.cpp
	$(CC) $(CFLAGS) -c  MainFrm.cpp
	$(CC) $(C_FLAGS) -o $(UNITTESTS_DIR)/HelloViewApp.app *.o $(LIBS)
clean:
	rm -rf *.so
	rm -rf *.o

