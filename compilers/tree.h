/*
*Name:gramtree_v1.h
*Author:WangLin
*Created on:2015-10-03
*Version 2.0
*Function:定义语法树&变量符号表&函数符号表&数组符号表&结构体符号表
*/
/*来自于词法分析器*/
extern int yylineno;//行号
extern char* yytext;//词
int yyerror(const char *s);//错误处理函数

/*抽象语法树的结点*/
struct Node
{
    int line; //行号
    char* name;//语法单元的名字
    int tag;//1为变量，2为函数，3为常数,4为数组，5为结构体
    struct Node *lchild;//左孩子
    struct Node *rchild;//右孩子
    char* content;//语法单元语义值(int i;i是一个ID，ID的content是‘i’)
    char* type;//语法单元数据类型:主要用于等号和操作符左右类型匹配判断
    float value;//常数值(记录integer和float的数据值)
};

