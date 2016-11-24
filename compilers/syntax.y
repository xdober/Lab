%{
	#include "lex.yy.c"
	#include "tree.h"
	#include <stdio.h>
	#include <unistd.h>
	int yyerror(const char *msg);
	extern int  exitstruc(struct Node* tp);
	extern int  exitvar(struct Node* tp);
	extern int  exitfunc(struct Node* tp);
	extern int  exitarray(struct Node* tp);
	extern int flagxr;
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
	if(!flagxr){
		printf("打印syntax tree:\n");
		eval($$,0);
		printf("syntax tree打印完毕!\n\n");
	}
	}
ExtDefList : ExtDef ExtDefList {$$=newNode("ExtDefList",2,$1,$2);}
	| {$$=newNode("ExtDef",0,-1);}
	;
ExtDef : Specifier ExtDecList FH { //变量定义:检查是否重定义Error type 3
	$$=newNode("ExtDef",3,$1,$2,$3);
	if(exitvar($2)) printf("Error type 3 at line %d:Redefined Variable '%s'\n",yylineno,$2->content);
	else newvar(2,$1,$2);
	}
	| Specifier FH {$$=newNode("ExtDef",2,$1,$2);}
	| Specifier FunDec CompSt {//函数定义:检查实际返回类型与函数类型是否匹配Error type 8
	$$=newNode("ExtDef",3,$1,$2,$3);
	newfunc(4,$1);
	}
	|error FH{yyerrok;cher =1;}
	;
ExtDecList : VarDec {$$=newNode("ExtDecList",1,$1);}
	| VarDec DH ExtDecList {$$=newNode("ExtDecList",3,$1,$2,$3);}
	;
Specifier : TYPE {$$=newNode("Specifier",1,$1);}
	| StructSpecifier {$$=newNode("Specifier",1,$1);}
	;
StructSpecifier : STRUCT OptTag LD DefList RD {//结构体定义:检查是否重定义Error type 16
	$$=newNode("StructSpecifier",5,$1,$2,$3,$4,$5);
	if(exitstruc($2)) printf("Error type 16 at line %d:Duplicated name %s\n",yylineno,$2->content);
	else newstruc(1,$2);}
	| STRUCT Tag {//结构体引用:检查是否未定义就引用Error type 17
	$$=newNode("StructSpecifier",2,$1,$2);
	if(!exitstruc($2)) printf("Error type 17 at Line %d:undefined structure '%s'\n",yylineno,$2->content);}
	;
OptTag : identifier {$$=newNode("OptTag",1,$1);}
	| {$$=newNode("OptTag",0,-1);}
	;
Tag : identifier {$$=newNode("Tag",1,$1);}
	;
VarDec : identifier {$$=newNode("VarDec",1,$1);}
	| VarDec LF intnumber RF {$$=newNode("VarDec",4,$1,$2,$3,$4);}
	|error RF{yyerrok;cher =1;}
	;
FunDec : identifier LB VarList RB {//函数定义:检查是否重复定义Error type 4
	$$=newNode("FunDec",4,$1,$1,$2,$3,$4);
	$$->content=$1->content;
	if(exitfunc($1)) printf("Error type 4 at Line %d:Redefined Function '%s'\n",yylineno,$1->content);
	else newfunc(2,$1);}
	| identifier LB RB {$$=newNode("FunDec",3,$1,$2,$3);}
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
Def : Specifier DecList FH {//变量或数组定义:检查变量是否重定义 Error type 3
	$$=newNode("Def",3,$1,$2,$3);
	if(exitvar($2)||exitarray($2))  printf("Error type 3 at Line %d:Redefined Variable '%s'\n",yylineno,$2->content);
	 else if($2->tag==4) newarray(2,$1,$2);
	else newvar(2,$1,$2);}
	;
DecList : Dec {$$=newNode("DecList",1,$1);}
	| Dec DH DecList {$$=newNode("DecList",3,$1,$2,$3);}
	;
Dec : VarDec {$$=newNode("Dec",1,$1);}
	|VarDec AS Exp {$$=newNode("Dec",3,$1,$2,$3);}
	;
