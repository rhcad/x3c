ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Utility/Interface/Database

all:
	$(CC) $(CFLAGS) -c  Cx_CfgDbSection.cpp
	$(CC) $(CFLAGS) -c  Cx_CfgRecordset.cpp
	$(CC) $(CFLAGS) -c  Cx_CfgDatabase.cpp
	$(CC) $(CFLAGS) -c  Cx_CfgRecord.cpp
	$(CC) $(CFLAGS) -c  Cx_ConfigFactory.cpp
	$(CC) $(CFLAGS) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libTextUtility.so *.o
clean:
	rm -rf *.so
	rm -rf *.o




