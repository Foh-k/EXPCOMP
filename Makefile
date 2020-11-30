CC := gcc
CFLAGS :=  -Wall -Wextra

OBJ := ast.o
OBJ += gen.o
OBJ += genLib.o
OBJ += genUnary.o
OBJ += genBinary.o
OBJ += genFunc.o
OBJ += stmt.o
OBJ += mult.o
OBJ += div.o
OBJ += test1.o
OBJ += callFunc.o
OBJ += io.o

HFILE := ast.h
HFILE += gen.h

test1: $(OBJ)

$(OBJ) : $(HFILE)

clean:
	$(RM) *.o
	$(RM) test1
