#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../Headers/ast.h"

int cntGlobal;
int cntFuncs = 2;
int cntLocal;
int cntParam;
int hasProto;

SymEntryPtr symAdd(SymbolSort sort, char *name, int no, int nParam, int nVar, SymEntryPtr belong)
{
    SymEntryPtr sym = makeSym(sort, name, no, nParam, nVar, belong);
    assert(sym);
    sym->prev = symtable;
    symtable = sym;

    return sym;
}

SymEntryPtr addgvar(char *name)
{
    // 記号表にすでに存在
    if (symLookup(name))
    {
        fprintf(stderr, "Duplicated Global Variables are defined\n");
        exit(0);
    }

    return symAdd(SYM_VAR, name, cntGlobal++, 0, 0, NULL);
}

SymEntryPtr symLookup(char *name)
{
    SymEntryPtr t = symtable;
    while (t)
    {
        assert(t);
        if (!strcmp(t->name, name))
        {
            assert(t);
            if ((t->belong == curfunc) || (t->belong == NULL))
            {
                break;
            }
        }

        assert(t);
        t = t->prev;
    }
    return t;
}

StmtNodePtr addStmt(StmtNodePtr stmt1, StmtNodePtr stmt2)
{
    StmtNodePtr s = stmt1;
    if (s)
    {
        while (s->next)
        {
            s = s->next;
        }
        s->next = stmt2;
        return stmt1;
    }
    else
        return stmt2;
}

void funcHead(char *name)
{
    SymEntryPtr sym;
    if ((sym = symLookup(name)) != NULL) // 登録済み
    {
        assert(sym);
        if (sym->sort == SYM_VAR)
        {
            fprintf(stderr, "function declaration is conflicted with variable\n");
            exit(1);
        }

        DefNodePtr defs = sourcedefs;
        assert(defs);
        assert(defs->sym);
        while (defs != NULL && strcmp(defs->sym->name, name))
        {
            defs = defs->next;
        }

        assert(defs);
        if (defs || defs->sort == DEF_FUNC)
        {
            fprintf(stderr, "multipler function definition is detected\n");
            exit(1);
        }

        // プロトタイプ宣言あり
        hasProto = 1;
    }
    else // 初出
    {
        sym = symAdd(SYM_FUNC, name, cntFuncs++, 0, 0, NULL);
        hasProto = 0;
    }
    cntParam = 1;
    cntLocal = 0;
    curfunc = sym;
}

void funcParams()
{
    if (hasProto)
    {
        assert(curfunc);
        if (curfunc->nParam != cntParam - 1)
        {
            fprintf(stderr, "Unmatch number of parameters\n");
            exit(1);
        }
    }
    else
    {
        assert(curfunc);
        curfunc->nParam = cntParam - 1;
    }
}

DefNodePtr removeProtoParams()
{
    if (hasProto)
    {
        fprintf(stderr, "Multiple prototype decralation\n");
        exit(1);
    }

    SymEntryPtr t = symtable;
    assert(t);
    assert(t->belong);
    assert(curfunc);
    while (t->sort == SYM_PARAM && !strcmp(t->belong->name, curfunc->name))
    {
        // 面倒なのでfreeは省略
        t = t->prev;
    }
    symtable = t;

    return makeDef(PROTOTYPE, curfunc, NULL);
}

void paramAdd(char *name)
{
    SymEntryPtr t = symtable;
    while (t)
    {
        assert(t);
        // assert(t->belong);
        assert(curfunc);
        if (t->belong && !strcmp(t->belong->name, curfunc->name))
        {
            if (t->sort == SYM_PARAM && !strcmp(t->name, name))
            {
                fprintf(stderr, "Parameter name is conflicted\n");
                exit(1);
            }
        }
        t = t->prev;
    }

    symAdd(SYM_PARAM, name, cntParam++, 0, 0, curfunc);
}

void lvarAdd(char *name)
{
    SymEntryPtr t = symtable;
    while (t)
    {
        assert(t);
        // assert(t->belong);
        assert(curfunc);
        if (t->belong && !strcmp(t->belong->name, curfunc->name))
        {
            if (t->sort == SYM_VAR && !strcmp(t->name, name))
            {
                fprintf(stderr, "Local Variable name is conflicted\n");
                exit(1);
            }
        }
        t = t->prev;
    }
    symAdd(SYM_VAR, name, cntLocal++, 0, 0, curfunc);
}

DefNodePtr funcDef(StmtNodePtr stmt)
{
    assert(curfunc);
    curfunc->nVar = cntLocal;
    return makeDef(DEF_FUNC, curfunc, stmt);
}