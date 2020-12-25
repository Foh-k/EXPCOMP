%{
    // C code
    #include "../Headers/ast.h"
    #include "../Headers/gen.h"
    
    extern int yylex(void);
    int yyerror(char *msg);
    void output();
%}

%union {
    int ival;
    char *name;
    ExprNodePtr expr;   
    StmtNodePtr stmt;
    DefNodePtr def;
    SymEntryPtr sym;
}

%token <ival> NUM
%token <name> ID
%type <expr> expr
%type <expr> alist

%token IF ELSE WHILE RETURN
%type <stmt> st_list stmt if_part

%token TINT
%type <sym> decl_gvar
%type <def> program global_def

%type <def> func_def

%right ASSIGN
%left LOR
%left LAND
%left BLT BEQ BNE
%left ADD SUB
%left MUL DIV MOD
%left BAND BOR XOR
%left LSHIFT RSHIFT
%right NOT UM
%right BNOT
%right INC DEC

%left ','

%start program

%%


expr
    : NUM   { $$ = makeExpr(OP_CONST, $1, NULL, NULL, NULL); }
    | ID ASSIGN expr   { $$ = makeExpr(OP_ASSIGN, 0, symLookup($1), $3, NULL); }
    | expr LOR expr { $$ = makeExpr(OP_LOR, 0, NULL, $1, $3); }
    | expr LAND expr { $$ = makeExpr(OP_LAND, 0, NULL, $1, $3); }
    | expr BLT expr { $$ = makeExpr(OP_BLT, 0, NULL, $1, $3); }
    | expr BEQ expr { $$ = makeExpr(OP_BEQ, 0, NULL, $1, $3); }
    | expr BNE expr { $$ = makeExpr(OP_BNE, 0, NULL, $1, $3); }
    | expr ADD expr { $$ = makeExpr(OP_ADD, 0, NULL, $1, $3); }
    | expr SUB expr { $$ = makeExpr(OP_SUB, 0, NULL, $1, $3); }
    | expr MUL expr { $$ = makeExpr(OP_MUL, 0, NULL, $1, $3); }
    | expr DIV expr { $$ = makeExpr(OP_DIV, 0, NULL, $1, $3); }
    | expr MOD expr { $$ = makeExpr(OP_MOD, 0, NULL, $1, $3); }
    | expr BAND expr { $$ = makeExpr(OP_BAND, 0, NULL, $1, $3); }
    | expr XOR expr { $$ = makeExpr(OP_XOR, 0, NULL, $1, $3); }
    | expr LSHIFT expr  { $$ = makeExpr(OP_LSHIFT, 0, NULL, $1, $3); }
    | expr RSHIFT expr  { $$ = makeExpr(OP_RSHIFT, 0, NULL, $1, $3); }
    | NOT expr  { $$ = makeExpr(OP_NOT, 0, NULL, $2, NULL); }
    | SUB expr %prec UM { $$ = makeExpr(OP_UM, 0, NULL, $2, NULL); }
    | BNOT expr { $$ = makeExpr(OP_BNOT, 0, NULL, $2, NULL); }
    | INC expr  { $$ = makeExpr(OP_INC, 0, NULL, $2, NULL); }
    | DEC expr  { $$ = makeExpr(OP_DEC, 0, NULL, $2, NULL); }
    | ID '(' alist ')'  { $$ = makeFuncExpr(OP_FUNCALL, $1, $3); }
    | '(' expr ')'  { $$ = $2; }
    | ID    { $$ = makeExpr(OP_VAR, 0, symLookup($1), NULL, NULL); }
    ;

alist
    : /* Empty */ { $$ = NULL; }
    | expr { $$ = makeExpr(OP_ALIST, 0, NULL, $1, NULL); }
    | alist ',' expr { $$ = makeExpr(OP_ALIST, 0, NULL, $1, $3); }
    ;

st_list
    : /* Empty */ { $$ = NULL; }
    | st_list stmt  { $$ = addStmt($1, $2); }
    ;

stmt
    : '{' st_list '}'   { $$ = $2; }
    | expr ';'  { $$ = makeStmt(STMT_EXPR, $1, NULL, NULL); }
    | if_part   /* implict */
    | if_part ELSE stmt { $1->st2 = $3; $$ = $1; }
    | WHILE '(' expr ')' stmt { $$ = makeStmt(STMT_WHILE, $3, $5, NULL); }
    | RETURN expr ';'   { $$ = makeStmt(STMT_RETURN, $2, NULL, NULL); }
    ;

if_part
    : IF '(' expr ')' stmt  { $$ = makeStmt(STMT_IF, $3, $5, NULL); }
    ;

program
    : global_def    { sourcedefs = $1; $$ = $1; }
    | program global_def    { $1->next = $2; $$ = $2; }
    ;

global_def
    : decl_gvar ';' { $$ = makeDef(DEF_GLOBAL, $1, NULL); }
    | f_head ';'    { $$ = removeProtoParams(); }
    | func_def  /* implict */
    ;

func_def
    : f_head '{' decl_lvar_list st_list '}' { $$ = funcDef($4); }
    ;

f_head
    : TINT ID '(' { funcHead($2); } p_list ')' { funcParams(); }
    ;

p_list
    : /* Empty */
    | p_list_l
    ;

p_list_l
    : decl_par
    | p_list_l ',' decl_par
    ;

decl_par
    : TINT ID   { paramAdd($2); }
    ;

decl_lvar_list
    : /* Empty */
    | decl_lvar_list decl_lvar ';'
    ;

decl_lvar
    : TINT ID   { lvarAdd($2); }
    ;

decl_gvar
    : TINT ID   { $$ = addgvar($2); }
    ;


%%

int yyerror(char *msg)
{
    fprintf(stderr, "yyerror(): \"%s\".\n", msg);
    output();
    return 0;
}

void output()
{
    fprintf(stderr, "output\n");
    // DefNodePtr dfs = sourcedefs;
    // while(dfs)
    // {
    //     fprintf(stdout, "%s\n", dfs->sym->name);
    //     dfs = dfs->next;
    // }
    // genCode();
}