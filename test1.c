#include <stdio.h>
#include "Headers/ast.h"
#include "Headers/gen.h"
#include "Yaccs/y.tab.h"    

#define ECONST(k) makeExpr(OP_CONST, k, NULL, NULL, NULL)
#define EVAR(p) makeExpr(OP_VAR, 0, p, NULL, NULL)
#define EBIN(op, l, r) makeExpr(op, 0, NULL, l, r)
#define SEXPR(e) makeStmt(STMT_EXPR, e, NULL, NULL)
#define IN(var) SEXPR(makeExpr(OP_ASSIGN, 0, var, makeExpr(OP_FUNCALL, 0, fin, NULL, NULL), NULL))
#define OUT(f) SEXPR(makeExpr(OP_FUNCALL, 0, fout, makeExpr(OP_ALIST, 0, NULL, f, NULL), NULL))

FILE *af;

void test()
{
    SymEntryPtr fin = makeSym(SYM_FUNC, "in", 0, 0, 0, NULL);
    SymEntryPtr fout = makeSym(SYM_FUNC, "out", 1, 1, 0, NULL);
    SymEntryPtr fib = makeSym(SYM_FUNC, "fib", 2, 1, 0, NULL);
    SymEntryPtr param_k = makeSym(SYM_PARAM, "k", 1, 0, 0, fib);

    StmtNodePtr l2 = makeStmt(STMT_IF,
                              EBIN(OP_BLT, EVAR(param_k), ECONST(2)),
                              makeStmt(STMT_RETURN, ECONST(1), NULL, NULL),
                              NULL);

    ExprNodePtr listleft = makeExpr(OP_ALIST, 0, NULL, EBIN(OP_SUB, EVAR(param_k), ECONST(2)), NULL);
    ExprNodePtr listright = makeExpr(OP_ALIST, 0, NULL, EBIN(OP_SUB, EVAR(param_k), ECONST(1)), NULL);
    ExprNodePtr fibleft = makeExpr(OP_FUNCALL, 0, fib, listleft, NULL);
    ExprNodePtr fibright = makeExpr(OP_FUNCALL, 0, fib, listright, NULL);

    StmtNodePtr l3 = makeStmt(STMT_RETURN,
                              EBIN(OP_ADD, fibleft, fibright),
                              NULL,
                              NULL);

    l2->next = l3;

    sourcedefs = makeDef(DEF_FUNC, fib, l2);
    SymEntryPtr mein = makeSym(SYM_FUNC, "main", 3, 0, 1, NULL);
    SymEntryPtr lclv = makeSym(SYM_VAR, "v", 1, 0, 0, mein);

    StmtNodePtr l8 = IN(lclv);

    ExprNodePtr fibcall = makeExpr(OP_FUNCALL, 0, fib, makeExpr(OP_ALIST, 0, NULL, EVAR(lclv), NULL), NULL);
    StmtNodePtr l9 = OUT(fibcall);
    l8->next = l9;

    StmtNodePtr l10 = makeStmt(STMT_RETURN, ECONST(0), NULL, NULL);
    l9->next = l10;

    sourcedefs->next = makeDef(DEF_FUNC, mein, l8);

    genCode();
}


void testtable()
{
    // symtableに追加
    symAdd(SYM_VAR, "test", 0, 0, 0, NULL);
    symAdd(SYM_VAR, "dummy", 1, 0, 0, NULL);
    // symtableからの検索
    SymEntryPtr look = symLookup("test");
    printf("%s\n", look->name);
}

int main()
{
    af = stdout;
    // test();
    // testtable();
    yyparse();
    genCode();
    return 0;
}