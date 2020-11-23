#include <stdio.h>
#include "./ast.h"

FILE *af;

void test1()
{
    ExprNodePtr lit123 = makeExpr(OP_CONST, 123, NULL, NULL, NULL);
    genCodeExpr(lit123);
}

int main()
{
    af = stdout;
    test1();
    return 0;
}