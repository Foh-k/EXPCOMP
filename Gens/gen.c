#include <stdio.h>
#include <stdlib.h>
#include "../Headers/ast.h"
#include "../Headers/gen.h"

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

    case OP_MOD:
        genCodeExprMod(expr);
        break;

    case OP_ASSIGN:
        genCodeExprAssign(expr);
        break;

    case OP_LOR:
        genCodeExprLor(expr);
        break;

    case OP_LAND:
        genCodeExprLand(expr);
        break;

    case OP_BOR:
        genCodeExprBor(expr);
        break;

    case OP_BAND:
        genCodeExprBand(expr);
        break;

    case OP_XOR:
        genCodeExprXor(expr);
        break;

    case OP_BNOT:
        genCodeExprBnot(expr);
        break;

    case OP_LSHIFT:
        genCodeExprLshift(expr);
        break;

    case OP_RSHIFT:
        genCodeExprRshift(expr);
        break;

    case OP_INC:
        genCodeExprInc(expr);
        break;

    case OP_DEC:
        genCodeExprDec(expr);
        break;

    case OP_FUNCALL:
        genCodeExprFuncall(expr);
        break;

    default:
        fprintf(stderr, "Undefined Expression\n");
        exit(1);
    }
}