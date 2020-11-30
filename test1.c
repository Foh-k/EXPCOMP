#include <stdio.h>
#include "ast.h"
#include "gen.h"

FILE *af;
int multcall;
int divcall;
int labelNo;
int varNo;

void test()
{
    SymEntryPtr fib = makeSym(SYM_FUNC, "fib", 0, 1, 2, NULL);
    SymEntryPtr n = makeSym(SYM_VAR, "n", -2, 0, 0, fib);
    SymEntryPtr m = makeSym(SYM_VAR, "m", -1, 0, 0, fib);
    SymEntryPtr k = makeSym(SYM_PARAM, "k", 1, 0, 0, fib);
    ExprNodePtr varm = makeExpr(OP_VAR, 0, m, NULL, NULL);
    ExprNodePtr vark = makeExpr(OP_VAR, 0, k, NULL, NULL);
    ExprNodePtr add = makeExpr(OP_ADD, 0, NULL, varm, vark);
    ExprNodePtr assg = makeExpr(OP_ASSIGN, 0, n, add, NULL);
    StmtNodePtr st = makeStmt(STMT_EXPR, NULL, assg, NULL, NULL);
    genCodeStmt(st);
}

int main()
{
    af = stdout;
    test();

    fprintf(af, "      halt\n");
    // fprintf(af, "      G0000: .space 1 ; sum\n");
    // fprintf(af, "      G0001: .space 1 ; k\n");

    if (multcall)
        multLib();
    if (divcall)
        divLib();

    return 0;
}