# Makefile

ROOTDIR = ../../..
include $(ROOTDIR)/config.mk

SUBDIRS = $(sort $(dir $(wildcard */)))
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))

.PHONY: ConfigDB 

ConfigDB:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C ConfigDB


clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@cd $(basename $@) ; $(MAKE) clean


