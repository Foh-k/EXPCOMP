#include "ast.h"
#include "gen.h"
#include <stdio.h>
#include <stdlib.h>

DefNodePtr sourcedefs;

void genCodeGlobals()
{
    fprintf(af, "G%04d:.space 1 ; Define Global Variable %s", sourcedefs->sym->no, sourcedefs->sym->name);
}

void genCodeFuncs()
{
    genCodeFunc(sourcedefs);
}

void genCodeDef()
{
    while (sourcedefs)
    {
        switch (sourcedefs->sort)
        {
        case DEF_GLOBAL:
            genCodeGlobals();
            break;

        case DEF_FUNC:
            genCodeFuncs();
            break;

        default:
            fprintf(stderr, "undefined DefSort\n");
            exit(1);
        }

        sourcedefs = sourcedefs->next;
    }
}