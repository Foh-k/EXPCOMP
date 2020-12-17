#include "../Headers/ast.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Ttokens
{
    int sort;
    int ival;
    char *name;
} Ttokens;

#define T_T(t)     \
    {              \
        t, 0, NULL \
    }
#define T_INT(k)     \
    {                \
        NUM, k, NULL \
    }
#define T_ID(n)  \
    {            \
        ID, 0, n \
    }
#define T_CH(c)    \
    {              \
        c, 0, NULL \
    }

Ttokens thetokens[] = {
    T_T(TINT), T_ID("fib"), T_CH('('), T_T(TINT), T_ID("k"), T_CH(')'), T_CH('{'),
    T_T(IF), T_CH('('), T_ID("k"), T_T(BLT), T_INT(2), T_CH(')'), T_CH('{'),
    T_T(RETURN), T_INT(1), T_CH(';'), T_CH('}'),
    T_T(RETURN), T_ID("fib"), T_CH('('), T_ID("k"), T_T(SUB), T_INT(2), T_CH(')'),
    T_T(ADD), T_ID("fib"), T_CH('('), T_ID("k"), T_T(SUB), T_INT(1), T_CH(')'),
    T_CH(';'),
    T_CH('}'),
    T_T(TINT), T_ID("main"), T_CH('('), T_CH(')'), T_CH('{'),
    T_T(TINT), T_ID("v"), T_CH(';'),
    T_ID("v"), T_T(ASSIGN), T_ID("in"), T_CH('('), T_CH(')'), T_CH(';'),
    T_ID("out"), T_CH('('), T_ID("fib"), T_CH('('), T_ID("v"),
    T_CH(')'), T_CH(')'), T_CH(';'),
    T_T(RETURN), T_INT(0), T_CH(';'),
    T_CH('}')};

int yylex()
{
    static int i = 0;
    Ttokens *p = thetokens + i;
    i++;

    // fprintf(stdout, "Load a Token No:%d\n", i);
    // fprintf(stdout, "{%d, %d, %s}\n", p->sort, p->ival, p->name);

    if (p->sort == NUM)
        yylval.ival = p->ival;
    else if (p->sort == ID)
        yylval.name = p->name;

    return p->sort;
}