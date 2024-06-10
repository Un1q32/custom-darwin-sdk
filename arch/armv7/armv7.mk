ARCH := armv7
BUILTINS := fixunsdfdi floatundidf udivdi3 umoddi3 umodsi3 modsi3 divsi3 udivsi3
_BUILTINS := $(addprefix src/builtins/$(ARCH)-,$(addsuffix .o,$(BUILTINS)))
BCC = $(V)src=$@; src=$${src\#\#*/}; printf " \033[1;32mCC\033[0m %s\n" "$$src"; $(BUILTIN_CC) -isysroot sdk -std=c99 $(CFLAGS) $(OPTFLAGS) -c -o $@ $<

.PHONY: all

all: $(_BUILTINS)

src/builtins/$(ARCH)-fixunsdfdi.o: compiler-rt/lib/builtins/fixunsdfdi.c
	$(BCC)

src/builtins/$(ARCH)-floatundidf.o: compiler-rt/lib/builtins/floatundidf.c
	$(BCC)

src/builtins/$(ARCH)-udivdi3.o: compiler-rt/lib/builtins/udivdi3.c
	$(BCC)

src/builtins/$(ARCH)-umoddi3.o: compiler-rt/lib/builtins/umoddi3.c
	$(BCC)

ifdef NOASM

src/builtins/$(ARCH)-umodsi3.o: compiler-rt/lib/builtins/umodsi3.c
	$(BCC)

src/builtins/$(ARCH)-modsi3.o: compiler-rt/lib/builtins/modsi3.c
	$(BCC)

src/builtins/$(ARCH)-divsi3.o: compiler-rt/lib/builtins/divsi3.c
	$(BCC)

src/builtins/$(ARCH)-udivsi3.o: compiler-rt/lib/builtins/udivsi3.c
	$(BCC)

else

src/builtins/$(ARCH)-umodsi3.o: compiler-rt/lib/builtins/arm/umodsi3.S
	$(BCC)

src/builtins/$(ARCH)-modsi3.o: compiler-rt/lib/builtins/arm/modsi3.S
	$(BCC)

src/builtins/$(ARCH)-divsi3.o: compiler-rt/lib/builtins/arm/divsi3.S
	$(BCC)

src/builtins/$(ARCH)-udivsi3.o: compiler-rt/lib/builtins/arm/udivsi3.S
	$(BCC)

endif
