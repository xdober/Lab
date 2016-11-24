#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
//=========================面向过程的STACK========================//
struct POSTK{
	int  *elems;				//申请内存用于存放栈的元素
	int   max;					//栈能存放的最大元素个数
	int   pos;					//栈实际已有元素个数，栈空时pos=0;
};
void initPOSTK(POSTK *const p, int m);		//初始化p指的栈：最多m个元素
void initPOSTK(POSTK *const p, const POSTK&s); //用栈s初始化p指的栈
int  size (const POSTK *const p);				//返回p指栈的最大元素个数max
int  howMany (const POSTK *const p);		//返回p指栈的实际元素个数pos
int  getelem (const POSTK *const p, int x);	//取下标x处的栈元素
POSTK *const push(POSTK *const p, int e); 	//将e入栈，并返回p值
POSTK *const pop(POSTK *const p, int &e); 	//出栈到e，并返回p值
POSTK *const assign(POSTK*const p, const POSTK&s); //赋s给p指的栈，返p值
void print(const POSTK*const p);				//打印p指向的栈
void destroyPOSTK(POSTK*const p);			//销毁p指向的栈

void initPOSTK(POSTK *const p, int m) {
	p->elems = (int *)malloc(m*sizeof(int));
	if (!p->elems) {
		//printf("构造失败！\n");
		return;
	};
	p->max = m;
	p->pos = 0;
	//printf("构造成功！\n");
}
void initPOSTK(POSTK *const p, const POSTK&s) {
	p->elems = (int *)malloc((s.max)*sizeof(int));//根据s的最大个数申请p的空间
	if (!p->elems) {
		printf("构造失败！\n");
		return;
	};
	memcpy(p->elems, s.elems, (s.pos)*sizeof(int));//把s的内容复制到p
	p->max = s.max;
	p->pos = s.pos;
	printf("构造成功！\n");
}
int size (const POSTK *const p) {
	return p->max;
}
int  howMany (const POSTK *const p) {
	return p->pos;
}
int  getelem (const POSTK *const p, int x) {
	return p->elems[x];
}
POSTK *const push(POSTK *const p, int e) {
	if (p->pos == p->max) exit(-1);
	p->elems[p->pos++] = e;
	return p;
}
POSTK *const pop(POSTK *const p, int &e) {
	if (!p->pos) exit(-1);
	e = p->elems[--p->pos];
	return p;
}
POSTK *const assign(POSTK*const p, const POSTK&s) {
	if (p->max < s.max) {//空间不足先申请空间
		free(p->elems);
		p->elems = (int *)malloc((s.max)*sizeof(int));
	}
	memcpy(p->elems, s.elems, (s.max)*sizeof(int));
	p->max = s.max;
	p->pos = s.pos;
	return p;
}
void print(const POSTK*const p) {
	int i=0;
	for ( ; i < p->pos; ++i)
	{
		printf("%d ", p->elems[i]);
	}
}
void destroyPOSTK(POSTK*const p) {
	free(p->elems);
	free(p);
}

int main(){
	POSTK *stk1 = (POSTK *)malloc(sizeof(POSTK));
	POSTK *stk2 = (POSTK *)malloc(sizeof(POSTK));
	int em;
	int op = 1, sz, pz, n=2, temp = 0;
	initPOSTK(stk2,10);
	for (int i = 0; i < 10; ++i)
	{
		push(stk2,i);
	}
	while(op) {
		temp++;
		system("cls");
		printf("\n\n");
		printf("\t\t\tMenu for STACK\n");
		printf("\t\t--------------------------------------------\n");
		printf("\t\t1.initStack\t\t2.initStack from a stack\n");
		printf("\t\t3.size of stack\t\t4.pos of stack\n");
		printf("\t\t5.get one elem\t\t6.push\n");
		printf("\t\t7.pop\t\t\t8.assign\n");
		printf("\t\t9.print\t\t\t10.destroy\n");
		printf("\t\t0.exit\n");
		printf("\t\t--------------------------------------------\n");
		printf("\t请选择你的操作\n");
		scanf("%d",&op);getchar();
		switch(op) {
			case 1:
				initPOSTK(stk1,10);
				printf("\t\t初始化成功\n");
				break;
			case 2:
				initPOSTK(stk1,*stk2);
				printf("初始化成功\n");
				break;
			case 3:
				sz = size(stk1);
				printf("\t\t栈的大小是%d",sz);
				break;
			case 4:
				pz = howMany(stk1);
				printf("\t\t栈中有%d个数据",pz);
				break;
			case 5:
				em = getelem(stk1,n);
				printf("\t\t第%d个元素是%d", n+1,em);
				break;
			case 6:
				push(stk1, temp);
				printf("\t\t已将数字%d入栈\n", temp);
				pz = howMany(stk1);
				sz = size(stk1);
				printf("\t\t栈中已有%d个数据，最多可存放%d个数据", pz, sz);
				break;
			case 7:
				pop(stk1, em);
				printf("\t\t出栈成功，栈尾元素是%d\n", em);
				pz = howMany(stk1);
				printf("\t\t栈中有%d个数据，最少需存放0个数据", pz);
				break;
			case 8:
				assign(stk1, *stk2);
				printf("复制成功\n");
				break;
			case 9:
				print(stk1);
				break;
			case 10:
				destroyPOSTK(stk1);
				printf("\t\t销毁成功\n");
				break;
			case 0:
				goto et;
		}
		getchar();
	}
et:
	return 0;
}




