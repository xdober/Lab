%{
	#include "lex.yy.c"
	#include "tree.h"
	#include <stdio.h>
	#include <unistd.h>
	int yyerror(const char *msg);
	extern void eval(struct Node *a,int level);
	int cher = 0;
	int pnum=0;
%}

%error-verbose
%locations
%union{
struct Node* a;
double d;
}
%token <a> TYPE STRUCT
%token <a> IF ELSE WHILE  RETURN
%token <a> LD RD FH DH
%token <a> intnumber floatnumber identifier e_r_r_o_r
%type  <a> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag  Tag VarDec  FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args EESSL
%left <a> LB RB LF RF DOT RELOP AND OR AD SU MU DI
%right <a> NT AS
%nonassoc  xdnb
%nonassoc ELSE
%%
Program : ExtDefList {
	$$=newNode("Program",1,$1);
		printf("打印syntax tree:\n");
		eval($$,0);
		printf("syntax tree打印完毕!\n\n");
	}
ExtDefList : ExtDef ExtDefList {$$=newNode("ExtDefList",2,$1,$2);}
	| {$$=newNode("ExtDef",0,-1);}
	;
ExtDef : Specifier ExtDecList FH {
	$$=newNode("ExtDef",3,$1,$2,$3);
	}
	| Specifier FH {$$=newNode("ExtDef",2,$1,$2);}
	| Specifier FunDec CompSt {
	$$=newNode("ExtDef",3,$1,$2,$3);
	}
	|error FH{yyerrok;cher =1;}
	;
ExtDecList : VarDec {$$=newNode("ExtDecList",1,$1);}
	| VarDec DH ExtDecList {$$=newNode("ExtDecList",3,$1,$2,$3);}
	;
Specifier : TYPE {$$=newNode("Specifier",1,$1);}
	| StructSpecifier {$$=newNode("Specifier",1,$1);}
	;
StructSpecifier : STRUCT OptTag LD DefList RD {
	$$=newNode("StructSpecifier",5,$1,$2,$3,$4,$5);
	}
	| STRUCT Tag {
	$$=newNode("StructSpecifier",2,$1,$2);
	}
	;
OptTag : identifier {
		$$=newNode("OptTag",1,$1);
	}
	| {$$=newNode("OptTag",0,-1);}
	;
Tag : identifier {$$=newNode("Tag",1,$1);}
	;
VarDec : identifier {
		$$=newNode("VarDec",1,$1);
		$$->tag = 1;
	}
	| VarDec LF intnumber RF {
		$$=newNode("VarDec",4,$1,$2,$3,$4);
		$$->tag = 4;
	}
	|error RF{yyerrok;cher =1;}
	;
FunDec : identifier LB VarList RB {
		$$=newNode("FunDec",4,$1,$1,$2,$3,$4);
	}
	| identifier LB RB {
		$$=newNode("FunDec",3,$1,$2,$3);
	}
	;
VarList : ParamDec DH VarList {$$=newNode("VarList",3,$1,$2,$3);}
	| ParamDec {$$=newNode("VarList",1,$1);}
	;
ParamDec : Specifier VarDec {$$=newNode("ParamDec",2,$1,$2);}
	;
CompSt : LD DefList StmtList RD {$$=newNode("CompSt",4,$1,$2,$3,$4);}
	;
StmtList : Stmt StmtList {$$=newNode("StmtList",2,$1,$2);}
	| {$$=newNode("StmtList",0,-1);}
	;
Stmt : Exp FH {$$=newNode("Stmt",2,$1,$2);}
	|CompSt {$$=newNode("Stmt",1,$1);}
	| RETURN Exp FH {$$=newNode("Stmt",3,$1,$2,$3);}
	| IF LB Exp RB Stmt EESSL {$$=newNode("Stmt",6,$1,$2,$3,$4,$5,$6);}
	| WHILE LB Exp RB Stmt {$$=newNode("Stmt",5,$1,$2,$3,$4,$5);}
	| error FH {yyerrok;cher =1;}
	|error EESSL {yyerrok;cher =1;}
	;
EESSL : ELSE Stmt {$$=newNode("EESSL",2,$1,$2);}
	| %prec xdnb {$$=newNode("EESSL",0,-1);}
	;
DefList : Def DefList {$$=newNode("DefList",2,$1,$2);}
	| {$$=newNode("DefList",0,-1);}
	;
Def : Specifier DecList FH {
	$$=newNode("Def",3,$1,$2,$3);
	}
	;
DecList : Dec {$$=newNode("DecList",1,$1);}
	| Dec DH DecList {$$=newNode("DecList",3,$1,$2,$3);}
	;
Dec : VarDec {$$=newNode("Dec",1,$1);}
	|VarDec AS Exp {$$=newNode("Dec",3,$1,$2,$3);}
	;
Exp : Exp AS Exp {
	$$=newNode("Exp",3,$1,$2,$3);
	}
	|Exp AND Exp {$$=newNode("Exp",3,$1,$2,$3);}
	|Exp OR Exp {$$=newNode("Exp",3,$1,$2,$3);}
	|Exp RELOP Exp {$$=newNode("Exp",3,$1,$2,$3);}
	|Exp AD Exp {
	$$=newNode("Exp",3,$1,$2,$3);
	}
	|Exp SU Exp {
	$$=newNode("Exp",3,$1,$2,$3);
	}
	|Exp MU Exp {
	$$=newNode("Exp",3,$1,$2,$3);
	}
	|Exp DI Exp {
	$$=newNode("Exp",3,$1,$2,$3);
	}
	|LB Exp RB {$$=newNode("Exp",3,$1,$2,$3);}
	|SU Exp {$$=newNode("Exp",2,$1,$2);}
	|NT Exp {$$=newNode("Exp",2,$1,$2);}
	|identifier LB Args RB {
	$$=newNode("Exp",4,$1,$2,$3,$4);
	}
	|identifier LB RB {$$=newNode("Exp",3,$1,$2,$3);}
	|Exp LF Exp RF {
	$$=newNode("Exp",4,$1,$2,$3,$4);
	}
	|Exp DOT identifier {
	$$=newNode("Exp",3,$1,$2,$3);
	}
	|identifier {
	$$=newNode("Exp",1,$1);
	}
	|intnumber {
		$$=newNode("Exp",1,$1);
	}//整型常数
	|floatnumber {
		$$=newNode("Exp",1,$1);
		$$->tag=3;
		$$->type="floatnumber";
		$$->value=$1->value;
	} //浮点型常数
    | error RB {yyerrok;}
    | error RF {yyerrok;}
    | error AD Exp {yyerrok;}
    | error SU Exp {yyerrok;}
    | error MU Exp {yyerrok;}
    | error DI Exp {yyerrok;}
	;
Args : Exp DH Args {$$=newNode("Args",3,$1,$2,$3);
	pnum=pnum+1;}
	|Exp {$$=newNode("Args",1,$1);pnum=pnum+1;}
	;
%%

int yyerror(const char* msg) {
	fprintf(stderr,"%d:%d:error: %s\n", yylloc.first_line, yylloc.first_column, msg);
	return 0;
}
