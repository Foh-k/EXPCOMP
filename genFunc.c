#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "gen.h"

void genCodeExprFuncall(ExprNodePtr expr)
{
    // 返り値の場所の確保
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
    fprintf(af, "      call F%04d ; call Function %s\n", expr->sym->no, expr->sym->name);
    fprintf(af, "      mv acc, sp\n");
    fprintf(af, "      add #%04d\n", expr->sym->nParam);
    fprintf(af, "      mv sp, acc\n");
}
