#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "gen.h"

void in()
{
    fprintf(af, "      in #0\n");
    fprintf(af, "      push\n");
}

void out()
{
    fprintf(af, "      ld _FP\n");
    fprintf(af, "      mv ixr, acc\n");
    fprintf(af, "      ld ixr, 2\n");
    fprintf(af, "      out #0");
}