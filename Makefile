# LDLIBS := 
CC := gcc
CFLAGS :=  -Wall -Wextra

test1: ast.o gen.o test1.o

ast.o gen.o test1.o : ast.h

clean:
	$(RM) *.o
	$(RM) test1