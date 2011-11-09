# Makefile

ROOTDIR = ..
include $(ROOTDIR)/config.mk

SUBDIRS = $(filter-out  bin/  pkg_Utility/  pkg_AppUI/, $(sort $(dir $(wildcard */))))
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))

.PHONY:  pkg_Core   pkg_Example   pkg_UnitTest  pkg_Platform
all:  pkg_Core   pkg_Utility   pkg_Example   pkg_UnitTest  pkg_Platform

pkg_Core:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C pkg_Core

pkg_Example:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C pkg_Example

#pkg_UnitTest:
#	@echo
#	@echo Making all in subdirectory $@...
#	$(MAKE) -C pkg_UnitTest

pkg_Platform:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C pkg_Platform

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@cd $(basename $@) ; $(MAKE) clean
