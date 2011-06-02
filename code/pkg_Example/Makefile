# Makefile

ROOTDIR = ../..
include $(ROOTDIR)/config.mk

SUBDIRS = $(filter-out Interface/, $(sort $(dir $(wildcard */))))
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))

.PHONY: Modules

Modules:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C Modules

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@cd $(basename $@) ; $(MAKE) clean


