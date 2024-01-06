CC := $(CROSS_PREFIX)cc
AR := $(CROSS_PREFIX)ar

CFLAGS := -Wall -Wextra -Werror -O2 -g

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)

.PHONY: all sdk clean

all: src/libc.a

sdk: all
	mkdir -p sdk/usr/lib
	cp src/libc.a sdk/usr/lib
	ln -sf libc.a sdk/usr/lib/libSystem.a
	cp *.o sdk/usr/lib
	cp -r include sdk/usr

src/libc.a: $(OBJS)
	$(AR) rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	rm -rf sdk src/*.o src/libc.a
