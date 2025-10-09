CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -Wpedantic -Wundef -Wshadow -Wconversion \
	-Wdouble-promotion -Wcast-align -Wcast-qual -Wlogical-op -Wpointer-arith \
	-Wformat=2 -Wwrite-strings -Wmissing-declarations -Wmissing-include-dirs \
	-Wmissing-prototypes -Wduplicated-cond -Wduplicated-branches
CPPFLAGS = ${INCS} ${DEPFLAGS}
DEPFLAGS = -MMD -MP

CONFIG ?= debug
ifeq (${CONFIG}, debug)
	CFLAGS += -g3 -O0
	LIB_SUFFIX = d
else ifeq (${CONFIG}, release)
	CFLAGS += -g0 -O3
	CPPFLAGS += -DNDEBUG
	LIB_SUFFIX =
endif

ifdef MARCH_NATIVE
	CFLAGS += -march=native -mtune=native
endif

ifdef V
	Q =
else
	Q = @
endif

SRC = src
BUILD = build

INCS = -Iinclude
SRCS = ${shell find ${SRC} -type f -name '*.c'}
OBJS = ${patsubst ${SRC}/%.c, ${BUILD}/${CONFIG}/%.o, ${SRCS}}
DEPS = ${patsubst ${SRC}/%.c, ${BUILD}/${CONFIG}/%.d, ${SRCS}}

LIB = ${BUILD}/${CONFIG}/libscu${LIB_SUFFIX}.a

.PHONY: all static clean help

all: static

static: ${LIB}

${LIB}: ${OBJS}
	${Q}mkdir -p ${dir $@}
	${Q}ar -rcs $@ $^

${BUILD}/${CONFIG}/%.o: ${SRC}/%.c
	${Q}mkdir -p ${dir $@}
	${Q}${CC} ${CFLAGS} ${CPPFLAGS} -c $< -o $@

clean:
	${Q}rm -rf ${BUILD}

help:
	@echo "Usage: make [TARGET]... [VARIABLE]..."
	@echo ""
	@echo "Targets:"
	@echo "  all     Build all targets (default)."
	@echo "  static  Build a static library."
	@echo "  clean   Remove all build artifacts."
	@echo "  help    Display this help and exit."
	@echo ""
	@echo "Variables:"
	@echo "  CONFIG={debug|release}  Set the build configuration (default: debug)."
	@echo "  MARCH_NATIVE            Enable machine-specific optimizations."
	@echo "  V                       Enable verbose build output."