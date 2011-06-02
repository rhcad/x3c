CC=g++

.PHONY:  clean  ChangeObserver Log Module PluginManager Portability UtilFunc Utility Xml

all:  ChangeObserver Log Module PluginManager Portability UtilFunc Utility Xml

ChangeObserver:
	@echo
	@echo Making all in subdirectory $@...
	@$(MAKE) -C ChangeObserver

Log:
	@echo
	@echo Making all in subdirectory $@...
	@$(MAKE) -C Log

Module:
	@echo
	@echo Making all in subdirectory $@...
	@$(MAKE) -C Module

PluginManager:
	@echo
	@echo Making all in subdirectory $@...
	@$(MAKE) -C PluginManager

Portability:
	@echo
	@echo Making all in subdirectory $@...
	@$(MAKE) -C Portability

UtilFunc:
	@echo
	@echo Making all in subdirectory $@...
	@$(MAKE) -C UtilFunc

Utility:
	@echo
	@echo Making all in subdirectory $@...
	@$(MAKE) -C Utility

Xml:
	@echo
	@echo Making all in subdirectory $@...
	@$(MAKE) -C Xml

clean:	$(CLEANSUBDIRS)

$(CLEANSUBDIRS):
	@cd $(basename $@) ; $(MAKE) clean

