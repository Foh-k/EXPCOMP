#include <stdio.h>
#include "./ast.h"

FILE *af;

void test1()
{
    ExprNodePtr lit123 = makeExpr(OP_CONST, 123, NULL, NULL, NULL);
    ExprNodePtr not1 = makeExpr(OP_NOT, 0, NULL, lit123, NULL);
    ExprNodePtr not2 = makeExpr(OP_NOT, 0, NULL, not1, NULL);
    genCodeExpr(not2);
}

int main()
{
    af = stdout;
    test1();
    return 0;
}