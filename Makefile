ARCHS := i386 x86_64 x86_64h armv6 armv7 armv7s armv7k
CLANG := clang
CC := $(CLANG) -target darwin $(addprefix -arch ,$(ARCHS))
BUILTIN_CC = $(CLANG) -target darwin -arch $(ARCH)
ifeq ($(shell uname),Darwin)
LIBTOOL := libtool
else
LIBTOOL := llvm-libtool-darwin
endif

COMPILER_RT_VERSION := 18.1.7

CFLAGS := -Wall -Wextra -Wpedantic
OPTFLAGS := -g
LDFLAGS := -static
ifneq ($(shell uname),Darwin)
LDFLAGS += -fuse-ld=ld64 -mlinker-version=951.9
endif

SRCS := $(wildcard src/*/*.c)
ASMS := $(wildcard src/*/*.S)
OBJS := $(SRCS:.c=.o) $(ASMS:.S=.o)
TESTSRCS := $(wildcard tests/*.c)
TESTEXES := $(TESTSRCS:tests/%.c=tests/bin/%)

HEADERS := $(wildcard include/*.h) $(wildcard include/*/*.h)

ifndef VERBOSE
V := @
endif

.PHONY: all release tests clean clangd

all: sdk/usr/include sdk/usr/lib

release: OPTFLAGS := -O2
release: all

tests: $(TESTEXES)

sdk/usr/include: $(HEADERS)
	@printf "Installing headers...\n"
	$(V)rm -rf sdk/usr/include
	$(V)mkdir -p sdk/usr
	$(V)cp -r include sdk/usr

sdk/usr/lib: crt/crt0.o src/libc.a
	@printf "Installing libraries...\n"
	$(V)rm -rf sdk/usr/lib
	$(V)mkdir -p sdk/usr/lib
	$(V)cp src/libc.a sdk/usr/lib
	$(V)cp crt/crt0.o sdk/usr/lib
	$(V)for lib in libSystem.a libgcc_s.1.a libgcc_s.10.5.a libgcc_s.10.4.a libgcc_static.a; do ln -sf libc.a sdk/usr/lib/$$lib; done
	$(V)for obj in crt1.o crt1.3.1.o crt1.10.5.o crt1.10.6.o; do ln -sf crt0.o sdk/usr/lib/$$obj; done

tests/bin/%: tests/%.c all
	@printf " \033[1;32mCC\033[0m $@\n"
	$(V)$(CC) -isysroot sdk -std=c99 $(CFLAGS) $(OPTFLAGS) -c $< -o tests/$*.o
	$(V)$(CC) -isysroot sdk $(LDFLAGS) $(OPTFLAGS) -lc tests/$*.o -o $@
	$(V)ldid -S $@

src/libc.a: $(ARCHS) $(OBJS)
	@printf " \033[1;34mAR\033[0m %s\n" "libc.a"
	$(V)$(LIBTOOL) -static -o $@ src/*/*.o

compiler-rt:
	@printf "Downloading compiler-rt...\n"
	$(V)rm -rf compiler-rt
	$(V)curl -# -L https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPILER_RT_VERSION)/compiler-rt-$(COMPILER_RT_VERSION).src.tar.xz | xz -d | tar -x
	$(V)mv compiler-rt-$(COMPILER_RT_VERSION).src compiler-rt

x86_64:

x86_64h:

arm64:

arm64e:

i386: ARCH := i386
i386: compiler-rt sdk/usr/include $(HEADERS)
	@$(MAKE) -f arch/$(ARCH)/$(ARCH).mk NOASM=$(NOASM) BUILTIN_CC="$(BUILTIN_CC)" V=$(V) CFLAGS="$(CFLAGS)" OPTFLAGS="$(OPTFLAGS)"

armv6: ARCH := armv6
armv6: compiler-rt sdk/usr/include $(HEADERS)
	@$(MAKE) -f arch/$(ARCH)/$(ARCH).mk NOASM=$(NOASM) BUILTIN_CC="$(BUILTIN_CC)" V=$(V) CFLAGS="$(CFLAGS)" OPTFLAGS="$(OPTFLAGS)"

armv7: ARCH := armv7
armv7: compiler-rt sdk/usr/include $(HEADERS)
	@$(MAKE) -f arch/$(ARCH)/$(ARCH).mk NOASM=$(NOASM) BUILTIN_CC="$(BUILTIN_CC)" V=$(V) CFLAGS="$(CFLAGS)" OPTFLAGS="$(OPTFLAGS)"

armv7s: ARCH := armv7s
armv7s: compiler-rt sdk/usr/include $(HEADERS)
	@$(MAKE) -f arch/$(ARCH)/$(ARCH).mk NOASM=$(NOASM) BUILTIN_CC="$(BUILTIN_CC)" V=$(V) CFLAGS="$(CFLAGS)" OPTFLAGS="$(OPTFLAGS)"

armv7k: ARCH := armv7k
armv7k: compiler-rt sdk/usr/include $(HEADERS)
	@$(MAKE) -f arch/$(ARCH)/$(ARCH).mk NOASM=$(NOASM) BUILTIN_CC="$(BUILTIN_CC)" V=$(V) CFLAGS="$(CFLAGS)" OPTFLAGS="$(OPTFLAGS)"

crt/crt0.o: crt/crt.o crt/start.o
	$(V)printf " \033[1;34mLD\033[0m crt0.o\n"
	$(V)$(CC) -isysroot sdk $(LDFLAGS) $(OPTFLAGS) -nostdlib -r crt/crt.o crt/start.o -o $@

crt/start.o $(ASMS:.S=.o): %.o: %.S $(HEADERS)
	@src=$@; src=$${src##*/}; printf " \033[1;33mAS\033[0m %s\n" "$$src"
	$(V)$(CC) -isysroot sdk -D_UNIQ_LIBC_PRIVATE_API $(OPTFLAGS) -c $< -o $@

%.o: %.c sdk/usr/include $(HEADERS)
	@src=$@; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) -fno-builtin -isysroot sdk -std=c99 -D_UNIQ_LIBC_PRIVATE_API $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	@printf "Cleaning up...\n"
	$(V)rm -rf sdk/* tests/*.o tests/bin/* src/libc.a crt/*.o src/*/*.o

clangd:
	@printf "Generating clangd config...\n"
	$(V)printf 'CompileFlags:\n  Add: [-I$(PWD)/include, -D_UNIQ_LIBC_PRIVATE_API, --target=x86_64-apple-darwin]\n' > .clangd
