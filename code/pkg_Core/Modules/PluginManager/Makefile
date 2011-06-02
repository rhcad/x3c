ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Modules/PluginManager

all:
	$(CC) $(CFLAGS) -c  Cx_ObjectFactory.cpp
	$(CC) $(CFLAGS) -c  Module.cpp
	$(CC) $(CFLAGS) -c  Cx_PluginLoader.cpp
	$(CC) $(C_FLAGS) -o $(PLUGINS_DIR)/libPluginManager.so *.o
clean:
	rm -rf *.so
	rm -rf *.o


