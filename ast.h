#pragma once

typedef enum {
    OP_ASSSIGN, /* Assignment */
    OP_LOR, OP_LAND, OP_BLT, OP_BEQ, OP_BNE, /* Binary Operators */
    OP_ADD, OP_SUB, SP_MUL, OP_DIV, OP_MOD,
    OP_NOT, OP_UM, /* Unary Operators */
    OP_VAR, /* Variable Reference */
    OP_CONST /* Literal */
} OpSort; /* Sort of operators */

typedef enum {
    SYM_GLOBAL
} SymbolSort;

typedef struct SymEntry *SymEntryPtr;
typedef struct SymEntry{
    SymbolSort class;
    char *name;
    int no;
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

// in ast.c
ExprNodePtr makeExpr(OpSort opr, int value, SymEntryPtr symbol, ExprNodePtr left, ExprNodePtr right);

// in gen.c
void genCodeExprConst(ExprNodePtr expr);
void genCodeExpr(ExprNodePtr expr);
