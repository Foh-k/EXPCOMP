# -------------------------------------------- #
# Compile Generatoion Files
# -------------------------------------------- #

CC := gcc
CFLAGS :=  -Wall -Wextra

GOBJ := Gens/ast.o
GOBJ += Gens/gen.o
GOBJ += Gens/genLib.o
GOBJ += Gens/genUnary.o
GOBJ += Gens/genBinary.o
GOBJ += Gens/genFunc.o
GOBJ += Gens/stmt.o
GOBJ += Gens/mult.o
GOBJ += Gens/div.o
GOBJ += Gens/callFunc.o
GOBJ += Gens/io.o
GOBJ += Gens/globals.o
GOBJ += Gens/runtime.o
GOBJ += Gens/symtable.o

OBJS += ${GOBJ}

HFILE := Headers/ast.h
HFILE += Headers/gen.h

# genall: ${GOBJ}

${GOBJ}: ${HFILE}

.PHONY: genclean

genclean:
	${RM} Gens/*.o
