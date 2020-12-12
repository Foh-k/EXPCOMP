# -------------------------------------------- #
# Compile yacc Files
# -------------------------------------------- #

YACC := bison
YFLAGS := -y
YFLAGS += -d
YFLAGS += -t
YFLAGS += -v

YOBJ := Yaccs/calc.o

# OBJS += ${YOBJ} # 今後test1とリンクする必要があるかによって変更

yaccall: ${YOBJ}

.PHONY: Yclean

yclean:
	${RM} Yaccs/*.o
	${RM} Yaccs/*.tab.?
	${RM} Yaccs/*.output
