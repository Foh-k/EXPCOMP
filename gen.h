#pragma once

#include "./ast.h"

// in gen.c
void genCodeExprConst(ExprNodePtr expr);
void genCodeExprUM(ExprNodePtr expr);
void genCodeExprNot(ExprNodePtr expr);
void genCodeExprVar(ExprNodePtr expr);
void genCodeExprAdd(ExprNodePtr expr);
void genCodeExprSub(ExprNodePtr expr);
void genCodeExprBlt(ExprNodePtr expr);
void genCodeExprBeq(ExprNodePtr expr);
void genCodeExprBne(ExprNodePtr expr);
void genCodeExpr(ExprNodePtr expr);
void genCodeExprMult(ExprNodePtr expr);
void genCodeExprAssign(ExprNodePtr expr);
void genCodeExprLor(ExprNodePtr expr);
void genCodeExprLand(ExprNodePtr expr);
void genCodeExprBor(ExprNodePtr expr);
void genCodeExprBand(ExprNodePtr expr);
void genCodeExprXor(ExprNodePtr expr);
void genCodeExprBnot(ExprNodePtr expr);
void genCodeExprLshift(ExprNodePtr expr);
void genCodeExprRshift(ExprNodePtr expr);
void genCodeExprInc(ExprNodePtr expr);
void genCodeExprDec(ExprNodePtr expr);

// in mult.c
void multLib(void);

// in div.c
void divLib(void);