# Included by Makefile

INCLUDE_DIR   =$(ROOTDIR)/code

INSTALL_DIR   =$(ROOTDIR)/code/bin
PLUGINS_DIR   =$(INSTALL_DIR)/plugins
UNITTESTS_DIR =$(INSTALL_DIR)/tests

CC          = g++
CFLAGS     += -g
C_FLAGS    += -Wall -g
CFLAGS_SO   = $(CFLAGS) -fPIC
C_FLAGS_SO  = $(C_FLAGS) -shared -fPIC
