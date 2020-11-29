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
    genCodeStmtExpr(stmt);
    fprintf(af, "      pop\n");
    fprintf(af, "      or #0\n");
    fprintf(af, "      jpz ELSE%04d\n", labelNo);
    genCodeStmt(stmt->st1);
    fprintf(af, "      jp END%04d\n", labelNo + 1);
    fprintf(af, "ELSE%04d:\n", labelNo);
    genCodeStmt(stmt->st2);
    fprintf(af, "END%04d:\n", labelNo + 1);
    labelNo += 2;
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

        default:
            fprintf(stderr, "Undefined Statement\n");
            exit(1);
        }
        stmt = stmt->next;
    }
}