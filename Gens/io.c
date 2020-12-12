#include <stdio.h>
#include <stdlib.h>
#include "../Headers/ast.h"
#include "../Headers/gen.h"

void in()
{
    // FP操作は無意味なので省略
    fprintf(af, "F0000:    ; call in()\n");
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      in 0\n");
    fprintf(af, "      st ixr, 1\n");
    fprintf(af, "      ret\n");
}

void out()
{
    // FP操作は無意味なので省略
    fprintf(af, "F0001:    ; call out()\n");
    fprintf(af, "      mv ixr, sp\n");
    fprintf(af, "      ld ixr, 1\n");
    fprintf(af, "      out 0\n");
    fprintf(af, "      ret\n");
}