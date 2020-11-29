#include "ast.h"
#include "gen.h"
#include <stdio.h>
#include <stdlib.h>

void genCodeStmtExpr(StmtNodePtr stmt)
{
    genCodeExpr(stmt->expr);
    fprintf(af, "      inc sp\n");
}

void genCodeStmtIf(StmtNodePtr stmt)
{
    int el = labelNo;
    int end = labelNo + 1;
    labelNo += 2;
    genCodeExpr(stmt->expr);
    fprintf(af, "      pop\n");
    fprintf(af, "      or #0\n");
    fprintf(af, "      jpz ELSE%04d\n", el);
    genCodeStmt(stmt->st1);
    fprintf(af, "      jp END%04d\n", end);
    fprintf(af, "ELSE%04d:\n", el);
    genCodeStmt(stmt->st2);
    fprintf(af, "END%04d:\n", end);
}

void genCodeStmtWhile(StmtNodePtr stmt)
{
    int loop = labelNo;
    int end = labelNo + 1;
    labelNo += 2;
    fprintf(af, "LOOP%04d:\n", loop);
    genCodeExpr(stmt->expr);
    fprintf(af, "      pop\n");
    fprintf(af, "      or #0\n");
    fprintf(af, "      jpz END%04d\n", end);
    genCodeStmt(stmt->st1);
    fprintf(af, "      jp LOOP%04d\n", loop);
    fprintf(af, "END%04d:\n", end);
}

void genCodeStmt(StmtNodePtr stmt)
{
    while (stmt != NULL)
    {
        switch (stmt->sort)
        {
        case STMT_EXPR:
            genCodeStmtExpr(stmt);
            break;

        case STMT_IF:
            genCodeStmtIf(stmt);
            break;

        case STMT_WHILE:
            genCodeStmtWhile(stmt);
            break;

        default:
            fprintf(stderr, "Undefined Statement\n");
            exit(1);
        }
        stmt = stmt->next;
    }
}