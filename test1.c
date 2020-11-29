#include <stdio.h>
#include "ast.h"
#include "gen.h"

FILE *af;
int multcall;
int divcall;
int labelNo;

void test1()
{
    ExprNodePtr lit123 = makeExpr(OP_CONST, 123, NULL, NULL, NULL);
    ExprNodePtr not1 = makeExpr(OP_NOT, 0, NULL, lit123, NULL);
    ExprNodePtr not2 = makeExpr(OP_NOT, 0, NULL, not1, NULL);
    genCodeExpr(not2);
}

void test4()
{
    SymEntry s1 = {SYM_GLOBAL, "hanoicount", 7};
    ExprNodePtr e1 = makeExpr(OP_VAR, 0, &s1, NULL, NULL);
    genCodeExpr(e1);
}

void test5()
{
    ExprNodePtr lit1 = makeExpr(OP_CONST, 1, NULL, NULL, NULL);
    ExprNodePtr lit2 = makeExpr(OP_CONST, 2, NULL, NULL, NULL);
    ExprNodePtr lit3 = makeExpr(OP_CONST, 3, NULL, NULL, NULL);
    ExprNodePtr add = makeExpr(OP_ADD, 0, NULL, lit2, lit1);
    ExprNodePtr sub = makeExpr(OP_SUB, 0, NULL, lit3, add);
    genCodeExpr(sub);
}

void test6()
{
    ExprNodePtr lit1 = makeExpr(OP_CONST, 3, NULL, NULL, NULL);
    ExprNodePtr lit2 = makeExpr(OP_CONST, 4, NULL, NULL, NULL);
    ExprNodePtr blt = makeExpr(OP_BLT, 0, NULL, lit1, lit2);
    genCodeExpr(blt);
}

void test7()
{
    ExprNodePtr lit1 = makeExpr(OP_CONST, 3, NULL, NULL, NULL);
    ExprNodePtr lit2 = makeExpr(OP_CONST, 4, NULL, NULL, NULL);
    ExprNodePtr mul = makeExpr(OP_MUL, 0, NULL, lit1, lit2);
    genCodeExpr(mul);
}

void test8()
{
    SymEntry s = {SYM_GLOBAL, "flag", 1};
    ExprNodePtr var = makeExpr(OP_VAR, 0, &s, NULL, NULL);
    ExprNodePtr not = makeExpr(OP_NOT, 0, NULL, var, NULL);
    ExprNodePtr c0 = makeExpr(OP_CONST, 0, NULL, NULL, NULL);
    ExprNodePtr c1 = makeExpr(OP_CONST, 1, NULL, NULL, NULL);
    ExprNodePtr as0 = makeExpr(OP_ASSSIGN, 0, &s, c0, NULL);
    ExprNodePtr as1 = makeExpr(OP_ASSSIGN, 0, &s, c1, NULL);
    StmtNodePtr expr1 = makeStmt(STMT_EXPR, NULL, as0, NULL, NULL);
    StmtNodePtr expr2 = makeStmt(STMT_EXPR, NULL, as1, NULL, NULL);
    StmtNodePtr ifnode = makeStmt(STMT_IF, NULL, not, expr1, expr2);
    genCodeStmt(ifnode);
}

int main()
{
    af = stdout;
    // test1();
    // test4();
    // test5();
    // test6();
    // test7();
    test8();

    if (multcall)
        multLib();
    if (divcall)
        divLib();

    return 0;
}