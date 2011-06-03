# Makefile

ROOTDIR = ../../..
include $(ROOTDIR)/config.mk

SUBDIRS = $(filter-out Public/, $(sort $(dir $(wildcard */))))
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))


.PHONY: TestCore

TestCore:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C TestCore

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@cd $(basename $@) ; $(MAKE) clean


