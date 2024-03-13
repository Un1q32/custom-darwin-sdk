ARCH := i386
BUILTINS := udivdi3 umoddi3 fixunsxfdi
_BUILTINS := $(addprefix src/$(ARCH)-,$(addsuffix .o,$(BUILTINS)))
BCC = $(V)src=$@; src=$${src\#\#*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"; $(_BUILTIN_CC) $@ $<

.PHONY: all

all: $(_BUILTINS)

src/$(ARCH)-fixunsxfdi.o: compiler-rt/lib/builtins/fixunsxfdi.c
	$(BCC)

ifdef NOASM

src/$(ARCH)-udivdi3.o: compiler-rt/lib/builtins/udivdi3.c
	$(BCC)

src/$(ARCH)-umoddi3.o: compiler-rt/lib/builtins/umoddi3.c
	$(BCC)

else

src/$(ARCH)-udivdi3.o: compiler-rt/lib/builtins/i386/udivdi3.S
	$(BCC)

src/$(ARCH)-umoddi3.o: compiler-rt/lib/builtins/i386/umoddi3.S
	$(BCC)

endif