Exp : Exp AS Exp {//检查等号左右类型匹配判断Error type 5
	$$=newNode("Exp",3,$1,$2,$3);
	if($1->type!=NULL && $3->type!=NULL){
		if(strcmp($1->type,$3->type)){printf("Error type 5 at Line %d:Type mismatched for assignment.\n ",yylineno);}
		flagxr = 1;
	}
	}
	|Exp AND Exp {$$=newNode("Exp",3,$1,$2,$3);}
	|Exp OR Exp {$$=newNode("Exp",3,$1,$2,$3);}
	|Exp RELOP Exp {$$=newNode("Exp",3,$1,$2,$3);}
	|Exp AD Exp {//检查操作符左右类型Error type 7
	$$=newNode("Exp",3,$1,$2,$3);
	if(strcmp($1->type,$3->type)) {printf("Error type 7 at Line %d:Type mismatched for operand.\n ",yylineno);}}
	|Exp SU Exp {
	$$=newNode("Exp",3,$1,$2,$3);
	if($1->type==NULL||$3->type==NULL)
	{
	    flagxr=1;
	printf("Error type 7 at line %d：Type mismatched for operands\n",yylineno);
	}	
	else if(strcmp($1->type,$3->type))
	{	
	    printf("Error type 7 at line %d：Type mismatched for operands\n",yylineno);
	    flagxr=1;
	}	
	}
	|Exp MU Exp {//检查操作符左右类型Error type 7
	$$=newNode("Exp",3,$1,$2,$3);
	if($1->type==NULL||$3->type==NULL)
	{
	    flagxr=1;
		printf("Error type 7 at line %d：Type mismatched for operands\n",yylineno);
	}	
	else if(strcmp($1->type,$3->type))
	{	
	    printf("Error type 7 at line %d：Type mismatched for operands\n",yylineno);
	    flagxr=1;
	}
	}
	|Exp DI Exp {//检查操作符左右类型Error type 7
	$$=newNode("Exp",3,$1,$2,$3);
	if($1->type==NULL||$3->type==NULL)
	{
	    flagxr=1;
	    printf("Error type 7 at line %d：Type mismatched for operands\n",yylineno);
	}	
	else if(strcmp($1->type,$3->type))
	{	
	    printf("Error type 7 at line %d：Type mismatched for operands\n",yylineno);
	    flagxr=1;
	}
	}
	|LB Exp RB {$$=newNode("Exp",3,$1,$2,$3);}
	|SU Exp {$$=newNode("Exp",2,$1,$2);}
	|NT Exp {$$=newNode("Exp",2,$1,$2);}
	|identifier LB Args RB {//函数引用:检查是否未定义就调用Error type 2 
	$$=newNode("Exp",4,$1,$2,$3,$4);
	if(exitvar($1)){
		printf("Error type 11 at line %d：'%s'is not a function\n",yylineno,$1->content);
	    flagxr=1;
	}
	else if(!exitfunc($1)){
		printf("Error type 2 at Line %d:undefined Function %s\n ",yylineno,$1->content);
		flagxr=1;
	} 
	}
	|identifier LB RB {$$=newNode("Exp",3,$1,$2,$3);}
	|Exp LF Exp RF {//数组引用：是否定义&标识误用&下标 Error type 10，Error type 12
	$$=newNode("Exp",4,$1,$2,$3,$4);
	if((!exitarray($1))&&(exitvar($1))||(exitfunc($1)))
	{
        printf("Error type 10 at line %d：'%s' is not an array\n",yylineno,$1->content);
 	    flagxr=1;
	}
	else if($3->type == NULL)
	{
	    flagxr=1;
	}
	else if(strcmp("int",$3->type))
	{
	    printf("Error type 12 at line %d：'%f' is not an integer\n",yylineno,$3->value);
	    flagxr=1;
	}
	else if(exitvar($1))
	{
	    printf("Error type 11 at line %d：'%s'is not a function\n",yylineno,$1->content);
	    flagxr=1;
	}	
	else if(!exitarray($1))
	{
	    printf("Error type 2 at line %d：Undefined function '%s'\n",yylineno,$1->content);
	    flagxr=1;
	}
	else newarray(3,$1->type,$1,$2);
	}
	|Exp DOT identifier {//结构体引用:检查点号引用Error type 13
	$$=newNode("Exp",3,$1,$2,$3);
	if(!exitstruc($1)){
		printf("Error type 13 at Line %d:Illegal use of '.'.\n",yylineno);
		flagxr=1;
	}
	}
	|identifier {//变量引用:检查是否定义Error type 1 
	$$=newNode("Exp",1,$1);
	if(!exitvar($1)&&!exitarray($1)){
        printf("Error type 1 at Line %d:undefined variable %s\n ",yylineno,$1->content);
		flagxr=1;
	}
    else $$->type=typevar($1);
	}
	|intnumber {$$=newNode("Exp",1,$1);$$->tag=3;$$->type="intnumber";}//整型常数
	|floatnumber {$$=newNode("Exp",1,$1);$$->tag=3;$$->type="floatnumber";$$->value=$1->value;} //浮点型常数
    | error RB {yyerrok;}
    | error RF {yyerrok;}
    | error AD Exp {yyerrok;}
    | error SU Exp {yyerrok;}
    | error MU Exp {yyerrok;}
    | error DI Exp {yyerrok;}
; 
Args : Exp DH Args {$$=newNode("Args",3,$1,$2,$3);
	pnum=pnum+1;}//记录形参个数
	|Exp {$$=newNode("Args",1,$1);pnum=pnum+1;}
	;
%%

int yyerror(const char* msg) {
	fprintf(stderr,"%d:%d:error: %s\n", yylloc.first_line, yylloc.first_column, msg);
	return 0;
}

