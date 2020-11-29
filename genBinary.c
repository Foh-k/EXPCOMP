#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "gen.h"

void genCodeExprAdd(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 1\n");
    fprintf(af, "      add ixr, 0\n");
    fprintf(af, "      st ixr, 1\n");
    fprintf(af, "      inc sp\n");
}

void genCodeExprSub(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 1\n");
    fprintf(af, "      sub ixr, 0\n");
    fprintf(af, "      st ixr, 1\n");
    fprintf(af, "      inc sp\n");
}

void genCodeExprBlt(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 1\n");
    fprintf(af, "      sub ixr, 0\n");
    fprintf(af, "      ld #1\n");
    fprintf(af, "      jps L%04d\n", labelNo);
    fprintf(af, "      ld #0\n");
    fprintf(af, "L%04d:\n", labelNo);
    fprintf(af, "      st ixr, 1\n");
    fprintf(af, "      inc sp\n");
    labelNo++;
}

void genCodeExprBeq(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 1\n");
    fprintf(af, "      sub ixr, 0\n");
    fprintf(af, "      ld #1\n");
    fprintf(af, "      jpz L%04d\n", labelNo);
    fprintf(af, "      ld #0\n");
    fprintf(af, "L%04d:\n", labelNo);
    fprintf(af, "      st ixr, 1\n");
    fprintf(af, "      inc sp\n");
    labelNo++;
}

void genCodeExprBne(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 1\n");
    fprintf(af, "      sub ixr, 0\n");
    fprintf(af, "      ld #0\n");
    fprintf(af, "      jpz L%04d\n", labelNo);
    fprintf(af, "      ld #1\n");
    fprintf(af, "L%04d:\n", labelNo);
    fprintf(af, "      st ixr, 1\n");
    fprintf(af, "      inc sp\n");
    labelNo++;
}

void genCodeExprMult(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      call _mult\n");
    fprintf(af, "      inc sp");
    multcall = 1;
}

void genCodeExprDiv(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      call _div\n");
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 0\n");
    fprintf(af, "      st ixr, 1\n");
    fprintf(af, "      inc sp\n");
    divcall = 1;
}

void genCodeExprMod(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      call _div\n");
    fprintf(af, "      inc sp\n");
    divcall = 1;
}

void genCodeExprLor(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    fprintf(af, "      pop\n");
    fprintf(af, "      or #0\n");
    fprintf(af, "      jpz L%04d\n", labelNo + 1);
    fprintf(af, "      jp L%04d\n", labelNo + 2);
    fprintf(af, "L%04d:\n", labelNo + 1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      pop\n");
    fprintf(af, "      or #0\n");
    fprintf(af, "      jpz L%04d\n", labelNo);
    fprintf(af, "L%04d:\n", labelNo + 2);
    fprintf(af, "      ld #1\n");
    fprintf(af, "L%04d:\n", labelNo);
    fprintf(af, "      push\n");
    labelNo += 3;
}

void genCodeExprLand(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    fprintf(af, "      pop\n");
    fprintf(af, "      or #0\n");
    fprintf(af, "      jpz L%04d\n", labelNo + 2);
    fprintf(af, "      jp L%04d\n", labelNo + 1);
    fprintf(af, "L%04d:\n", labelNo + 1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      pop\n");
    fprintf(af, "      or #0\n");
    fprintf(af, "      jpz L%04d\n", labelNo + 2);
    fprintf(af, "      ld #1\n");
    fprintf(af, "      jp L%04d\n", labelNo);
    fprintf(af, "L%04d:\n", labelNo + 2);
    fprintf(af, "      ld #0\n");
    fprintf(af, "L%04d:\n", labelNo);
    fprintf(af, "      push\n");
    labelNo += 3;
}

void genCodeExprBor(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 1\n");
    fprintf(af, "      or ixr, 0\n");
    fprintf(af, "      st ixr, 1\n");
    fprintf(af, "      inc sp\n");
}

void genCodeExprBand(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 1\n");
    fprintf(af, "      and ixr, 0\n");
    fprintf(af, "      st ixr, 1\n");
    fprintf(af, "      inc sp\n");
}

void genCodeExprXor(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 1\n");
    fprintf(af, "      eor ixr, 0\n");
    fprintf(af, "      st ixr, 1\n");
    fprintf(af, "      inc sp\n");
}

void genCodeExprLshift(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 0\n");
    fprintf(af, "      or #0\n");
    fprintf(af, "      jpz L%04d\n", labelNo + 1);
    fprintf(af, "L%04d:\n", labelNo);
    fprintf(af, "      st ixr, 0");
    fprintf(af, "      ld ixr, 1\n");
    fprintf(af, "      lsl\n");
    fprintf(af, "      st ixr, 1\n");
    fprintf(af, "      ld ixr, 0\n");
    fprintf(af, "      dec acc\n");
    fprintf(af, "      jpz L%04d\n", labelNo + 1);
    fprintf(af, "      jp L%04d\n", labelNo);
    fprintf(af, "L%04d:\n", labelNo + 1);
    fprintf(af, "      inc sp\n");
    labelNo += 2;
}

void genCodeExprRshift(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 0\n");
    fprintf(af, "      or #0\n");
    fprintf(af, "      jpz L%04d\n", labelNo + 1);
    fprintf(af, "L%04d:\n", labelNo);
    fprintf(af, "      st ixr, 0");
    fprintf(af, "      ld ixr, 1\n");
    fprintf(af, "      lsr\n");
    fprintf(af, "      st ixr, 1\n");
    fprintf(af, "      ld ixr, 0\n");
    fprintf(af, "      dec acc\n");
    fprintf(af, "      jpz L%04d\n", labelNo + 1);
    fprintf(af, "      jp L%04d\n", labelNo);
    fprintf(af, "L%04d:\n", labelNo + 1);
    fprintf(af, "      inc sp\n");
    labelNo += 2;
}