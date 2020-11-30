#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "gen.h"

void genCodeExprFunc(ExprNodePtr expr)
{
    fprintf(af, "      dec sp\n");
    // 引数を持つ
    if (expr->sub1)
    {
        ExprNodePtr alist = expr->sub1;
        do
        {
            genCodeExpr(alist->sub1);
            alist = alist->sub2;
        } while (alist && (alist->op == OP_ALIST)); // NULLでリスト終了
    }
    fprintf(af, "      call F%04d\n", expr->sym->no);
    fprintf(af, "      mv acc, sp\n");
    fprintf(af, "      add #%04d\n", expr->sym->nParam);
    fprintf(af, "      sp, acc\n");
}
