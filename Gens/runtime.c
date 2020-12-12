#include "../Headers/ast.h"
#include "../Headers/gen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int labelNo;
int varNo;

void genCode()
{
    DefNodePtr mainfunc;
    DefNodePtr defs = sourcedefs;
    while (strcmp(defs->sym->name, "main"))
        defs = defs->next;
    mainfunc = defs;

    fprintf(af, "      .text\n");
    fprintf(af, "CRT0:\n");
    fprintf(af, "      ld16 #0xFFE\n");
    fprintf(af, "      mv sp, acc\n");
    fprintf(af, "      call F%04d\n", mainfunc->sym->no);
    fprintf(af, "      halt\n");
    fprintf(af, "\n");
    fprintf(af, "      .data\n");
    fprintf(af, "_FP:  .space 1\n");
    genCodeGlobals();
    fprintf(af, "\n");
    fprintf(af, "      .text\n");
    genCodeFuncs();
    in();
    out();
    multLib();
    divLib();

    fprintf(af, "      .const 0xfff\n");
    fprintf(af, "      .word CRT0\n");
}