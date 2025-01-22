CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -Wpedantic -Werror
CPPFLAGS = $(INCS) $(DEPFLAGS)
DEPFLAGS = -MMD -MP
LDFLAGS =
LDLIBS =

ifeq ($(OS), Windows_NT)
    STATIC_LIB_EXT = .lib
    SHARED_LIB_EXT = .dll
    LDLIBS += -lbcrypt
else
    STATIC_LIB_EXT = .a
    SHARED_LIB_EXT = .so
endif

CONFIG ?= release
ifeq ($(CONFIG), debug)
    CFLAGS += -g3 -O0
    LIB_SUFFIX = d
else
    CFLAGS += -g0 -O3
endif

SRC = src
BIN = bin
OBJ = obj

INCS = -Iinclude
SRCS = $(shell find $(SRC) -type f -name '*.c')
STATIC_OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/$(CONFIG)/static/%.o, $(SRCS))
SHARED_OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/$(CONFIG)/shared/%.o, $(SRCS))
STATIC_DEPS = $(patsubst %.o, %.d, $(STATIC_OBJS))
SHARED_DEPS = $(patsubst %.o, %.d, $(SHARED_OBJS))

STATIC_LIB = $(BIN)/$(CONFIG)/static/libscu$(LIB_SUFFIX)$(STATIC_LIB_EXT)
SHARED_LIB = $(BIN)/$(CONFIG)/shared/libscu$(LIB_SUFFIX)$(SHARED_LIB_EXT)

.PHONY: all static shared clean help

all: static shared

static: $(STATIC_LIB)

shared: $(SHARED_LIB)

clean:
	@rm -rf $(BIN) $(OBJ)

help:
	@echo "Usage: make [TARGET]... [VARIABLE]..."
	@echo ""
	@echo "Targets:"
	@echo "  all     Build both a static and shared library (default)."
	@echo "  static  Build only a static library."
	@echo "  shared  Build only a shared library."
	@echo "  clean   Remove all build artifacts."
	@echo "  help    Display this help."
	@echo ""
	@echo "Variables:"
	@echo "  CONFIG={debug|release}  Set the configuration (default = release)."

$(STATIC_LIB): $(STATIC_OBJS)
	@mkdir -p $(dir $@)
	@ar -rcs $@ $^

$(SHARED_LIB): $(SHARED_OBJS)
	@mkdir -p $(dir $@)
	@$(CC) -shared $^ $(LDLIBS) -o $@

$(OBJ)/$(CONFIG)/static/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ)/$(CONFIG)/shared/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -fPIC $(CPPFLAGS) -c $< -o $@

-include $(STATIC_DEPS) $(SHARED_DEPS)