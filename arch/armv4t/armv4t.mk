ARCH := armv4t
BUILTINS := fixunsdfdi floatundidf udivdi3 umoddi3 umodsi3 modsi3 divsi3 udivsi3 clzdi2 fixdfsi muldf3 floatsidf subdf3 comparedf2 adddf3 fp_mode addsf3 clzsi2 divsf3 extendsfdf2 fixsfsi comparesf2 mulsf3 subsf3 truncdfsf2
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

src/builtins/$(ARCH)-fixdfsi.o: compiler-rt/lib/builtins/fixdfsi.c
	$(BCC)

src/builtins/$(ARCH)-muldf3.o: compiler-rt/lib/builtins/muldf3.c
	$(BCC)

src/builtins/$(ARCH)-floatsidf.o: compiler-rt/lib/builtins/floatsidf.c
	$(BCC)

src/builtins/$(ARCH)-subdf3.o: compiler-rt/lib/builtins/subdf3.c
	$(BCC)

src/builtins/$(ARCH)-comparedf2.o: compiler-rt/lib/builtins/comparedf2.c
	$(BCC)

src/builtins/$(ARCH)-adddf3.o: compiler-rt/lib/builtins/adddf3.c
	$(BCC)

src/builtins/$(ARCH)-fp_mode.o: compiler-rt/lib/builtins/arm/fp_mode.c
	$(BCC)

src/builtins/$(ARCH)-divsf3.o: compiler-rt/lib/builtins/divsf3.c
	$(BCC)

src/builtins/$(ARCH)-extendsfdf2.o: compiler-rt/lib/builtins/extendsfdf2.c
	$(BCC)

src/builtins/$(ARCH)-fixsfsi.o: compiler-rt/lib/builtins/fixsfsi.c
	$(BCC)

src/builtins/$(ARCH)-comparesf2.o: compiler-rt/lib/builtins/comparesf2.c
	$(BCC)

src/builtins/$(ARCH)-mulsf3.o: compiler-rt/lib/builtins/mulsf3.c
	$(BCC)

src/builtins/$(ARCH)-subsf3.o: compiler-rt/lib/builtins/subsf3.c
	$(BCC)

src/builtins/$(ARCH)-truncdfsf2.o: compiler-rt/lib/builtins/truncdfsf2.c
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

src/builtins/$(ARCH)-clzdi2.o: compiler-rt/lib/builtins/clzdi2.c
	$(BCC)

src/builtins/$(ARCH)-addsf3.o: compiler-rt/lib/builtins/addsf3.c
	$(BCC)

src/builtins/$(ARCH)-clzsi2.o: compiler-rt/lib/builtins/clzsi2.c
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

src/builtins/$(ARCH)-clzdi2.o: compiler-rt/lib/builtins/arm/clzdi2.S
	$(BCC)

src/builtins/$(ARCH)-addsf3.o: compiler-rt/lib/builtins/arm/addsf3.S
	$(BCC)

src/builtins/$(ARCH)-clzsi2.o: compiler-rt/lib/builtins/arm/clzsi2.S
	$(BCC)

endif
