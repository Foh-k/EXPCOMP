# LDLIBS := 
CC := gcc
CFLAGS :=  -Wall -Wextra

test1: ast.o gen.o stmt.o mult.o div.o test1.o

ast.o gen.o stmt.o mult.o div.o test1.o : ast.h gen.h

clean:
	$(RM) *.o
	$(RM) test1