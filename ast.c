#include <stdio.h>
#include <stdlib.h>
#include "./ast.h"

ExprNodePtr makeExpr(OpSort opr, int value, SymEntryPtr symbol, ExprNodePtr left, ExprNodePtr right)
{
    ExprNodePtr node;
    if ((node = (ExprNodePtr)malloc(sizeof(ExprNode))) == NULL)
    {
        printf("Malloc is faild");
        exit(1);
    }

    node->op = opr;
    node->val = value;
    node->sym = symbol;
    node->sub1 = left;
    node->sub2 = right;

    return node;
}
