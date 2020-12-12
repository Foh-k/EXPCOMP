#include <stdio.h>
#include <stdlib.h>
#include "../Headers/ast.h"
#include "../Headers/gen.h"

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
    fprintf(af, "L%04d:\n", labelNo);
    fprintf(af, "      push\n");
    labelNo++;
}

void genCodeExprBnot(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    fprintf(af, "      pop\n");
    fprintf(af, "      not\n");
    fprintf(af, "      push\n");
}

void genCodeExprInc(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    fprintf(af, "      pop\n");
    fprintf(af, "      inc acc\n");
    fprintf(af, "      push\n");
    fprintf(af, "      st G%04d\n", expr->sym->no);
}

void genCodeExprDec(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    fprintf(af, "      pop\n");
    fprintf(af, "      dec acc\n");
    fprintf(af, "      push\n");
    fprintf(af, "      st G%04d\n", expr->sym->no);
}