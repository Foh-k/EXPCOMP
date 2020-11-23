#include <stdio.h>
#include <stdlib.h>
#include "./ast.h"

extern FILE *af;

void genCodeExprConst(ExprNodePtr expr)
{
    fprintf(af, "      ld16 #%d ; Const\n", expr->val);
    fprintf(af, "      push\n");
}

void genCodeExprUM(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    fprintf(af, "      ld #0\n");
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      sub ixr, 0\n");
    fprintf(af, "      st ixr, 0\n");
}

void genCodeExpr(ExprNodePtr expr)
{
    switch (expr->op)
    {
    case OP_CONST:
        genCodeExprConst(expr);
        break;

    case OP_UM:
        genCodeExprUM(expr);
        break;
    default:
        fprintf(stderr, "Undefined Expression\n");
        exit(1);
    }
}