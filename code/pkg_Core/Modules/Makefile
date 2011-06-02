# Makefile

ROOTDIR = ../../..
include $(ROOTDIR)/config.mk

SUBDIRS = $(filter-out Interface/, $(sort $(dir $(wildcard */))))
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))

.PHONY: ChangeManager  ConfigXml  FileUtility  LogManager  LogWriter  PluginManager  StringTable  TextUtility
all: ChangeManager  ConfigXml  FileUtility  LogManager  LogWriter  PluginManager  StringTable  TextUtility

ChangeManager:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C ChangeManager

ConfigXml:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C ConfigXml

FileUtility:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C FileUtility

LogManager:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C LogManager

LogWriter:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C LogWriter

PluginManager:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C PluginManager

StringTable:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C StringTable

TextUtility:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C TextUtility

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@cd $(basename $@) ; $(MAKE) clean


