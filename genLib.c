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
    switch (s->sort)
    {
    case SYM_VAR:
        if (s->belong)
        {
            // 局所変数
            fprintf(af, "      ld _FP\n");
            fprintf(af, "      mv ixr, acc\n");
            fprintf(af, "      ld ixr, %d\n", s->no);
            fprintf(af, "      push\n");
        }
        else
        {
            // 大域変数
            fprintf(af, "      ld G%04d ; %s\n", s->no, s->name);
            fprintf(af, "      push\n");
        }
        break;

    case SYM_PARAM:
        // 仮引数
        fprintf(af, "      ld _FP\n");
        fprintf(af, "      mv ixr, acc\n");
        fprintf(af, "      ld ixr, %d\n", 2 + s->belong->nParam - s->no);
        fprintf(af, "      push\n");
        break;

    default:
        fprintf(stderr, "Undefined Variable sort\n");
        exit(1);
    }
}

void genCodeExprAssign(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    SymEntryPtr s = expr->sym;
    switch (s->sort)
    {
    case SYM_VAR:
        if (s->belong)
        {
            // 局所変数
            fprintf(af, "      ld _FP\n");
            fprintf(af, "      mv ixr, acc\n");
            fprintf(af, "      pop\n");
            fprintf(af, "      st ixr, %d\n", s->no);
            fprintf(af, "      push\n");
        }
        else
        {
            // 大域変数
            fprintf(af, "      pop ; =Assignment\n");
            fprintf(af, "      st G%04d\n", expr->sym->no);
            fprintf(af, "      push\n");
        }
        break;

    case SYM_PARAM:
        // 仮引数、代入していいかは微妙
        fprintf(af, "      ld _FP\n");
        fprintf(af, "      mv ixr, acc\n");
        fprintf(af, "      pop\n");
        fprintf(af, "      st ixr, %d\n", 2 + s->belong->nParam - s->no);
        fprintf(af, "      push\n");
        break;

    default:
        break;
    }
}