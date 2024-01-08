CC := clang -target armv7-apple-darwin
AR := llvm-ar

CFLAGS := -Wall -Wextra -Werror -std=c89
OPTFLAGS := -O2

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)
CRTSRCS := $(wildcard crt/*.c)
CRTOBJS := $(CRTSRCS:.c=.o)

.PHONY: all debug crt sdk clean

all: src/libc.a $(CRTOBJS)

debug: OPTFLAGS := -O0 -g
debug: all

sdk: all
	mkdir -p sdk/usr/lib
	cp src/libc.a sdk/usr/lib
	cp crt/*.o sdk/usr/lib
	ln -sf libc.a sdk/usr/lib/libSystem.a
	ln -sf libc.a sdk/usr/lib/libgcc_s.1.a
	ln -sf crt1.o sdk/usr/lib/crt1.3.1.o
	cp -r include sdk/usr

src/libc.a: $(OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) -Iinclude $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	rm -rf sdk src/*.o crt/*.o src/libc.a
