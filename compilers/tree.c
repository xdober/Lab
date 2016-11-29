#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>//变长参数函数所需的头文件
#include <string.h>
#include "tree.h"
extern int yyparse(void);
extern int cher;
int i;
struct Node *newNode(char* name,int num,...)//抽象语法树建立
{
	va_list valist; //定义变长参数列表
	struct Node *a=(struct Node*)malloc(sizeof(struct Node));//新生成的父节点
	struct Node *temp=(struct Node*)malloc(sizeof(struct Node));
	if(!a) 
	{
		exit(0);
	}
	a->name=name;//语法单元名字
	va_start(valist,num);//初始化变长参数为num后的参数
	if(num>0)//num>0为非终结符：变长参数均为语法树结点，孩子兄弟表示法
	{
		temp=va_arg(valist, struct Node*);//取变长参数列表中的第一个结点设为a的左孩子
		a->lchild=temp;
		a->line=temp->line;//父节点a的行号等于左孩子的行号
		if(num>=2) //可以规约到a的语法单元>=2
		{
			for(i=0; i<num-1; ++i)//取变长参数列表中的剩余结点，依次设置成兄弟结点
			{
				temp->rchild=va_arg(valist,struct Node*);
				temp=temp->rchild;
			}
		}
	}
	else //num==0为终结符或产生空的语法单元：第1个变长参数表示行号，产生空的语法单元行号为-1。
	{
		int t=va_arg(valist, int); //取第1个变长参数
		a->line=t;
		if((!strcmp(a->name,"identifier"))||(!strcmp(a->name,"TYPE")))//"ID,TYPE,INTEGER，借助union保存yytext的值
		{
			char*t;
			t=(char*)malloc(sizeof(char* )*40);
			strcpy(t,yytext);
			a->type=t;
		}
		else if(!strcmp(a->name,"intnumber")) {
			a->value=atoi(yytext);
		} else if(!strcmp(a->name,"floatnumber")){
			a->value=atof(yytext);
		}
		else {}
	}
	return a;
}

void eval(struct Node *a,int level)//先序遍历抽象语法树
{
    if(a!=NULL&&!cher)
    {
        for(i=0; i<level; ++i)//孩子结点相对父节点缩进2个空格
            printf("  ");
        if(a->line!=-1){ //产生空的语法单元不需要打印信息
            printf("%s ",a->name);//打印语法单元名字，identifier/TYPE/intnum要打印yytext的值
            if((!strcmp(a->name,"identifier"))||(!strcmp(a->name,"TYPE")))printf(":%s ",a->type);
            else if(!strcmp(a->name,"intnumber"))printf(":%.0f",a->value);
            else if(!strcmp(a->name,"floatnumber")) printf(":%f",a->value);
            else  printf("(%d)",a->line);
        }
        printf("\n");

        eval(a->lchild,level+1);//遍历左子树
        eval(a->rchild,level);//遍历右子树
    }
}
