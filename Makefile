all: test1 calc

# ------------------------------ #
# C
# ------------------------------ #
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
OBJ += globals.o
OBJ += runtime.o

HFILE := ast.h
HFILE += gen.h

# ------------------------------ #
# yacc
# ------------------------------ #

BTAR := calc.y
BFLAGS := -y    # 名前の統一
BFLAGS += -d    # ヘッダ出力
BFLAGS += -t
# BFLAGS := -v  # 詳細な状態表

.PHONY: calc

calc : $(BTAR)
	bison $(BFLAGS) $(BTAR)
	$(CC) $(CFLAGS) -o calc y.tab.c
	
# ------------------------------ #


test1: $(OBJ)

$(OBJ) : $(HFILE)


.PHONY: clean

clean:
	$(RM) *.o
	$(RM) test1
	$(RM) *.tab.c
	$(RM) *.tab.h
