SRC := mylex.o
LEX := flex
CC := gcc
CFLAGS := -Wall -Wextra

cmake : ${SRC}

.PHONY : clean

clean:
	cd ../Yaccs; ${MAKE} clean;
	${RM} lex.yy.c
	${RM} *.o
	${RM} ${CALC:.o=}
