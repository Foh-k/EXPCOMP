# -------------------------------------------- #
# Compile yacc Files
# -------------------------------------------- #

YACC := bison
YFLAGS := -y
YFLAGS += -d
YFLAGS += -t
YFLAGS += -v

# YOBJ := Yaccs/calc.o
YOBJ := myparse.o
YOBJ += lex.o

HFILE := ../Headers/ast.h
HFILE += ../Headers/gen.h

yaccall: ${YOBJ}

${YOBJ}: ${HFILE}

.PHONY: Yclean

clean:
	${RM} *.o	
	${RM} *.tab.?
	${RM} *.output
	${RM} ${YOBJ:.o=}
