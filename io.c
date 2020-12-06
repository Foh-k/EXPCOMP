#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "gen.h"

void in()
{
    // FP操作は無意味なので省略
    fprintf(af, "F0000d:    ; call in()\n");
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      in #0\n");
    fprintf(af, "      st ixr, 2\n");
    fprintf(af, "      ret\n");
}

void out()
{
    // FP操作は無意味なので省略
    fprintf(af, "F0001d:    ; call in()\n");
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, #2");
    fprintf(af, "      out #0\n");
    fprintf(af, "      ret\n");
}