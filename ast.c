#include <stdio.h>
#include <stdlib.h>
#include "./ast.h"

ExprNodePtr makeExpr(OpSort opr, int value, SymEntryPtr symbol, ExprNodePtr left, ExprNodePtr right)
{
    ExprNodePtr node;
    if ((node = (ExprNodePtr)malloc(sizeof(ExprNode) * 8)) == NULL)
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

StmtNodePtr makeStmt(StmtSort sort, StmtNodePtr next, ExprNodePtr expr, StmtNodePtr st1, StmtNodePtr st2)
{
    StmtNodePtr node;
    if ((node = (StmtNodePtr)malloc(sizeof(StmtNode) * 8)) == NULL)
    {
        fprintf(stderr, "Malloc Failed in makeStmt()\n");
        exit(1);
    }

    node->sort = sort;
    node->next = next;
    node->expr = expr;
    node->st1 = st1;
    node->st2 = st2;

    return node;
}

SymEntryPtr makeSym(SymbolSort sort, char *name, int no, int nParam, int nVar, SymEntryPtr belong)
{
    SymEntryPtr entry;
    if ((entry = (SymEntryPtr)malloc(sizeof(SymEntry) * 8)) == NULL)
    {
        fprintf(stderr, "Malloc Failed in makeSym()\n");
        exit(1);
    }

    entry->sort = sort;
    entry->name = name;
    entry->no = no;
    entry->nParam = nParam;
    entry->nVar = nVar;
    entry->belong = belong;

    return entry;
}

DefNodePtr makeDef(DefSort sort, SymEntryPtr sym, StmtNodePtr body)
{
    DefNodePtr node;
    if ((node = (DefNodePtr)malloc(sizeof(DefNode) * 8)) == NULL)
    {
        fprintf(stderr, "Malloc Failed in makeDef()\n");
        exit(1);
    }

    node->sort = sort;
    node->sym = sym;
    node->body = body;
    node->next = NULL;

    return node;
}
