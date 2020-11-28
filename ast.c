#include <stdio.h>
#include <stdlib.h>
#include "./ast.h"

ExprNodePtr makeExpr(OpSort opr, int value, SymEntryPtr symbol, ExprNodePtr left, ExprNodePtr right)
{
    ExprNodePtr node;
    if ((node = (ExprNodePtr)malloc(sizeof(ExprNode))) == NULL)
    {
        fprintf(stderr, "Malloc Failed in makeExpr()\n");
        exit(1);
    }

    node->op = opr;
    node->val = value;
    node->sym = symbol;
    node->sub1 = left;
    node->sub2 = right;

    return node;
}

StmtNodePtr makeStmt(StmtSort sort, ExprNodePtr expr, StmtNodePtr st1, StmtNodePtr st2)
{
    StmtNodePtr node;
    if ((node = (StmtNodePtr)malloc(sizeof(StmtNode))) == NULL)
    {
        fprintf(stderr, "Malloc Failed in makeStmt()\n");
        exit(1);
    }

    node->sort = sort;
    node->next = NULL;
    node->expr = expr;
    node->st1 = st1;
    node->st2 = st2;

    return node;
}
