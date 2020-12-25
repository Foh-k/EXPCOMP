%{
#include <stdlib.h>
#include "../Headers/ast.h"
#include "../Headers/gen.h"
#include "../Yaccs/y.tab.h"
%}

%x COMMENT
%option noyywrap

%%

"/*" { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(0); }

"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"return" { return RETURN; }
"int" { return TINT; }
"=" { return ASSIGN; }
"||" { return LOR;}
"&&" { return LAND;}
"<" { return BLT;}
"==" { return BEQ;}
"!=" { return BNE;}
"+" { return ADD;}
"-" { return SUB;}
"*" { return MUL;}
"/" { return DIV;}
"%" { return MOD;}
"&" { return BAND;}
"|" { return BOR;}
"^" { return XOR;}
"<<" { return LSHIFT;}
">>" { return RSHIFT;}
"!" { return NOT;}
"~" { return BNOT;}
"++" { return INC;}
"--" { return DEC;}

"0x"[0-9A-Fa-f]+  { yylval.ival = strtol(yytext, NULL, 16); return NUM; }
"0"[0-7]*   { yylval.ival = strtol(yytext, NULL, 8); return NUM; }
[1-9][0-9]* {yylval.ival = strtol(yytext, NULL, 10); return NUM; }

[_A-Za-z][_A-Za-z0-9]* {yylval.name = malloc(yyleng+1); strcpy(yylval.name, yytext); return ID; }

[ \t\n] ;

. { return yytext[0]; }

%%