#include <stdio.h>
#include "./ast.h"

FILE *af;

void test1()
{
    ExprNodePtr lit123 = makeExpr(OP_CONST, 123, NULL, NULL, NULL);
    ExprNodePtr minus1 = makeExpr(OP_UM, 0, NULL, lit123, NULL);
    ExprNodePtr minus2 = makeExpr(OP_UM, 0, NULL, minus1, NULL);
    genCodeExpr(minus2);
}

int main()
{
    af = stdout;
    test1();
    return 0;
}