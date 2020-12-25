#include <stdio.h>
#include <unistd.h>
#include "Headers/ast.h"
#include "Headers/gen.h"
#include "Yaccs/y.tab.h"

FILE *af;
extern FILE *yyin;

void help(FILE *o)
{
    fprintf(o, "Usage: ./expcc [options] {file | code}\n");
    fprintf(o, "Options:\n");
    fprintf(o, "-h            \t View help\n");
    fprintf(o, "-o <filename> \t define output filename. if you don't use this option, file is named \"a.asm\" automatically\n");
    fprintf(o, "-t            \t output for stdout\n");
    exit(0);
}

int main(int argc, char *argv[])
{
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
        char *filename = "a.asm";
        if ((af = fopen(filename, "w")) == NULL)
        {
            fprintf(stderr, "Open file a.asm is failed\n");
        }
    }

    if (optind == argc)
    {
        yyin = stdin;
    }
    else
    {
        if ((yyin = fopen(argv[optind], "r")) == NULL)
        {
            fprintf(stderr, "Open file %s is failed\n", argv[optind]);
            exit(1);
        }
    }

    yyparse();
    genCode();

    fclose(yyin);
    fclose(af);
    return 0;
}