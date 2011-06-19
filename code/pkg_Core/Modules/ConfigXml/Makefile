ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Modules/ConfigXml
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Modules/TinyXml

all:
	$(CC) $(CFLAGS) -c  Cx_ConfigXml.cpp
	$(CC) $(CFLAGS) -c  Cx_XmlSection.cpp
	$(CC) $(CFLAGS) -c  Module.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libConfigXml.so *.o
clean:
	rm -rf *.so
	rm -rf *.o
