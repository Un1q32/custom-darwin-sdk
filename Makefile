ARCHS := i386 x86_64 x86_64h armv6 armv7 armv7s armv7k
CLANG := clang
CC := $(CLANG) -target darwin $(addprefix -arch ,$(ARCHS))
BUILTIN_CC = $(CLANG) -target darwin -arch $(ARCH)
_BUILTIN_CC = $(BUILTIN_CC) -isysroot sdk -std=c99 $(CFLAGS) $(OPTFLAGS) -c -o
ifeq ($(shell uname),Darwin)
LIBTOOL := libtool
else
LIBTOOL := llvm-libtool-darwin
endif

COMPILER_RT_VERSION := 18.1.2

CFLAGS := -Wall -Wextra -Wpedantic -Werror -Iinclude
OPTFLAGS := -g
LDFLAGS := -mlinker-version=907 -static
ifneq ($(shell uname),Darwin)
LDFLAGS += -fuse-ld=ld64
endif

SRCS := $(wildcard src/*.c)
ASMS := $(wildcard src/*.S)
OBJS := $(SRCS:.c=.o) $(ASMS:.S=.o)
TESTSRCS := $(wildcard tests/*.c)
TESTEXES := $(TESTSRCS:tests/%.c=tests/bin/%)

HEADERS := $(wildcard include/*.h) $(wildcard include/*/*.h)

ifndef VERBOSE
V := @
endif

ifdef NOCODESIGN
CS := \#
endif

.PHONY: all debug tests clean clangd

all: sdk/usr/include sdk/usr/lib

release: OPTFLAGS := -O2
release: all

tests: $(TESTEXES)

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
	$(V)for lib in libSystem.a libgcc_s.1.a libgcc_s.10.5.a libgcc_s.10.4.a libgcc_static.a libm.a; do ln -sf libc.a sdk/usr/lib/$$lib; done
	$(V)for obj in crt0.o crt1.o crt1.3.1.o crt1.10.5.o crt1.10.6.o; do ln -sf start.o sdk/usr/lib/$$obj; done

tests/bin/%: tests/%.c all
	@printf " \033[1;32mCC\033[0m $@\n"
	$(V)$(CC) -isysroot sdk -std=c99 $(CFLAGS) $(OPTFLAGS) -c $< -o tests/$*.o
	$(V)$(CC) -isysroot sdk $(LDFLAGS) $(OPTFLAGS) -nostdlib -lstart.o -lc tests/$*.o -o $@
	$(V)$(CS)ldid -S $@

src/libc.a: $(ARCHS) $(OBJS)
	@printf " \033[1;34mAR\033[0m %s\n" "libc.a"
	$(V)$(LIBTOOL) -static -o $@ src/*.o

compiler-rt:
	@printf "Downloading compiler-rt...\n"
	$(V)curl -# -L https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPILER_RT_VERSION)/compiler-rt-$(COMPILER_RT_VERSION).src.tar.xz | xz -d | tar -x
	$(V)mv compiler-rt-$(COMPILER_RT_VERSION).src compiler-rt

x86_64:

x86_64h:

i386: ARCH := i386
i386: compiler-rt sdk/usr/include
	@$(MAKE) -f make/$(ARCH).mk NOASM=$(NOASM) _BUILTIN_CC="$(_BUILTIN_CC)" V=$(V)

armv6: ARCH := armv6
armv6: compiler-rt sdk/usr/include
	@$(MAKE) -f make/$(ARCH).mk NOASM=$(NOASM) _BUILTIN_CC="$(_BUILTIN_CC)" V=$(V)

armv7: ARCH := armv7
armv7: compiler-rt sdk/usr/include
	@$(MAKE) -f make/$(ARCH).mk NOASM=$(NOASM) _BUILTIN_CC="$(_BUILTIN_CC)" V=$(V)

armv7s: ARCH := armv7s
armv7s: compiler-rt sdk/usr/include
	@$(MAKE) -f make/$(ARCH).mk NOASM=$(NOASM) _BUILTIN_CC="$(_BUILTIN_CC)" V=$(V)

armv7k: ARCH := armv7k
armv7k: compiler-rt sdk/usr/include
	@$(MAKE) -f make/$(ARCH).mk NOASM=$(NOASM) _BUILTIN_CC="$(_BUILTIN_CC)" V=$(V)

crt/start.o $(ASMS:.S=.o): %.o: %.S
	@src=$@; src=$${src##*/}; printf " \033[1;33mAS\033[0m %s\n" "$$src"
	$(V)$(CC) -ffreestanding -isysroot sdk $(OPTFLAGS) -c $< -o $@

%.o: %.c sdk/usr/include
	@src=$@; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) -ffreestanding -isysroot sdk -std=c99 $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	@printf "Cleaning up...\n"
	$(V)rm -rf sdk/* tests/*.o tests/bin/* src/libc.a crt/*.o src/*.o

clangd:
	@printf "Generating clangd config...\n"
	$(V)printf 'CompileFlags:\n  Add: [-I$(PWD)/include, --target=x86_64-apple-darwin]\n' > .clangd
