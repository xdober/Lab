%{
#include "tree.h"
#include "syntax.tab.h"
	int yycolumn = 1;
	#define YY_USER_ACTION\
		yylloc.first_line = yylloc.last_line = yylineno;\
		yylloc.first_column = yycolumn;\
		yylloc.last_column = yycolumn + yyleng - 1;\
		yycolumn += yyleng;
	int yywrap(void);
%}
%option yylineno
%option noinput
%option nounput
digit [0-9]
number [-]?({digit}+)
floatnumber [-]?({digit}+"."{digit}*|{digit}*"."{digit}+)
letter [a-zA-Z]
identifier {letter}({digit}|{letter}|_)*
blank [\t\x0B\f\r\x20]+
error ({digit}+)({letter}+)
%%
"//"[^\n]*\n {}
"\n" {yycolumn = 1;}
"/*"[^*/]*"*/" {}
"int"|"float" {yylval.a=newast("TYPE",0,yylineno);return TYPE;}
"if" {yylval.a=newast("IF",0,yylineno);return IF;}
"else" {yylval.a=newast("ELSE",0,yylineno);return ELSE;}
"while" {yylval.a=newast("WHILE",0,yylineno);return WHILE;}
"struct" {yylval.a=newast("STRUCT",0,yylineno);return STRUCT;}
"return" {yylval.a=newast("RETURN",0,yylineno); return RETURN;}
{floatnumber} {yylval.a=newast("FLOAT",0,yylineno); return FLOAT;}
{number} {yylval.a=newast("INT",0,yylineno); return INT;}
{identifier} {yylval.a=newast("ID",0,yylineno); return ID;}
{blank} {}
";" {yylval.a=newast("SEMI",0,yylineno); return SEMI;}
"," {yylval.a=newast("COMMA",0,yylineno); return COMMA;}
"=" {yylval.a=newast("ASSIGNOP",0,yylineno); return ASSIGNOP;}
">"|"<"|">="|"<="|"=="|!= {yylval.a=newast("RELOP",0,yylineno); return RELOP;}
"+" {yylval.a=newast("PLUS",0,yylineno); return PLUS;}
"-" {yylval.a=newast("MINUS",0,yylineno); return MINUS;}
"*" {yylval.a=newast("STAR",0,yylineno); return STAR;}
"/" {yylval.a=newast("DIV",0,yylineno); return DIV;}
"&&" {yylval.a=newast("AND",0,yylineno); return AND;}
"||" {yylval.a=newast("OR",0,yylineno); return OR;}
"." {yylval.a=newast("DOT",0,yylineno); return DOT;}
"!" {yylval.a=newast("NOT",0,yylineno); return NOT;}
"(" {yylval.a=newast("LP",0,yylineno); return LP;}
")" {yylval.a=newast("RP",0,yylineno); return RP;}
"[" {yylval.a=newast("LB",0,yylineno); return LB;}
"]" {yylval.a=newast("RB",0,yylineno); return RB;}
"{" {yylval.a=newast("LC",0,yylineno); return LC;}
"}" {yylval.a=newast("RC",0,yylineno); return RC;}
{error} {printf("Error type A at line %d: Mystirious charachter '%s'\n",yylineno,yytext);}
. {printf("Error type A at line %d: Mystirious charachter '%s'\n",yylineno,yytext);}
%%
int yywrap(void)
{
	return 1;
}
