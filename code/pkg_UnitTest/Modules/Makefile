# Makefile

ROOTDIR = ../../..
include $(ROOTDIR)/config.mk

SUBDIRS = $(sort $(dir $(wildcard */)))
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))


.PHONY: Public TestCore

Public:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C Public

TestCore:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C TestCore

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@cd $(basename $@) ; $(MAKE) clean


