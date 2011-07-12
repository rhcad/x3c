# Makefile

ROOTDIR = ../../..
include $(ROOTDIR)/config.mk

SUBDIRS = $(filter-out Public/, $(sort $(dir $(wildcard */))))
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))


.PHONY: TestCore  TestUtility  TestPlatform
all: TestCore  TestUtility  TestPlatform

TestCore:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C TestCore

TestUtility:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C TestUtility

TestPlatform:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C TestPlatform

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@cd $(basename $@) ; $(MAKE) clean
