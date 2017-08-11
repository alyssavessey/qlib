LIBRARY = qlib.a
PROJECT = qlib.a
PLATFORM := $(shell uname)
PRJ_DIR = $(PLATFORM)
OBJ_DIR = build
SRC_DIR = src
FAST    = -O3   # optimize
DEBUG   = -g -gdwarf-2
SANITIZE = 0
ifeq ($(PLATFORM),Darwin)
    DARWIN_VERSION := $(shell sw_vers | grep ProductVersion | cut -d. -f2)
endif

INC_DIR = \
    . \
    ./sort \
    ./thread

SOURCES = \
    thread/mutex.cpp \
    thread/thread.cpp

CFLAGS  = -Wall
CFLAGS += $(DEBUG)
CFLAGS += $(FAST)
CFLAGS += -D_LINUX
CFLAGS += -std=c++14

CC      = gcc
CL      = g++

# create list of object files from list of source files with form: build/source.cpp.o
_OBJECT = $(patsubst %,$(OBJ_DIR)/%,$(SOURCES:.cpp=.cpp.o))

# create list of object files from list of source files with form: build/main.cpp.o
#_MAIN = $(patsubst %,$(OBJ_DIR)/%,$(MAIN:.cpp=.cpp.o))

# prepend project directory to name of final output file
_OUTPUT = $(PRJ_DIR)/$(PROJECT)

# prepend project directory to name of library file
_LIBRARY = $(PRJ_DIR)/lib/$(LIBRARY)

.PHONY: all
all: $(_OUTPUT)

$(OBJ_DIR)/%.cpp.o: %.cpp
	mkdir -p $(shell dirname $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(_OUTPUT): $(_MAIN) $(_LIBRARY)
	mkdir -p $(shell dirname $@)

$(_LIBRARY): $(_OBJECT)
	mkdir -p $(shell dirname $@)
ifeq ($(PLATFORM),Darwin)
	libtool -o $@ -static $^ $(DEBUG)
else
	$(AR) -rsc $@ $^
endif

.PHONY: clean
clean:
	-rm -f $(_OUTPUT) $(_LIBRARY) $(_OBJECT) $(_MAIN)
