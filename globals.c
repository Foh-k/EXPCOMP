#include "ast.h"
#include "gen.h"
#include <stdio.h>
#include <stdlib.h>

DefNodePtr sourcedefs;

void genCodeGlobals()
{
    DefNodePtr defs = sourcedefs;
    while (defs)
    {
        if (defs->sort == DEF_GLOBAL)
            fprintf(af, "G%04d:.space 1 ; Global Variable %s", sourcedefs->sym->no, sourcedefs->sym->name);

        defs = defs->next;
    }
}

void genCodeFuncs()
{
    DefNodePtr defs = sourcedefs;
    while (defs)
    {
        if (defs->sort == DEF_FUNC)
            genCodeFunc(defs);
        
        defs = defs->next;
    }
}
