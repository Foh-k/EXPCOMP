# -------------------------------------------- #
# Compile yacc Files
# -------------------------------------------- #

YACC := bison
YFLAGS := -y
YFLAGS += -d
YFLAGS += -t
YFLAGS += -v

YOBJ := myparse.o

HFILE := ../Headers/ast.h
HFILE += ../Headers/gen.h

yaccall: ${YOBJ}

${YOBJ}: ${HFILE}

.PHONY: clean

clean:
	${RM} *.o	
	${RM} *.tab.?
	${RM} *.output
	${RM} ${YOBJ:.o=}
	${RM} ${CALC:.o=}
