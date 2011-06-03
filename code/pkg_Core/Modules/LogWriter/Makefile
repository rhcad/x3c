ROOTDIR = ../../../..
include $(ROOTDIR)/config.mk

CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Interface
CFLAGS   +=   -I$(INCLUDE_DIR)/pkg_Core/Modules/LogWriter/log4cplus/include

CFLAGS   +=   -DUNICODE
CFLAGS   +=   -DINSIDE_LOG4CPLUS
CFLAGS   +=   -DLOG4CPLUS_STATIC

all:
	$(CC) $(CFLAGS) -c  LogObserver.cpp
	$(CC) $(CFLAGS) -c  Module.cpp
	$(CC) $(CFLAGS) -c  Plugin.cpp
	$(CC) $(C_FLAGS) -o $(PLUGINS_DIR)/libLogWriter.so *.o
clean:
	rm -rf *.so
	rm -rf *.o


