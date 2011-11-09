# Makefile

ROOTDIR = ../../..
include $(ROOTDIR)/config.mk

SUBDIRS = $(filter-out Public/ HookManager/ ComHook/, $(sort $(dir $(wildcard */))))
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))

.PHONY: x3core
all: x3core

x3core:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C x3core

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@cd $(basename $@) ; $(MAKE) clean
