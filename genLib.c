#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "gen.h"

void genCodeExprConst(ExprNodePtr expr)
{
    fprintf(af, "      ld16 #%d ; Const\n", expr->val);
    fprintf(af, "      push\n");
}

void genCodeExprVar(ExprNodePtr expr)
{
    SymEntryPtr s = expr->sym;
    switch (s->class)
    {
    case SYM_GLOBAL:
        fprintf(af, "      ld G%04d ; %s\n", s->no, s->name);
        fprintf(af, "      push\n");
        break;

    default:
        fprintf(stderr, "Undefined Variable Class\n");
        exit(1);
    }
}

void genCodeExprAssign(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    fprintf(af, "      pop ; =Assignment\n");
    fprintf(af, "      st G%04d\n", expr->sym->no);
    fprintf(af, "      push\n");
}