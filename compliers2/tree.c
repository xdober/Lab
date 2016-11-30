# include"tree.h"
extern void yyrestart(FILE * f);
extern int yyparse(void);
extern int yyerror(const char*);
int i,flag_xsj=0;
int size_xsj = 0;//数组大小
int x1=0;//变量个数
int x2=0;//函数个数
int x3=0;//数组个数
int x4=0;//结构体个数
int x5=0;//形参个数
int paramnum= 0;//实参个数
struct ast *newast(char* name,int num,...)//抽象语法树建立
{
    va_list valist; //定义变长参数列表
    struct ast *a=(struct ast*)malloc(sizeof(struct ast));//新生成的父节点
    struct ast *temp;
    if(!a)
    {
        yyerror("out of space");
        exit(0);
    }
    a->name=name;//语法单元名字
    va_start(valist,num);//初始化变长参数为num后的参数

    if(num > 0)//num>0为非终结符：变长参数均为语法树结点，孩子兄弟表示法
    {
        temp=va_arg(valist, struct ast*);//取变长参数列表中的第一个结点设为a的左孩子
        a->l=temp;
        a->line=temp->line;//父节点a的行号等于左孩子的行号
        if(num == 1)
	{
	    a->content = temp->content;//父节点的语义值等于左孩子的语义值
	//printf("/n这儿是多少呢？%d/n",temp->tag);
            a->tag =temp->tag;
	}
        if(num >= 2) //可以规约到a的语法单元>=2
        {
            for(i = 0; i < num-1; ++i)//取变长参数列表中的剩余结点，依次设置成兄弟结点
            {
                temp->r=va_arg(valist,struct ast*);
                temp=temp->r;
            }
        }
    }
    else //num==0为终结符或产生空的语法单元：第1个变长参数表示行号，产生空的语法单元行号为-1。
    {
        int t=va_arg(valist, int); //取第1个变长参数
        a->line=t;
        if(!strcmp(a->name,"INT"))
	{
	    a->type = "int";
	    a->value=atof(yytext);
	}
	else if(!strcmp(a->name,"FLOAT"))
	{
	    a->type = "FLOAT";
	    a->value=atof(yytext);
	}
	else{
	    char* s;
	    s = (char*)malloc(sizeof(char)*40);//存储词法单元的语义值
	    strcpy(s,yytext);
	    a->content = s;
	}
    }
    return a;
}

void eval(struct ast *a,int level)//先序遍历抽象语法树
{
    if(a!=NULL)
    {
        for(i=0; i<level; ++i)//孩子结点相对父节点缩进2个空格
        {
            printf("  ");
        }
        if(a->line!=-1){ //产生空的语法单元不需要打印信息
            printf("%s ",a->name);//打印语法单元名字，ID/TYPE/INTEGER要打印yytext的值
            if((!strcmp(a->name,"ID"))||(!strcmp(a->name,"TYPE")))
            {
                printf(":%s ",a->content);
            }
            else if(!strcmp(a->name,"INT"))
            {
                printf(":%s",a->type);
            }
            else
            {
                printf("(%d)",a->line);
            }
        }
        printf("\n");

        eval(a->l,level+1);//遍历左子树
        eval(a->r,level);//遍历右子树
    }
}

/*建立变量符号表*/
void newvar(int num,...)
{
    va_list valist;//定义变长参数列表
    struct var *a=(struct var*)malloc(sizeof(struct var));//新生成的父节点
    struct ast *temp;
    va_start(valist,num);//初始化变长参数为num后的参数
    temp=va_arg(valist, struct ast*);//取变长参数列表中的第一个结点
    if(temp->scope!=NULL)
    {
        a->type = temp->scope;
    }
    else
    {
        a->type = temp->content;
    }
    temp=va_arg(valist, struct ast*);//取变长参数列表中的第二个结点
    a->name = temp->content;
    vartail->next = a;
    vartail = a;
    x1++;
}

