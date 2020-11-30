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
    SymEntryPtr fib = makeSym(SYM_FUNC, "fib(k-2)", 15, 1, 2, NULL);
    SymEntryPtr k = makeSym(SYM_PARAM, "k", 1, 0, 0, fib);

    ExprNodePtr c2 = makeExpr(OP_CONST, 2, NULL, NULL, NULL);
    ExprNodePtr vark = makeExpr(OP_VAR, 0, k, NULL, NULL);
    ExprNodePtr minus = makeExpr(OP_SUB, 0, NULL, vark, c2);
    ExprNodePtr l1 = makeExpr(OP_ALIST, 0, fib, minus, NULL);
    ExprNodePtr func = makeExpr(OP_FUNCALL, 0, fib, l1, NULL);
    StmtNodePtr st = makeStmt(STMT_EXPR, NULL, func, NULL, NULL);
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