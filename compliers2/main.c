#include<stdio.h>
#include "lex.yy.c"
extern int yyrestart(FILE *f);
extern int yyparse(void);
int main(int argc,char** argv)
{
	varhead=(struct var*)malloc(sizeof(struct var));//变量符号表头指针
        vartail=varhead;//变量符号表尾指针
	funchead=(struct func*)malloc(sizeof(struct func));//函数符号表头指针
	functail=(struct func*)malloc(sizeof(struct func));//函数符号表尾指针
        funchead->next = functail;//函数符号表尾指针
	arrayhead=(struct array*)malloc(sizeof(struct array));//数组符号表头指针
        arraytail=arrayhead;//数组符号表尾指针
	struchead=(struct struc*)malloc(sizeof(struct struc));//结构体符号表头指针
        structail=struchead;//结构体符号表尾指针
	if(argc <= 1) return 1;
	FILE* f = fopen(argv[1],"r");
	if(!f)
	{
		perror(argv[1]);
		return 1;
	}
	yyrestart(f);
	yyparse();
	return 0;
}