/*查找变量是否定义，1表示已经定义，0表示未定义*/
int is_var_define(struct ast* temp)
{
    int flag=0;
    struct var* p = (struct var*)malloc(sizeof(struct var));
    p = varhead->next;
	while(p!=NULL)
    {
		if(p->name!=NULL&&temp->content!=NULL)
		{
			if(!strcmp(p->name,temp->content))
			{
		    		flag = 1;
		    		return 1;
			}
		}
		p = p->next;
    }
	if(!flag)
	{
    	return 0;
	}
}
/*给变量赋作用域*/
void scopevar(char* name)
{
	struct var* temp=varhead;
	while(temp!=NULL)
	{
		if(temp->scope==NULL)
		{
			temp->scope=name;
		}
		temp=temp->next;
	}
}


/*查找变量的类型*/
char* var_type(struct ast* temp)
{
    struct var* p = (struct var*)malloc(sizeof(struct var*));
    p = varhead->next;
    while(p!=NULL)
    {
	if(p->name!=NULL&&temp->content!=NULL)
	{
	if(!strcmp(p->name,temp->content))
        {
            return p->type;
        }
	}
        p = p->next;
    }
}
//查找变量作用域
char* var_scope(struct ast* temp)
{
    struct var* p = (struct var*)malloc(sizeof(struct var*));
    p = varhead->next;
    while(p!=NULL)
    {
	if(p->name!=NULL&&temp->content!=NULL)
	{
		if(!strcmp(p->name,temp->content))
        	{
            		return p->scope;
        	}
	}
        p = p->next;
    }
}

/*建立函数符号表*/
void newfunc(int num,...)
{
    va_list valist; //定义变长参数列表
    struct ast *temp=(struct ast*)malloc(sizeof(struct ast));
    va_start(valist,num);//初始化变长参数为num后的参数
    switch(num)
    {
    case 1:
	    functail->paramnum = functail->paramnum + 1;
	    break;
	case 2://记录函数名
	    temp=va_arg(valist, struct ast*);//取变长参数列表中的第一个结点
	    functail->name = temp->content;
	    x2++;
        break;
	case 3://记录返回值
	    temp=va_arg(valist, struct ast*);//取变长参数列表中的第一个结点
	    functail->rtype = temp->type;
	    break;
	default://记录函数类型,返回类型不匹配则报出错误
        temp=va_arg(valist, struct ast*);//取变长参数列表中的第1个结点
	    if(functail->rtype!=NULL)
	    {
		if(strcmp(functail->rtype,temp->content))
		{
		    printf("Error type 8 at line %d: Type mismatched for return.\n",yylineno);
	  	    flag_xsj=1;
		}
            }
	    functail->type = temp->content;
	    functail->tag = 1;
	    struct func* a = (struct func*)malloc(sizeof(struct func));
	    functail->next = a;
	    functail = a;
	    break;
    }

}

/*查找函数是否定义，1表示已经定义，0表示未定义*/
int is_func_define(struct ast* temp)
{
    int flag=0;
    struct func* p = (struct func*)malloc(sizeof(struct func*));
    p = funchead->next;
    while(p!=NULL&&p->name!=NULL&&p->tag==1)
    {
        if(!strcmp(p->name,temp->content))
	{
	    flag = 1;
	    return 1;
	}
	p = p->next;
    }
    if(!flag)
	return 0;
}

/*查找函数的类型*/
char* func_type(struct ast* temp)
{
    struct func* p = (struct func*)malloc(sizeof(struct func*));
    p = funchead->next;
    while(p!=NULL)
    {
        if(!strcmp(p->type,temp->content))
        {
            return p->type;
        }
        p = p->next;
    }
}

