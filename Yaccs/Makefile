# -------------------------------------------- #
# Compile yacc Files
# -------------------------------------------- #

YACC := bison
YFLAGS := -y
YFLAGS += -d
YFLAGS += -t
YFLAGS += -v

# YOBJ := Yaccs/calc.o
YOBJ := Yaccs/myparse.o
YOBJ += Yaccs/lex.o

OBJS += ${YOBJ} # 今後test1とリンクする必要があるかによって変更

# yaccall: ${YOBJ}

.PHONY: Yclean

yclean:
	${RM} Yaccs/*.o
	${RM} Yaccs/*.tab.?
	${RM} Yaccs/*.output
	${RM} Yaccs/${YOBJ:.o=}
