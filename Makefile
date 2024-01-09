CC := clang -target armv7-apple-darwin --no-default-config
AR := llvm-ar

CFLAGS := -Wall -Wextra -Werror -std=c89
OPTFLAGS := -O2
LDFLAGS := -mlinker-version=907

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)
CRTSRCS := $(wildcard crt/*.c)
CRTOBJS := $(CRTSRCS:.c=.o)
TESTSRCS := $(wildcard tests/*.c)
TESTEXES := $(TESTSRCS:.c=)
TESTEXES := $(subst tests,tests/bin,$(TESTEXES))

HEADERS := $(wildcard include/*.h) $(wildcard include/*/*.h)

.PHONY: all debug tests clean

all: sdk/usr/include sdk/usr/lib

debug: OPTFLAGS := -O0 -g
debug: all

sdk/usr/include: $(HEADERS)
	mkdir -p sdk/usr
	cp -r include sdk/usr

sdk/usr/lib: src/libc.a $(CRTOBJS)
	mkdir -p sdk/usr/lib
	cp src/libc.a sdk/usr/lib
	cp crt/*.o sdk/usr/lib
	ln -sf libc.a sdk/usr/lib/libSystem.a
	ln -sf libc.a sdk/usr/lib/libgcc_s.1.a
	ln -sf crt1.o sdk/usr/lib/crt1.3.1.o

tests: $(TESTEXES)

$(TESTEXES): $(TESTSRCS) all
	$(CC) -isysroot sdk $(CFLAGS) $(OPTFLAGS) $(LDFLAGS) $< -o $@

src/libc.a: $(OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) -Iinclude $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	rm -rf sdk src/*.o crt/*.o src/libc.a $(TESTEXES)
