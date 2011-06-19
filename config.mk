# Included by Makefile

INCLUDE_DIR   =$(ROOTDIR)/code
PLUGINS_DIR   =$(ROOTDIR)/code/bin/Plugins
UNITTESTS_DIR =$(ROOTDIR)/code/bin/UnitTests

C_FLAGS += -Wall -g -shared -fPIC
CC = g++
