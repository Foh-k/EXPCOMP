#include <stdio.h>
#include <stdlib.h>
#include "./ast.h"

extern FILE *af;
int labelNo = 0;

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

void genCodeExprNot(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    fprintf(af, "      pop ; Unary !\n");
    fprintf(af, "      or #0\n");
    fprintf(af, "      ld #1\n");
    fprintf(af, "      jpz L%04d\n", labelNo);
    fprintf(af, "      ld #0\n");
    fprintf(af, "L%04d:push\n", labelNo);
    labelNo++;
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

    case OP_NOT:
        genCodeExprNot(expr);
        break;

    default:
        fprintf(stderr, "Undefined Expression\n");
        exit(1);
    }
}