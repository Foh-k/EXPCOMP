all: test1

CC := gcc
CFLAGS :=  -Wall -Wextra
OBJS := test1.o
# in Yaccs
OBJS += Yaccs/myparse.o
# in Lex
OBJS += Lex/mylex.o
# in Gens
OBJS += Gens/ast.o
OBJS += Gens/gen.o
OBJS += Gens/genLib.o
OBJS += Gens/genUnary.o
OBJS += Gens/genBinary.o
OBJS += Gens/genFunc.o
OBJS += Gens/stmt.o
OBJS += Gens/mult.o
OBJS += Gens/div.o
OBJS += Gens/callFunc.o
OBJS += Gens/io.o
OBJS += Gens/globals.o
OBJS += Gens/runtime.o
OBJS += Gens/symtable.o

test1: yaccmake genmake ${OBJS}
	${CC} -o $@ ${CFLAGS} ${OBJS}

yaccmake: 
	cd Yaccs; ${MAKE};

lexmake:
	cd Lex; ${MAKE};
	
genmake:
	cd Gens; ${MAKE};


.PHONY: cleanmake

clean: 
	cd Yaccs; ${MAKE} clean;
	cd Gens; ${MAKE} clean;
	cd Lex; ${MAKE} clean;
	${RM} *.o
	${RM} test1
	${RM} *.out
	${RM} *.tab.c
	${RM} *.tab.h
	${RM} *.output
	${RM} *.asm
