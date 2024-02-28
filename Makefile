CC := clang -target darwin -arch x86_64 -arch armv6 -arch armv7 -arch armv7s
ifeq ($(shell uname),Darwin)
AR := ar
else
AR := cctools-ar
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
_BUILTINS := divsi3 udivsi3 udivdi3 modsi3 umoddi3 umodsi3 fixunsdfdi floatundidf clzdi2
BUILTINS := $(addprefix compiler-rt/lib/builtins/,$(addsuffix .c,$(_BUILTINS)))
OBJS := $(ASMS:.S=.o) $(BUILTINS:.c=.o) $(SRCS:.c=.o)
TESTSRCS := $(wildcard tests/*.c)
TESTEXES := $(TESTSRCS:tests/%.c=tests/bin/%)

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
	@rm -rf sdk/usr/include
	@mkdir -p sdk/usr
	@cp -r include sdk/usr

sdk/usr/lib: crt/start.o src/libc.a
	@printf "Installing libraries...\n"
	@rm -rf sdk/usr/lib
	@mkdir -p sdk/usr/lib
	@cp src/libc.a sdk/usr/lib
	@cp crt/start.o sdk/usr/lib
	@for lib in libSystem.a libgcc_s.1.a libm.a; do ln -sf libc.a sdk/usr/lib/$$lib; done
	@for obj in crt0.o crt1.o crt1.3.1.o crt1.10.5.o crt1.10.6.o; do ln -sf start.o sdk/usr/lib/$$obj; done

tests/bin/%: tests/%.c sdk/usr/lib
	@src=$<; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) $(_REQFLAGS) $(CFLAGS) $(OPTFLAGS) -c $< -o tests/$*.o
	$(V)$(CC) $(_REQFLAGS) $(LDFLAGS) $(OPTFLAGS) -nostdlib -lc -lstart.o tests/$*.o -o $@
	$(V)ldid -S $@

src/libc.a: $(OBJS)
	@printf " \033[1;34mAR\033[0m %s\n" "libc.a"
	@$(AR) rcs $@ $^ 2>/dev/null

$(BUILTINS): compiler-rt
compiler-rt:
	@printf "Downloading compiler-rt...\n"
	$(V)curl -# -L https://github.com/llvm/llvm-project/releases/download/llvmorg-$(COMPILER_RT_VERSION)/compiler-rt-$(COMPILER_RT_VERSION).src.tar.xz | tar -xJ
	$(V)mv compiler-rt-$(COMPILER_RT_VERSION).src compiler-rt

$(BUILTINS:.c=.o): %.o: %.c
	@src=$<; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) $(_REQFLAGS) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

crt/start.o $(ASMS:.S=.o): %.o: %.S
	@src=$<; src=$${src##*/}; printf " \033[1;33mAS\033[0m %s\n" "$$src"
	$(V)$(CC) -ffreestanding $(_REQFLAGS) $(OPTFLAGS) -c $< -o $@

%.o: %.c
	@src=$<; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) -ffreestanding $(_REQFLAGS) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	@printf "Cleaning up...\n"
	$(V)rm -rf sdk/* tests/*.o tests/bin/* src/libc.a crt/*.o $(OBJS)

clangd:
	@printf "Generating clangd config...\n"
	$(V)printf 'CompileFlags:\n  Add: [-I$(PWD)/include, --target=x86_64-apple-darwin10]\n' > .clangd
