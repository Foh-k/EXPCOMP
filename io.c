#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "gen.h"

void in(DefNodePtr func)
{
    // FP操作は無意味なので省略
    fprintf(af, "F%04d:    ; call in()\n", func->sym->no);
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      in #0\n");
    fprintf(af, "      st ixr, 2\n");
    fprintf(af, "      ret\n");
}

void out(DefNodePtr func)
{
    // in同様FP操作なし
    fprintf(af, "F%04d:    ; call out()\n", func->sym->no);
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 2\n");
    fprintf(af, "      out #0\n");
    fprintf(af, "      st ixr, 3\n");
    fprintf(af, "      ret\n");
}