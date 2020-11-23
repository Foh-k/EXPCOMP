#include "ast.h"
#include "gen.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *af;
int divcall = 0;

void divLib(void)
{
    fprintf(af, "; calculation library (div/mod)\n");
    fprintf(af, "_div:  mv ixr, sp\n");
    fprintf(af, "       ld ixr, 2\n");
    fprintf(af, "       or #0\n");
    fprintf(af, "       jsp _div1\n");
    fprintf(af, "       ld #0\n");
    fprintf(af, "       jp _div2\n");
    fprintf(af, "_div1: not\n");
    fprintf(af, "       inc acc\n");
    fprintf(af, "       st ixr, 2\n");
    fprintf(af, "       ld #3\n");
    fprintf(af, "_div2: push\n");
    fprintf(af, "       ld ixr, 1\n");
    fprintf(af, "       or #0\n");
    fprintf(af, "       jps _div3\n");
    fprintf(af, "       jpz _div_error\n");
    fprintf(af, "       jp _div4\n");
    fprintf(af, "_div3: not\n");
    fprintf(af, "       inc acc\n");
    fprintf(af, "       st ixr, 1\n");
    fprintf(af, "       ld ixr, -1\n");
    fprintf(af, "       eor #1\n");
    fprintf(af, "       st ixr, -1\n");
    fprintf(af, "_div4: ld #0\n");
    fprintf(af, "       push\n");
    fprintf(af, "       ld #1\n");
    fprintf(af, "       push\n");
    fprintf(af, "_div_pre:\n");
    fprintf(af, "       ld ixr, 1\n");
    fprintf(af, "       lsl\n");
    fprintf(af, "       jps _div_loop\n");
    fprintf(af, "       st ixr, 1\n");
    fprintf(af, "       ld ixr, -3\n");
    fprintf(af, "       lsl\n");
    fprintf(af, "       st ixr, -3\n");
    fprintf(af, "       jp _div_pre\n");
    fprintf(af, "div_loop:\n");
    fprintf(af, "       ld ixr, 2\n");
    fprintf(af, "       sub ixr, 1\n");
    fprintf(af, "       jps _div5\n");
    fprintf(af, "       st ixr, 2\n");
    fprintf(af, "       ld ixr, -2\n");
    fprintf(af, "       or #1\n");
    fprintf(af, "       st ixr, -2\n");
    fprintf(af, "_div5: ld ixr, -3\n");
    fprintf(af, "       lsr\n");
    fprintf(af, "       jpc _div6\n");
    fprintf(af, "       st ixr, -3\n");
    fprintf(af, "       ld ixr, 1\n");
    fprintf(af, "       lsr\n");
    fprintf(af, "       st ixr, 1\n");
    fprintf(af, "       ld ixr, -2\n");
    fprintf(af, "       lsl\n");
    fprintf(af, "       st ixr, -2\n");
    fprintf(af, "       jp _div_loop\n");
    fprintf(af, "_div6: ld ixr, -1\n");
    fprintf(af, "       and #0xFE\n");
    fprintf(af, "       ld ixr, -2\n");
    fprintf(af, "       jpz _div7\n");
    fprintf(af, "       not\n");
    fprintf(af, "       inc acc\n");
    fprintf(af, "_div7: st ixr, 1\n");
    fprintf(af, "       ld ixr, -1\n");
    fprintf(af, "       and #0xFD\n");
    fprintf(af, "       jpz _div8\n");
    fprintf(af, "       ld ixr, 2\n");
    fprintf(af, "       not\n");
    fprintf(af, "       inc acc\n");
    fprintf(af, "       st ixr, 2\n");
    fprintf(af, "_div8: mv sp, ixr\n");
    fprintf(af, "       ret\n");
    fprintf(af, "_div_error:\n");
    fprintf(af, "       halt\n");
}