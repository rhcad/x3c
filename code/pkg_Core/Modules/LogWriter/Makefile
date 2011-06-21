ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS_SO   +=   -I$(INCLUDE_DIR)/pkg_Core/Modules/LogWriter/log4cplus/include

CFLAGS_SO   +=   -DUNICODE
CFLAGS_SO   +=   -DINSIDE_LOG4CPLUS
CFLAGS_SO   +=   -DLOG4CPLUS_STATIC

all:
	$(CC) $(CFLAGS_SO) -c  LogObserver.cpp
	$(CC) $(CFLAGS_SO) -c  Module.cpp
	$(CC) $(CFLAGS_SO) -c  Plugin.cpp
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libLogWriter.so *.o
clean:
	rm -rf *.so
	rm -rf *.o


