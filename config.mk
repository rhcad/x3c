# Included by Makefile

INCLUDE_DIR   =$(ROOTDIR)/code

INSTALL_DIR   =$(ROOTDIR)/code/bin
PLUGINS_DIR   =$(INSTALL_DIR)/Plugins
UNITTESTS_DIR =$(INSTALL_DIR)/UnitTests

CC = g++
CFLAGS  += -g
C_FLAGS += -Wall -g
C_FLAGS_SO = $(C_FLAGS) -shared -fpic
