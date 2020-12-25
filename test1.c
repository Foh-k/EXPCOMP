#include <stdio.h>
#include <unistd.h>
#include "Headers/ast.h"
#include "Headers/gen.h"
#include "Yaccs/y.tab.h"

#define ECONST(k) makeExpr(OP_CONST, k, NULL, NULL, NULL)
#define EVAR(p) makeExpr(OP_VAR, 0, p, NULL, NULL)
#define EBIN(op, l, r) makeExpr(op, 0, NULL, l, r)
#define SEXPR(e) makeStmt(STMT_EXPR, e, NULL, NULL)
#define IN(var) SEXPR(makeExpr(OP_ASSIGN, 0, var, makeExpr(OP_FUNCALL, 0, fin, NULL, NULL), NULL))
#define OUT(f) SEXPR(makeExpr(OP_FUNCALL, 0, fout, makeExpr(OP_ALIST, 0, NULL, f, NULL), NULL))

FILE *af;
extern FILE *yyin;

void test()
{
    SymEntryPtr fin = makeSym(SYM_FUNC, "in", 0, 0, 0, NULL);
    SymEntryPtr fout = makeSym(SYM_FUNC, "out", 1, 1, 0, NULL);
    SymEntryPtr fib = makeSym(SYM_FUNC, "fib", 2, 1, 0, NULL);
    SymEntryPtr param_k = makeSym(SYM_PARAM, "k", 1, 0, 0, fib);

    StmtNodePtr l2 = makeStmt(STMT_IF,
                              EBIN(OP_BLT, EVAR(param_k), ECONST(2)),
                              makeStmt(STMT_RETURN, ECONST(1), NULL, NULL),
                              NULL);

    ExprNodePtr listleft = makeExpr(OP_ALIST, 0, NULL, EBIN(OP_SUB, EVAR(param_k), ECONST(2)), NULL);
    ExprNodePtr listright = makeExpr(OP_ALIST, 0, NULL, EBIN(OP_SUB, EVAR(param_k), ECONST(1)), NULL);
    ExprNodePtr fibleft = makeExpr(OP_FUNCALL, 0, fib, listleft, NULL);
    ExprNodePtr fibright = makeExpr(OP_FUNCALL, 0, fib, listright, NULL);

    StmtNodePtr l3 = makeStmt(STMT_RETURN,
                              EBIN(OP_ADD, fibleft, fibright),
                              NULL,
                              NULL);

    l2->next = l3;

    sourcedefs = makeDef(DEF_FUNC, fib, l2);
    SymEntryPtr mein = makeSym(SYM_FUNC, "main", 3, 0, 1, NULL);
    SymEntryPtr lclv = makeSym(SYM_VAR, "v", 1, 0, 0, mein);

    StmtNodePtr l8 = IN(lclv);

    ExprNodePtr fibcall = makeExpr(OP_FUNCALL, 0, fib, makeExpr(OP_ALIST, 0, NULL, EVAR(lclv), NULL), NULL);
    StmtNodePtr l9 = OUT(fibcall);
    l8->next = l9;

    StmtNodePtr l10 = makeStmt(STMT_RETURN, ECONST(0), NULL, NULL);
    l9->next = l10;

    sourcedefs->next = makeDef(DEF_FUNC, mein, l8);

    genCode();
}

void testtable()
{
    // symtableに追加
    symAdd(SYM_VAR, "test", 0, 0, 0, NULL);
    symAdd(SYM_VAR, "dummy", 1, 0, 0, NULL);
    // symtableからの検索
    SymEntryPtr look = symLookup("test");
    printf("%s\n", look->name);
}

extern int yylex(void);

void lextest()
{
    int tok;
    while ((tok = yylex()) != 0)
    {
        if (tok < 128)
        {
            printf("CHAR: %c\n", tok);
        }
        else
        {
            switch (tok)
            {
            case NUM:
                printf("NUMBER: %d\n", yylval.ival);
                break;
            case ID:
                printf("ID: %s\n", yylval.name);
                break;
            case IF:
                printf("IF\n");
                break;
            case ELSE:
                printf("ELSE\n");
                break;
            case WHILE:
                printf("WHILE\n");
                break;
            case RETURN:
                printf("RETURN\n");
                break;
            case TINT:
                printf("TINT\n");
                break;
            case ASSIGN:
                printf("ASSIGN\n");
                break;
            case LOR:
                printf("LOR\n");
                break;
            case LAND:
                printf("LAND\n");
                break;
            case BLT:
                printf("BLT\n");
                break;
            case BEQ:
                printf("BEQ\n");
                break;
            case BNE:
                printf("BNE\n");
                break;
            case ADD:
                printf("ADD\n");
                break;
            case SUB:
                printf("SUB\n");
                break;
            case MUL:
                printf("MUL\n");
                break;
            case DIV:
                printf("DIV\n");
                break;
            case MOD:
                printf("MOD\n");
                break;
            case BAND:
                printf("BAND\n");
                break;
            case BOR:
                printf("BOR\n");
                break;
            case XOR:
                printf("XOR\n");
                break;
            case LSHIFT:
                printf("LSHIFT\n");
                break;
            case RSHIFT:
                printf("RSHIFT\n");
                break;
            case NOT:
                printf("NOT\n");
                break;
            case UM:
                printf("UM\n");
                break;
            case BNOT:
                printf("BNOT\n");
                break;
            case INC:
                printf("INC\n");
                break;
            case DEC:
                printf("DEC\n");
            default:
                break;
            }
        }
    }
}

void help(FILE *o)
{
    fprintf(o, "Usage: ./test1 [options] file\n");
    fprintf(o, "Options:\n");
    fprintf(o, "-h            \t View help\n");
    fprintf(o, "-o <filename> \t define output filename. if you don't use this option, file is named \"a.asm\" automatically\n");
    fprintf(o, "-t            \t output for stdout\n");
    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        // ファイル名指定なし
        fprintf(stderr, "need to select a file written by picoC\n");
        help(stderr);
    }

    int opt;
    const char *optstring = "hto:";

    while ((opt = getopt(argc, argv, optstring)) != -1)
    {
        switch (opt)
        {
        // ヘルプ表示
        case 'h':
            help(stdout);
            break;

        // 標準出力に表示
        case 't':
            af = stdout;
            break;

        // ファイル名指定
        case 'o':
            if ((af = fopen(optarg, "w")) == NULL)
            {
                fprintf(stderr, "Open file %s is failed\n", optarg);
                exit(0);
            }

            break;

        default:
            fprintf(stderr, "Invalid option\n");
            help(stderr);
            break;
        }
    }
    if (!af)
    {
        char* filename = "a.asm";
        if ((af = fopen(filename, "w")) == NULL)
        {
            fprintf(stderr, "Open file a.asm is failed\n");
        }
    }

    if ((yyin = fopen(argv[optind], "r")) == NULL)
    {
        fprintf(stderr, "Open file %s is failed\n", argv[optind]);
        exit(1);
    }

    // test();
    // testtable();
    // lextest();
    yyparse();
    genCode();

    fclose(af);
    return 0;
}