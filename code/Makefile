# Makefile

ROOTDIR = ..
include $(ROOTDIR)/config.mk

SUBDIRS = $(filter-out  pkg_Example pkg_UnitTest  bin  pkg_AppUI, $(sort $(dir $(wildcard */))))
CLEANSUBDIRS = $(addsuffix .clean, $(SUBDIRS))

.PHONY:  pkg_Core   pkg_Utility   pkg_Example
all:  pkg_Core   pkg_Utility   pkg_Example

pkg_Core:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C pkg_Core

#pkg_Utility:
#	@echo
#	@echo Making all in subdirectory $@...
#	$(MAKE) -C pkg_Utility

pkg_Example:
	@echo
	@echo Making all in subdirectory $@...
	$(MAKE) -C pkg_Example

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@cd $(basename $@) ; $(MAKE) clean


