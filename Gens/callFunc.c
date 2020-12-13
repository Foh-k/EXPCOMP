#include <stdio.h>
#include <stdlib.h>
#include "../Headers/ast.h"
#include "../Headers/gen.h"

void genCodeFunc(DefNodePtr func)
{
    SymEntryPtr prevfunc = curfunc;
    curfunc = func->sym;
    fprintf(af, "F%04d:\n", func->sym->no);
    fprintf(af, "      ld _FP\n");
    fprintf(af, "      push\n");
    fprintf(af, "      mv acc, sp\n");
    fprintf(af, "      st _FP\n");
    fprintf(af, "      sub #%04d\n", func->sym->nVar);  
    fprintf(af, "      mv sp, acc\n");
    genCodeStmt(func->body);
    fprintf(af, "      push\n");
    fprintf(af, "E%04d:\n", func->sym->no);
    fprintf(af, "      ld _FP\n");
    fprintf(af, "      mv ixr, acc\n");
    fprintf(af, "      pop\n");
    fprintf(af, "      st ixr, %04d\n", func->sym->nParam + 2);
    fprintf(af, "      mv sp, ixr\n");
    fprintf(af, "      pop\n");
    fprintf(af, "      st _FP\n");
    fprintf(af, "      ret\n");
    curfunc = prevfunc;
}   