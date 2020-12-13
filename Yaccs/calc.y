%{

#include <stdio.h>
#include <string.h>

#define YYSTYPE double

extern int yydebug;

int yylex(void);
int yyerror(char *msg);

%}

%token NUM UMINUS

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

line
    : /* Empty */     { printf("> "); }
    | line expr '\n'  { printf("%f\n> ", $2); }
    | line error '\n' { yyerrok; }
    ;

expr
    : expr '+' expr         { $$ = $1 + $3; }
    | expr '-' expr         { $$ = $1 - $3; }
    | expr '*' expr         { $$ = $1 * $3; }
    | expr '/' expr         { $$ = $1 / $3; }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')'          { $$ = $2; }
    | NUM
    ;

%%

int yylex(void)
{
    int c;
    
    while((c = getchar()) == ' ');
    
    if((('0' <= c) && (c <= '9')) || c == '.')
    {
        ungetc(c, stdin);
        scanf("%lf", &yylval);
        return NUM;
    }
    else
    {
        return c;
    }
}

int main(int argc, char *argv[])
{
    /* Set flag if "-d" option specified. */
    if (argc == 2 && strcmp(argv[1], "-d") == 0)
    {
        yydebug = 1;
    }

    yyparse();
    return 0;
}

int yyerror(char *msg)
{
    fprintf(stderr, "yyerror(): \"%s\".\n", msg);
    return 0;
}