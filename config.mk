HOME=/root

# The installation directory of the DVSDK
DVSDK_INSTALL_DIR=$(HOME)/x3c

CODE_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/code
INCLUDE_DIR   =$(CODE_INSTALL_DIR)
PLUGINS_DIR   =$(CODE_INSTALL_DIR)/bin/Plugins
UNITTESTS_DIR =$(CODE_INSTALL_DIR)/bin/UnitTests

C_FLAGS += -Wall -g -shared
CC = g++
