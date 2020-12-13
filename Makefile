all: test1

CC := gcc
CFLAGS :=  -Wall -Wextra
OBJS := test1.o

include Gens/Makefile
include Yaccs/Makefile

test1: ${OBJS}
	${CC} -o $@ ${CFLAGS} ${OBJS}

yaccmake: ${YOBJ} # Yaccのみをコンパイルするやつ
	${CC} -o ${?:.o=} ${CFLAGS} ${YOBJ} 


.PHONY: clean

clean: yclean genclean
	${RM} *.o
	${RM} test1
	${RM} *.out
	${RM} *.tab.c
	${RM} *.tab.h
	${RM} *.output
