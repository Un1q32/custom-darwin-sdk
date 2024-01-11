ifeq ($(shell uname),Darwin)
CC := ccache /opt/local/libexec/llvm-17/bin/clang -target armv7-apple-ios
AR := ar
else
CC := clang -target armv7-apple-ios
AR := llvm-ar
endif

CFLAGS := -Wall -Wextra -Werror -std=c89
OPTFLAGS := -O2
LDFLAGS := -mlinker-version=907 -fuse-ld=ld

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)
CRTSRCS := $(wildcard crt/*.c)
CRTOBJS := $(CRTSRCS:.c=.o)
TESTSRCS := $(wildcard tests/*.c)
TESTEXES := $(TESTSRCS:.c=)
TESTEXES := $(subst tests,tests/bin,$(TESTEXES))

HEADERS := $(wildcard include/*.h) $(wildcard include/*/*.h)

ifndef VERBOSE
V := @
endif

.PHONY: all debug tests clean

all: sdk/usr/lib sdk/usr/include

debug: OPTFLAGS := -g
debug: all

sdk/usr/include: $(HEADERS)
	@printf "Installing headers...\n"
	@rm -rf sdk/usr/include
	@mkdir -p sdk/usr
	@cp -r include sdk/usr

sdk/usr/lib: $(CRTOBJS) src/libc.a
	@printf "Installing libraries...\n"
	@rm -rf sdk/usr/lib
	@mkdir -p sdk/usr/lib
	@cp src/libc.a sdk/usr/lib
	@cp $(CRTOBJS) sdk/usr/lib
	@ln -sf libc.a sdk/usr/lib/libSystem.a
	@ln -sf libc.a sdk/usr/lib/libgcc_s.1.a
	@ln -sf crt1.o sdk/usr/lib/crt1.3.1.o

tests: OPTFLAGS := -g
tests: $(TESTEXES)

tests/bin/%: tests/%.c sdk/usr/lib sdk/usr/include
	@src=$<; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) -isysroot sdk $(CFLAGS) $(OPTFLAGS) $(LDFLAGS) -o $@ $<

src/libc.a: $(OBJS)
	@printf " \033[1;34mAR\033[0m %s\n" "libc.a"
	@$(AR) rcs $@ $^

%.o: %.c
	@src=$<; src=$${src##*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"
	$(V)$(CC) -Iinclude $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	@printf "Cleaning up...\n"
	@rm -rf sdk src/*.o crt/*.o src/libc.a tests/bin/*
