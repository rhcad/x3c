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
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/appender.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/appenderattachableimpl.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/configurator.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/consoleappender.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/factory.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/fileappender.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/filter.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/global-init.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/hierarchy.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/hierarchylocker.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/layout.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/logger.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/loggerimpl.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/loggingevent.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/loglevel.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/loglog.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/logloguser.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/ndc.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/nteventlogappender.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/nullappender.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/objectregistry.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/patternlayout.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/pointer.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/property.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/rootlogger.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/sleep.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/socket-unix.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/socket.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/socketappender.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/socketbuffer.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/stringhelper.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/syncprims.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/syslogappender.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/threads.cxx
	$(CC) $(CFLAGS_SO) -c  log4cplus/src/timehelper.cxx
	$(CC) $(C_FLAGS_SO) -o $(PLUGINS_DIR)/libLogWriter.so *.o
clean:
	rm -rf *.so
	rm -rf *.o
