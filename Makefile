CC := clang -target armv7-apple-ios
ifeq ($(shell uname),Darwin)
AR := ar
else
AR := llvm-ar
endif

CFLAGS := -Wall -Wextra -Werror
OPTFLAGS := -O2
LDFLAGS := -mlinker-version=907 -fuse-ld=ld
_REQFLAGS := -isysroot sdk -Iinclude -std=c89

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)
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

sdk/usr/lib: crt/crt1.o src/libc.a
	@printf "Installing libraries...\n"
	@rm -rf sdk/usr/lib
	@mkdir -p sdk/usr/lib
	@cp src/libc.a sdk/usr/lib
	@cp crt/crt1.o sdk/usr/lib
	@ln -sf libc.a sdk/usr/lib/libSystem.a
	@ln -sf libc.a sdk/usr/lib/libgcc_s.1.a
	@ln -sf crt1.o sdk/usr/lib/crt1.3.1.o

tests/bin/%: tests/%.c sdk/usr/lib
	@src=$<; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) $(_REQFLAGS) $(CFLAGS) $(OPTFLAGS) -c $< -o tests/$*.o
	$(V)$(CC) $(_REQFLAGS) $(LDFLAGS) $(OPTFLAGS) -nostdlib -lc -lcrt1.o tests/$*.o -o $@
	$(V)ldid -Sentitlements.xml $@

src/libc.a: $(OBJS)
	@printf " \033[1;34mAR\033[0m %s\n" "libc.a"
	@$(AR) rcs $@ $^

%.o: %.c
	@src=$<; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) $(_REQFLAGS) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	@printf "Cleaning up...\n"
	$(V)rm -rf sdk/* src/*.o crt/*.o tests/*.o tests/bin/* src/libc.a

clangd:
	@printf "Generating clangd config...\n"
	$(V)printf 'CompileFlags:\n  Add: [-I$(PWD)/include, --target=armv6-apple-ios2]\n' > .clangd
