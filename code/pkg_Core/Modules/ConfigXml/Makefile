ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Modules/ConfigXml
CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Modules/TinyXml

all:
	$(CC) $(CFLAGS_SO) -c  Cx_ConfigXml.cpp
	$(CC) $(CFLAGS_SO) -c  Cx_XmlSection.cpp
	$(CC) $(CFLAGS_SO) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libConfigXml.so *.o $(LIBS)
clean:
	rm -rf *.so
	rm -rf *.o
