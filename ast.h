#pragma once

typedef enum {
    OP_ASSIGN, /* Assignment */
    OP_LOR, OP_LAND, OP_BLT, OP_BEQ, OP_BNE, /* Binary Operators */
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD,
    OP_BAND, OP_BOR, OP_XOR, OP_LSHIFT, OP_RSHIFT,
    OP_NOT, OP_UM, OP_BNOT, OP_INC, OP_DEC, /* Unary Operators */
    OP_VAR, /* Variable Reference */
    OP_CONST, /* Literal */
    OP_ALIST, OP_FUNCALL
} OpSort; /* Sort of operators */

typedef enum {
    SYM_VAR, SYM_PARAM, SYM_FUNC
} SymbolSort;

typedef struct SymEntry *SymEntryPtr;
typedef struct SymEntry{
    SymbolSort sort;
    char *name;
    int no;
    int nParam, nVar;
    SymEntryPtr belong;
} SymEntry;

typedef struct ExprNode *ExprNodePtr;
typedef struct ExprNode
{
    OpSort op;
    int val;
    SymEntryPtr sym;
    ExprNodePtr sub1;
    ExprNodePtr sub2;
} ExprNode;

typedef enum {
    STMT_EXPR, STMT_IF, STMT_WHILE, STMT_RETURN
} StmtSort;

typedef struct StmtNode *StmtNodePtr;
typedef struct StmtNode
{
    StmtSort sort;
    StmtNodePtr next;
    ExprNodePtr expr;
    StmtNodePtr st1, st2;
} StmtNode;

typedef enum {
    DEF_FUNC, DEF_GLOBAL, PROTOTYPE
} DefSort;

typedef struct DefNode *DefNodePtr;
typedef struct DefNode
{
    DefSort sort;
    SymEntryPtr sym;
    DefNodePtr next;
    StmtNodePtr body;
} DefNode;



// in ast.c
ExprNodePtr makeExpr(OpSort opr, int value, SymEntryPtr symbol, ExprNodePtr left, ExprNodePtr right);
StmtNodePtr makeStmt(StmtSort sort, StmtNodePtr next, ExprNodePtr expr, StmtNodePtr st1, StmtNodePtr st2);
SymEntryPtr makeSym(SymbolSort sort, char* name, int no, int nParam, int nVar, SymEntryPtr belong);
DefNodePtr makeDef(DefSort sort, SymEntryPtr sym, StmtNodePtr body);

// 関数呼び出し時に利用
extern SymEntryPtr curfunc;
