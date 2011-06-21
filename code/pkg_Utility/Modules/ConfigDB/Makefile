ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Utility/Interface/Database

all:
	$(CC) $(CFLAGS_SO) -c  Cx_CfgDbSection.cpp
	$(CC) $(CFLAGS_SO) -c  Cx_CfgRecordset.cpp
	$(CC) $(CFLAGS_SO) -c  Cx_CfgDatabase.cpp
	$(CC) $(CFLAGS_SO) -c  Cx_CfgRecord.cpp
	$(CC) $(CFLAGS_SO) -c  Cx_ConfigFactory.cpp
	$(CC) $(CFLAGS_SO) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libTextUtility.so *.o
clean:
	rm -rf *.so
	rm -rf *.o




