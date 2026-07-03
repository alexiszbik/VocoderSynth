# Project Name
TARGET = VocoderSynth

# Sources
CPP_SOURCES = VocoderSynth.cpp \
DaisyYMNK/Display/DisplayManager.cpp \
DaisyYMNK/Mux/Mux16.cpp

# Library Locations
LIBDAISY_DIR = libDaisy
DAISYSP_DIR = DaisySP
# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

