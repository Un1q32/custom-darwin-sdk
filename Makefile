CROSS_PREFIX := armv7-apple-darwin11-

CC := $(CROSS_PREFIX)cc
AR := $(CROSS_PREFIX)ar

CFLAGS := -Wall -Wextra -Werror
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
	cp -r include sdk/usr

src/libc.a: $(OBJS)
	$(AR) rcs $@ $^

src/syscall.o: src/syscall.c
	if [ "$(OPTFLAGS)" = "-O0 -g" ]; then \
		$(CC) -Iinclude $(CFLAGS) $(OPTFLAGS) -c $< -o $@; \
	else \
		$(CC) -Iinclude $(CFLAGS) $(OPTFLAGS) -O1 -c $< -o $@; \
	fi

%.o: %.c
	$(CC) -Iinclude $(CFLAGS) $(OPTFLAGS) -c $< -o $@

clean:
	rm -rf sdk src/*.o crt/*.o src/libc.a
