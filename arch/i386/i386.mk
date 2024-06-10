ARCH := i386
BUILTINS := udivdi3 umoddi3 fixunsxfdi
_BUILTINS := $(addprefix src/builtins/$(ARCH)-,$(addsuffix .o,$(BUILTINS)))
BCC = $(V)src=$@; src=$${src\#\#*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"; $(BUILTIN_CC) -isysroot sdk -std=c99 $(CFLAGS) $(OPTFLAGS) -c -o $@ $<
BAS = $(V)src=$@; src=$${src\#\#*/}; printf " \033[1;33mAS\033[0m %s\n" "$$src"; $(BUILTIN_CC) -isysroot sdk $(OPTFLAGS) -c -o $@ $<

2003 := fopen fputs nanosleep strerror strtod fwrite

.PHONY: all

all: $(_BUILTINS) $(addprefix src/builtins/$(ARCH)-,$(addsuffix 2003.o,$(2003)))

src/builtins/$(ARCH)-fixunsxfdi.o: compiler-rt/lib/builtins/fixunsxfdi.c
	$(BCC)

ifdef NOASM

src/builtins/$(ARCH)-udivdi3.o: compiler-rt/lib/builtins/udivdi3.c
	$(BCC)

src/builtins/$(ARCH)-umoddi3.o: compiler-rt/lib/builtins/umoddi3.c
	$(BCC)

else

src/builtins/$(ARCH)-udivdi3.o: compiler-rt/lib/builtins/i386/udivdi3.S
	$(BCC)

src/builtins/$(ARCH)-umoddi3.o: compiler-rt/lib/builtins/i386/umoddi3.S
	$(BCC)

endif

src/builtins/$(ARCH)-fopen2003.o: arch/i386/fopen2003.S
	$(BAS)

src/builtins/$(ARCH)-fputs2003.o: arch/i386/fputs2003.S
	$(BAS)

src/builtins/$(ARCH)-nanosleep2003.o: arch/i386/nanosleep2003.S
	$(BAS)

src/builtins/$(ARCH)-strerror2003.o: arch/i386/strerror2003.S
	$(BAS)

src/builtins/$(ARCH)-strtod2003.o: arch/i386/strtod2003.S
	$(BAS)

src/builtins/$(ARCH)-fwrite2003.o: arch/i386/fwrite2003.S
	$(BAS)
