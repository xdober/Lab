%{
#include <stdio.h>
#include <stdlib.h>
#include "syntax.tab.h"
extern struct Node *newNode(char* name,int num,...);
int yycolumn = 1;
#define YY_USER_ACTION    yylloc.first_line = yylloc.last_line = yylineno;	yylloc.first_column = yycolumn;yylloc.last_column = yycolumn + yyleng - 1;yycolumn += yyleng;
int yywrap(void);
%}

%option nounput
%option noinput
%option yylineno

digit [0-9]
eidigit [0-7]
sidigit {[0-9]|[a-f]|[A-F]}
intnumber [+-]?{digit}+|[+-]?0[0-7]*
floatnum [+-]?{digit}+\.{digit}*|[+-]?{digit}*\.{digit}+
letter [a-zA-Z]
identifier ({letter}|_)({digit}|{letter}|_)*
blank [\t\x0B\f\r\x20]+
error1 {digit}+_({letter}|{digit}|_)*

%%
"//"[^\n]*\n { yycolumn = 1; }
"/*"[^"*/"]*"*/" {}
{error1} {yylval.a = newNode("e_r_r_o_r",0,yylineno); return e_r_r_o_r ; }


int|float { yylval.a = newNode("TYPE",0,yylineno);return TYPE ; }
"struct" {yylval.a = newNode("STRUCT",0,yylineno); return STRUCT; }
"if" {yylval.a = newNode("IF",0,yylineno); return IF ; }
"else" {yylval.a = newNode("ELSE",0,yylineno); return ELSE ; }
"while" {yylval.a = newNode("WHILE",0,yylineno); return WHILE ; }
"return" {yylval.a = newNode("RETURN",0,yylineno); return RETURN; }

"(" {yylval.a = newNode("LB",0,yylineno); return LB  ; }
")" {yylval.a = newNode("RB",0,yylineno); return RB  ; }
"[" {yylval.a = newNode("LF",0,yylineno); return LF  ; }
"]" {yylval.a = newNode("RF",0,yylineno); return RF  ; }
"{" {yylval.a = newNode("LD",0,yylineno); return LD ; }
"}" {yylval.a = newNode("RD",0,yylineno); return RD ; }
";" {yylval.a = newNode("FH",0,yylineno); return FH ; }
"," {yylval.a = newNode("DH",0,yylineno); return DH ; }
"." {yylval.a = newNode("DOT",0,yylineno); return DOT  ; }
"-" {yylval.a = newNode("SU",0,yylineno); return SU  ; }
"!" {yylval.a = newNode("NT",0,yylineno); return NT  ; }
"*" {yylval.a = newNode("MU",0,yylineno); return MU  ; }
"/" {yylval.a = newNode("DI",0,yylineno); return DI  ; }
"+" {yylval.a = newNode("AD",0,yylineno); return AD ; }
>|<|<=|>=|==|!= {yylval.a = newNode("RELOP",0,yylineno); return RELOP ; }
"&&" {yylval.a = newNode("AND",0,yylineno); return AND  ; }
"||" {yylval.a = newNode("OR",0,yylineno); return OR  ; }
"=" {yylval.a = newNode("AS",0,yylineno); return AS  ; }

{blank} { }
{identifier} {yylval.a = newNode("identifier",0,yylineno); return identifier ; }
{floatnum} {yylval.a = newNode("floatnumber",0,yylineno); return floatnumber ; }
{intnumber} {yylval.a = newNode("intnumber",0,yylineno); return intnumber ; }
\n  { yycolumn = 1; }
. {yylval.a = newNode("e_r_r_o_r",0,yylineno); return e_r_r_o_r ; }
%%

int yywrap(void) {
	return 1;
}
