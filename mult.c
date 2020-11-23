#include "ast.h"
#include "gen.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *af;
int multcall = 0;

void multLib(void)
{
    fprintf(af, "; calculation library routine (multiply)");
    fprintf(af, "_mul:  mv ixr, sp\n");
    fprintf(af, "       ld #0\n");
    fprintf(af, "       push\n");
    fprintf(af, "       ld ixr, 2\n");
    fprintf(af, "       or #0\n");
    fprintf(af, "       jsp _mul1\n");
    fprintf(af, "       ld #0\n");
    fprintf(af, "       jp  _mul2\n");
    fprintf(af, "_mul1: not\n");
    fprintf(af, "       inc acc\n");
    fprintf(af, "       st ixr, 2\n");
    fprintf(af, "       ld #1\n");
    fprintf(af, "_mul2: push\n");
    fprintf(af, "_mul_loop:      \n");
    fprintf(af, "       ld ixr, 2\n");
    fprintf(af, "       asr\n");
    fprintf(af, "       st ixr, 2\n");
    fprintf(af, "       jpc _mul3\n");
    fprintf(af, "       jpz _mul4\n");
    fprintf(af, "       jp  _mul5\n");
    fprintf(af, "_mul3: ld ixr, 1\n");
    fprintf(af, "       add ixr, -1\n");
    fprintf(af, "       st ixr, -1\n");
    fprintf(af, "_mul5: ld ixr, 1\n");
    fprintf(af, "       asl\n");
    fprintf(af, "       st ixr, 1\n");
    fprintf(af, "       jp _mul_loop\n");
    fprintf(af, "_mul4: pop\n");
    fprintf(af, "       or #0\n");
    fprintf(af, "       pop\n");
    fprintf(af, "       jpz _mul6\n");
    fprintf(af, "       not\n");
    fprintf(af, "       inc acc\n");
    fprintf(af, "_mul6: st ixr, 2\n");
    fprintf(af, "       ret\n");

}