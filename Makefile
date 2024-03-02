ARCHS := x86_64 armv6 armv7 armv7s
_ARCHS := $(addprefix -arch ,$(ARCHS))
CLANG := clang
CC := $(CLANG) -target darwin $(_ARCHS)
BUILTIN_CC = $(CLANG) -target darwin -arch $(_ARCH)
ifeq ($(shell uname),Darwin)
LIBTOOL := libtool
else
LIBTOOL := llvm-libtool-darwin
endif

COMPILER_RT_VERSION := 17.0.6

CFLAGS := -Wall -Wextra -Werror
OPTFLAGS := -O2
LDFLAGS := -mlinker-version=907 -static
ifneq ($(shell uname),Darwin)
LDFLAGS += -fuse-ld=ld64
endif
_REQFLAGS := -isysroot sdk -Iinclude -std=c99

SRCS := $(wildcard src/*.c)
ASMS := $(wildcard src/*.S)
OBJS := $(SRCS:.c=.o) $(ASMS:.S=.o)
TESTSRCS := $(wildcard tests/*.c)
TESTEXES := $(TESTSRCS:tests/%.c=tests/bin/%)

X86_64_BUILTINS :=
ifdef NOASM
ARMV7S_BUILTINS := fixunsdfdi.c floatundidf.c udivdi3.c umoddi3.c umodsi3.c modsi3.c
ARMV7_BUILTINS := $(ARMV7S_BUILTINS) udivsi3.c divsi3.c
ARMV6_BUILTINS := $(ARMV7_BUILTINS) clzdi2.c
else
ARMV7S_BUILTINS := fixunsdfdi.c floatundidf.c udivdi3.c umoddi3.c arm/umodsi3.S arm/modsi3.S
ARMV7_BUILTINS := $(ARMV7S_BUILTINS) arm/udivsi3.S arm/divsi3.S
ARMV6_BUILTINS := $(ARMV7_BUILTINS)
endif

HEADERS := $(wildcard include/*.h) $(wildcard include/*/*.h)

ifndef VERBOSE
V := @
endif

.PHONY: all debug tests clean clangd

all: sdk/usr/lib sdk/usr/include

debug: OPTFLAGS := -g
debug: all

tests: OPTFLAGS := -g
tests: all $(TESTEXES)

sdk/usr/include: $(HEADERS)
	@printf "Installing headers...\n"
	$(V)rm -rf sdk/usr/include
	$(V)mkdir -p sdk/usr
	$(V)cp -r include sdk/usr

sdk/usr/lib: src/libc.a crt/start.o
	@printf "Installing libraries...\n"
	$(V)rm -rf sdk/usr/lib
	$(V)mkdir -p sdk/usr/lib
	$(V)cp src/libc.a sdk/usr/lib
	$(V)cp crt/start.o sdk/usr/lib
	$(V)for lib in libSystem.a libgcc_s.1.a libm.a; do ln -sf libc.a sdk/usr/lib/$$lib; done
	$(V)for obj in crt0.o crt1.o crt1.3.1.o crt1.10.5.o crt1.10.6.o; do ln -sf start.o sdk/usr/lib/$$obj; done

tests/bin/%: tests/%.c sdk/usr/lib
	@src=$<; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) $(_REQFLAGS) $(CFLAGS) $(OPTFLAGS) -c $< -o tests/$*.o
	$(V)$(CC) $(_REQFLAGS) $(LDFLAGS) $(OPTFLAGS) -nostdlib -lc -lstart.o tests/$*.o -o $@
	$(V)ldid -S $@

src/libc.a: $(ARCHS) $(OBJS)
	@printf " \033[1;34mAR\033[0m %s\n" "libc.a"
	$(V)$(LIBTOOL) -static -o $@ src/*.o

compiler-rt:
	@printf "Downloading compiler-rt...\n"
	$(V)curl -# -L https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPILER_RT_VERSION)/compiler-rt-$(COMPILER_RT_VERSION).src.tar.xz | xz -d | tar -x
	$(V)mv compiler-rt-$(COMPILER_RT_VERSION).src compiler-rt

x86_64: _ARCH := x86_64
x86_64: compiler-rt
	@printf "Building x86_64 builtins...\n"
	$(V)for src in $(X86_64_BUILTINS); do \
		_src=$${src##*/}; _src=$${_src%.*}; \
		$(BUILTIN_CC) $(_REQFLAGS) $(CFLAGS) $(OPTFLAGS) -c compiler-rt/lib/builtins/$$src -o src/$(_ARCH)-$$_src.o; \
	done

armv6: _ARCH := armv6
armv6: compiler-rt
	@printf "Building armv6 builtins...\n"
	$(V)for src in $(ARMV6_BUILTINS); do \
		_src=$${src##*/}; _src=$${_src%.*}; \
		$(BUILTIN_CC) $(_REQFLAGS) $(CFLAGS) $(OPTFLAGS) -c compiler-rt/lib/builtins/$$src -o src/$(_ARCH)-$$_src.o; \
	done

armv7: _ARCH := armv7
armv7: compiler-rt
	@printf "Building armv7 builtins...\n"
	$(V)for src in $(ARMV7_BUILTINS); do \
		_src=$${src##*/}; _src=$${_src%.*}; \
		$(BUILTIN_CC) $(_REQFLAGS) $(CFLAGS) $(OPTFLAGS) -c compiler-rt/lib/builtins/$$src -o src/$(_ARCH)-$$_src.o; \
	done

armv7s: _ARCH := armv7s
armv7s: compiler-rt
	@printf "Building armv7s builtins...\n"
	$(V)for src in $(ARMV7S_BUILTINS); do \
		_src=$${src##*/}; _src=$${_src%.*}; \
		$(BUILTIN_CC) $(_REQFLAGS) $(CFLAGS) $(OPTFLAGS) -c compiler-rt/lib/builtins/$$src -o src/$(_ARCH)-$$_src.o; \
	done

crt/start.o $(ASMS:.S=.o): %.o: %.S
	@src=$<; src=$${src##*/}; printf " \033[1;33mAS\033[0m %s\n" "$$src"
	$(V)$(CC) -ffreestanding $(_REQFLAGS) $(OPTFLAGS) -c $< -o $@

%.o: %.c
	@src=$<; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) -ffreestanding $(_REQFLAGS) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	@printf "Cleaning up...\n"
	$(V)rm -rf sdk/* tests/*.o tests/bin/* src/libc.a crt/*.o src/*.o

clangd:
	@printf "Generating clangd config...\n"
	$(V)printf 'CompileFlags:\n  Add: [-I$(PWD)/include, --target=x86_64-apple-darwin10]\n' > .clangd