/*查找函数的形参个数*/
int func_formalnum(struct ast* temp)
{
    struct func* p = (struct func*)malloc(sizeof(struct func*));
    p = funchead->next;
    while(p!=NULL)
    {
        if(!strcmp(p->type,temp->content))
        {
            return p->paramnum;
        }
        p = p->next;
    }
}
/*形参符号表*/
void newparamvar(int num,...)
{
    va_list valist;//定义变长参数列表
    struct paramvar *a=(struct paramvar*)malloc(sizeof(struct paramvar));//新生成的父节点
    struct ast *temp;
    va_start(valist,num);//初始化变长参数为num后的参数
    temp=va_arg(valist, struct ast*);//取变长参数列表中的第一个结点
    a->type = temp->content;
    temp=va_arg(valist, struct ast*);//取变长参数列表中的第二个结点
    a->name = temp->content;
    paramvartail->next = a;
    paramvartail = a;
    x5++;
}
/*给形参赋作用域*/
void scopeparamvar(char* name)
{
	struct paramvar* temp=paramvarhead;
	while(temp!=NULL)
	{
		if(temp->scope==NULL)
		{
			temp->scope=name;
		}
		temp=temp->next;
	}
}
/*查找变量是否定义，1表示已经定义，0表示未定义*/
int is_paramvar_define(struct ast* temp)
{
	int flag=0;
	struct paramvar* p = (struct paramvar*)malloc(sizeof(struct paramvar));
	p = paramvarhead->next;
	while(p!=NULL)
        {
		if(p->name!=NULL&&temp->content!=NULL)
		{
			if(!strcmp(p->name,temp->content))
			{
		    		flag = 1;
		    		return 1;
			}
		}
        	p = p->next;
    	}
    	if(!flag)
    	{
        	return 0;
    	}
}
/*建立数组符号表*/
void newarray(int num,...)
{
    va_list valist;//定义变长参数列表
    struct array *a=(struct array*)malloc(sizeof(struct array));//新生成的父节点
    struct ast *temp;
    va_start(valist,num);//初始化变长参数为num后的参数
    temp=va_arg(valist, struct ast*);//取变长参数列表中的第一个结点
    a->type = temp->content;
    temp=va_arg(valist, struct ast*);//取变长参数列表中的第二个结点
    a->name = temp->content;
    a->size = size_xsj;
    arraytail->next = a;
    arraytail = a;
    x3++;
}
/*查找数组是否定义，1表示已经定义，0表示未定义*/
int is_array_define(struct ast* temp)
{
    int flag=0;
    struct array* p = (struct array*)malloc(sizeof(struct array*));
    p = arrayhead->next;
    while(p!=NULL)
    {
        if(!strcmp(p->name,temp->content))
	{
	    flag = 1;
	    return 1;
	}
	p = p->next;
    }
    if(!flag)
	return 0;
}
void scopearray(char* name)
{
	struct array* temp=arrayhead;
	while(temp!=NULL)
	{
		if(temp->scope==NULL)
		{
			temp->scope=name;
		}
		temp=temp->next;
	}
}
/*查找数组的类型*/
char* array_type(struct ast* temp)
{
    struct array* p = (struct array*)malloc(sizeof(struct array*));
    p = arrayhead->next;
    while(p!=NULL)
    {
        if(!strcmp(p->type,temp->content))
        {
            return p->type;
        }
        p = p->next;
    }
}

/*建立结构体符号表*/
void newstruc(int num,...)
{
    va_list valist;//定义变长参数列表
    struct struc *a=(struct struc*)malloc(sizeof(struct struc));//新生成的父节点
    struct ast *temp;
    va_start(valist,num);//初始化变长参数为num后的参数
    	temp=va_arg(valist, struct ast*);//取变长参数列表中的第一个结点
    	a->name = temp->content;
	a->type = "struct";
    structail->next = a;
    structail = a;
    x4++;
}


/*查找结构体是否定义，1表示已经定义，0表示未定义*/
int is_struc_define(struct ast* temp)
{
    int flag=0;
    struct struc* p = (struct struc*)malloc(sizeof(struct struc*));
    p = struchead;
    while(p!=NULL)
    {
	if(temp->content!=NULL&&p->name!=NULL)
	if(!strcmp(p->name,temp->content))
	{
	    flag = 1;
	    return 1;
	}
	p = p->next;
    }
    if(!flag)
	return 0;
}

/*查找结构体的类型*/
char* struc_type(struct ast* temp)
{
    struct struc* p = (struct struc*)malloc(sizeof(struct struc*));
    p = struchead->next;
    while(p!=NULL)
    {
        if(!strcmp(p->type,temp->content))
        {
            return p->type;
        }
        p = p->next;
    }
}


