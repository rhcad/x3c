ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface/ChangeObserver
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface/UtilFunc
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface/Module

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Modules/FileUtility
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface/Utility

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Modules/LogManager
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface/Log


all:
	$(CC) $(CFLAGS) -c  Cx_LogManager.cpp
	$(CC) $(CFLAGS) -c  Module.cpp 
	$(CC) $(C_FLAGS) -o $(PLUGINS_DIR)/libLogManager.so *.o 
clean:
	rm -rf *.so 
	rm -rf *.o


