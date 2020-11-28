#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "gen.h"

extern FILE *af;
extern int multcall;
extern int divcall;

int labelNo = 0;

void genCodeExprConst(ExprNodePtr expr)
{
    fprintf(af, "      ld16 #%d ; Const\n", expr->val);
    fprintf(af, "      push\n");
}

void genCodeExprUM(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    fprintf(af, "      ld #0\n");
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      sub ixr, 0\n");
    fprintf(af, "      st ixr, 0\n");
}

void genCodeExprNot(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    fprintf(af, "      pop ; Unary !\n");
    fprintf(af, "      or #0\n");
    fprintf(af, "      ld #1\n");
    fprintf(af, "      jpz L%04d\n", labelNo);
    fprintf(af, "      ld #0\n");
    fprintf(af, "L%04d:push\n", labelNo);
    labelNo++;
}

void genCodeExprVar(ExprNodePtr expr)
{
    SymEntryPtr s = expr->sym;
    switch (s->class)
    {
    case SYM_GLOBAL:
        fprintf(af, "      ld G%04d ; %s\n", s->no, s->name);
        fprintf(af, "      push\n");
        break;

    default:
        fprintf(stderr, "Undefined Variable Class\n");
        exit(1);
    }
}

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
    fprintf(af, "L%04d:push\n", labelNo);
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
    fprintf(af, "L%04d:push\n", labelNo);
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
    fprintf(af, "L%04d:push\n", labelNo);
    labelNo++;
}

void genCodeExprMult(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      call _mult\n");
    multcall = 1;
}

void genCodeExprDiv(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    genCodeExpr(expr->sub2);
    fprintf(af, "      call _div\n");
    divcall = 1;
}

void genCodeExprAssign(ExprNodePtr expr)
{
    genCodeExpr(expr->sub1);
    fprintf(af, "      pop ; =Assignment\n");
    fprintf(af, "      st G%04d\n", expr->sym->no);
    fprintf(af, "      push\n");
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

void genCodeExpr(ExprNodePtr expr)
{
    switch (expr->op)
    {
    case OP_CONST:
        genCodeExprConst(expr);
        break;

    case OP_UM:
        genCodeExprUM(expr);
        break;

    case OP_NOT:
        genCodeExprNot(expr);
        break;

    case OP_VAR:
        genCodeExprVar(expr);
        break;

    case OP_ADD:
        genCodeExprAdd(expr);
        break;

    case OP_SUB:
        genCodeExprSub(expr);
        break;

    case OP_BLT:
        genCodeExprBlt(expr);
        break;

    case OP_BEQ:
        genCodeExprBeq(expr);
        break;

    case OP_BNE:
        genCodeExprBne(expr);
        break;

    case OP_MUL:
        genCodeExprMult(expr);
        break;

    case OP_DIV:
        genCodeExprDiv(expr);
        break;

    case OP_ASSSIGN:
        genCodeExprAssign(expr);
        break;

    default:
        fprintf(stderr, "Undefined Expression\n");
        exit(1);
    }
}