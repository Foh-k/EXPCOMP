# -------------------------------------------- #
# Compile Generatoion Files
# -------------------------------------------- #

CC := gcc
CFLAGS :=  -Wall -Wextra

GOBJ := ast.o
GOBJ += gen.o
GOBJ += genLib.o
GOBJ += genUnary.o
GOBJ += genBinary.o
GOBJ += genFunc.o
GOBJ += stmt.o
GOBJ += mult.o
GOBJ += div.o
GOBJ += callFunc.o
GOBJ += io.o
GOBJ += globals.o
GOBJ += runtime.o
GOBJ += symtable.o

HFILE := ../Headers/ast.h
HFILE += ../Headers/gen.h

genall: ${GOBJ}

${GOBJ}: ${HFILE}

.PHONY: clean

clean:
	${RM} *.o
