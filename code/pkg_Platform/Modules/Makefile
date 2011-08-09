# Makefile

ROOTDIR = ../../..
include $(ROOTDIR)/config.mk

SUBDIRS = $(filter-out Public/ x3core/, $(sort $(dir $(wildcard */))))
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))

.PHONY: ComHook
all: ComHook

ComHook:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C ComHook

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@cd $(basename $@) ; $(MAKE) clean