/*检查结构体里面是否重复定义*/
int is_vardefine(struct var* head)
{
	int i,j;
	int err=0,flag_err=0;
	struct var* temp1 = head;
	struct var* temp2;
	char* p;
	for(i = 0;i < x1;i++)
	{
		temp2=temp1->next;
		for(j = i;j < x1;j++)
		{
			if(temp1->name!=NULL&&temp2->name!=NULL)
			{
				if(!strcmp(temp1->name,temp2->name))
				{
					if(temp1->scope == NULL&&temp2->scope == NULL)
					{
		    			err=1;
						flag_xsj=1;
						p = temp1->name;
						break;
					}
					else if(temp1->scope != NULL&&temp2->scope != NULL)
					{
						if(!strcmp(temp1->scope,temp2->scope))
						{
							err=2;
							flag_xsj=1;
							p = temp1->name;
							break;
						}
					}
				}
			}
			temp2 = temp2->next;
		}
		if(err==1)
		{
			printf("Error type 3 at line %d：Redefined variable '%s'\n",yylineno,p);
			flag_err = 1;
			err = 0;
		}
		else if(err == 2)
		{
			printf("Error type 15 at line %d：Redefined field '%s'\n",yylineno,p);
			flag_err = 2;
			err = 0;
		}
		temp1 = temp1->next;
	}
	return flag_err;
}
int is_arraydefine(struct array* head)
{
	int i,j;
	int err=0,flag_err = 0;
	struct array* temp1 = head;
	struct array* temp2;
	char* p;
	for(i = 0;i < x3;i++)
	{
		temp2=temp1->next;
		for(j = i;j < x3;j++)
		{
			if(temp1->name!=NULL&&temp2->name!=NULL)
			{
				if(!strcmp(temp1->name,temp2->name))
				{
					if(temp1->scope == NULL&&temp2->scope == NULL)
					{
		    			err=1;
						flag_xsj=1;
						p = temp1->name;
					}
					else if(temp1->scope != NULL&&temp2->scope != NULL)
					{
						if(!strcmp(temp1->scope,temp2->scope))
						{
							err=2;
							flag_xsj=1;
							p = temp1->name;
						}
					}
				}
			}
			temp2 = temp2->next;
		}
		if(err==1)
		{
			printf("Error type 3 at line %d：Redefined array '%s'\n",yylineno,p);
			flag_err = 1;
			err = 0;
		}
		else if(err == 2)
		{
			printf("Error type 15 at line %d：Redefined field '%s'\n",yylineno,p);
			flag_err = 2;
			err = 0;
		}
		temp1 = temp1->next;
	}
	return flag_err;
}
int main(int argc,char** argv)
{
	int flag_err=0;
	varhead=(struct var*)malloc(sizeof(struct var));//变量符号表头指针
        vartail=varhead;//变量符号表尾指针
	funchead=(struct func*)malloc(sizeof(struct func));//函数符号表头指针
	functail=(struct func*)malloc(sizeof(struct func));//函数符号表尾指针
	funchead->next = functail;//函数符号表尾指针
	functail->paramnum=0;
	struct func* temp;
	temp = funchead->next;
	paramvarhead=(struct paramvar*)malloc(sizeof(struct paramvar));//形参符号表头指针
        paramvartail=paramvarhead;//变量符号表尾指针
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
	if(flag_xsj == 0)
	{
		printf("变量符号表\n");
		for(i = 0; i < x1; i++)
		{
	    		varhead=varhead->next;
	    		printf("%s  %s  %s\n",varhead->type,varhead->name,varhead->scope);
		}
		printf("\n");
		printf("函数符号表\n-------------------------\n");
		temp->paramnum = x5;
		for(i = 0; i < x2; i++)
		{
	    		funchead=funchead->next;
	    		printf("%s  %s  %s  %d\n",funchead->type,funchead->name,funchead->rtype,funchead->paramnum);
		}
		printf("\n");
		printf("形参符号表\n-------------------------\n");
		for(i = 0; i < x5; i++)
		{
	    		paramvarhead=paramvarhead->next;
	    		printf("%s  %s  %s\n",paramvarhead->type,paramvarhead->name,paramvarhead->scope);
		}
		printf("\n-------------------------\n\n\n");
        	printf("数组符号表\n-------------------------\n");
		for(i = 0; i < x3; i++)
		{
		    arrayhead=arrayhead->next;
		    printf("%s  %s  %d  %s\n",arrayhead->type,arrayhead->name,arrayhead->size,arrayhead->scope);
		}
		printf("\n-------------------------\n\n\n");
		printf("结构体符号表\n-------------------------\n");
		for(i = 0; i < x4; i++)
		{
		    struchead=struchead->next;
		    printf("%s  %s\n",struchead->type,struchead->name);
		}
		}
	return 0;
}
