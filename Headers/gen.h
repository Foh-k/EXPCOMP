#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern FILE *af;
extern int multcall;
extern int divcall;
extern int labelNo;

extern DefNodePtr sourcedefs;

// in gen.c
void genCodeExpr(ExprNodePtr expr);

// in genLib.c
void genCodeExprConst(ExprNodePtr expr);
void genCodeExprAssign(ExprNodePtr expr);
void genCodeExprVar(ExprNodePtr expr);

// in genUnary.c
void genCodeExprUM(ExprNodePtr expr);
void genCodeExprNot(ExprNodePtr expr);
void genCodeExprBnot(ExprNodePtr expr);
void genCodeExprInc(ExprNodePtr expr);
void genCodeExprDec(ExprNodePtr expr);

// in genBinary.c
void genCodeExprAdd(ExprNodePtr expr);
void genCodeExprSub(ExprNodePtr expr);
void genCodeExprBlt(ExprNodePtr expr);
void genCodeExprBeq(ExprNodePtr expr);
void genCodeExprBne(ExprNodePtr expr);
void genCodeExprMult(ExprNodePtr expr);
void genCodeExprDiv(ExprNodePtr expr);
void genCodeExprMod(ExprNodePtr expr);
void genCodeExprLor(ExprNodePtr expr);
void genCodeExprLand(ExprNodePtr expr);
void genCodeExprBor(ExprNodePtr expr);
void genCodeExprBand(ExprNodePtr expr);
void genCodeExprXor(ExprNodePtr expr);
void genCodeExprLshift(ExprNodePtr expr);
void genCodeExprRshift(ExprNodePtr expr);

// in genFunc.c
void genCodeExprFuncall(ExprNodePtr expr);

// in mult.c
void multLib(void);

// in div.c
void divLib(void);

// in stmt.c
void genCodeStmtExpr(StmtNodePtr stmt);
void genCodeStmtIf(StmtNodePtr stmt);
void genCodeStmtWhile(StmtNodePtr stmt);
void genCodeStmt(StmtNodePtr stmt);
void genCodeStmtReturn(StmtNodePtr stmt);

// in callFunc.c
void genCodeFunc(DefNodePtr func);

// in io.c
void in();
void out();


// in globals.c
void genCodeGlobals();
void genCodeFuncs();

// in runtime.c
void genCode();