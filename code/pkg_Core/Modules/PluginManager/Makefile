ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface

all:
	$(CC) $(CFLAGS) -c  Cx_ObjectFactory.cpp
	$(CC) $(CFLAGS) -c  Module.cpp
	$(CC) $(CFLAGS) -c  Cx_PluginLoader.cpp
	$(CC) $(C_FLAGS) -o $(PLUGINS_DIR)/libPluginManager.so *.o -ldl
clean:
	rm -rf *.so
	rm -rf *.o


