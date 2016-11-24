#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#include <iostream.h>
//========================面向对象的STACK=========================//
class OOSTK{
	int  *const  elems;		//申请内存用于存放栈的元素
	const  int   max;			//栈能存放的最大元素个数
	int   pos;					//栈实际已有元素个数，栈空时pos=0;
public:
	OOSTK(int m);			//初始化栈：最多m个元素
	OOSTK(const OOSTK &s);//用栈s拷贝初始化栈
	int  size ( ) const;			//返回栈的最大元素个数max
	int  howMany ( ) const;	//返回栈的实际元素个数pos
	int  getelem (int x) const;	//取下标x处的栈元素
	OOSTK& push(int e); 		//将e入栈，并返回当前栈
	OOSTK& pop(int &e); 	//出栈到e，并返回当前栈
	OOSTK& assign(const OOSTK &s); 	//赋s给栈，并返回被赋值的当前栈
	void print( ) const;						//打印栈
	~OOSTK( );							//销毁栈
};
OOSTK::OOSTK(int m): elems(m>0?new int[m]:new int [0]), max(m>0?m:0){
	pos = 0;
}
OOSTK::OOSTK(const OOSTK &s): elems(s.max>0?new int[s.max]: new int[0]),max(s.max>0?s.max:0){
	pos = s.pos;
	for (int i = 0; i < max; ++i) {
		elems[i] = s.elems[i];
	}
}
int OOSTK::size() const {
	return max;
}
int OOSTK::howMany() const {
	return pos;
}
int  OOSTK::getelem (int x) const {
	return elems[x];
}
OOSTK& OOSTK::push(int e) {
	if (pos == max) exit(-1);
	elems[pos++] = e;
	return *this;
}
OOSTK& OOSTK::pop(int &e) {
	if (!pos) exit(-1);
	e = elems[--pos];
	return *this;
}
OOSTK& OOSTK::assign(const OOSTK &s) {
	if (max < s.max) {//如果s的元素数目比p多，则先申请一块较大的内存作为重新作为p的数组空间
		int **tmp = (int **)&(this->elems);
		*tmp = (int *)malloc(s.max * sizeof(int));
		for (int i = 0; i < s.max; ++i)
		{
			*tmp[i] = s.elems[i];
		}
		this->pos = s.pos;
		return *this;
	}
	for (int i = 0; i < s.max; ++i)
	{
		elems[i] = s.elems[i];
	}
	pos = s.pos;
	return *this;
}
void OOSTK::print() const {
	for (int i = 0; i < pos; ++i) {
		printf("%d ", elems[i]);
	} 
}
OOSTK::~OOSTK(){
	delete elems;
	pos = 0;
}
//---------------------------------------------------------------------------
int main(){
	OOSTK *stk1, *stk2;
	int em, sz, n, pz;
	int op = 1, temp =0;
    stk2 = new OOSTK(5);//预先初始化的栈，用来测试构造函数和赋值函数
    stk2 -> push(1); 
    stk2 -> push(2); 
    stk2 -> push(3); 
    stk2 -> push(4); 
    stk2 -> push(5); 

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
				cout << "请输入需要初始化的栈的容量：\n\t\t";
				cin >>sz;
				getchar();
				stk1 = new OOSTK(sz);
				cout << "\t\t初始化成功\n";
				break;
			case 2:
				stk1 = new OOSTK(*stk2);
				cout << "\t\t初始化成功\n";
				break;
			case 3:
				sz = stk1 -> size();
				cout << "\t\t栈的大小是" << sz;
				break;
			case 4:
				pz = stk1 -> howMany();
				cout << "\t\t栈中有" << pz <<"个数据\n";
				break;
			case 5:
				cout << "你要取出第几个元素？\n";
				cin >> n;
				getchar();
				em = stk1 -> getelem(n);
				cout << "\t\t第" << n << "个元素是" << em << "\n";
				break;
			case 6:
				stk1 -> push(temp);
				cout << "\t\t已将数字" << temp << "入栈\n";
				pz = stk1 -> howMany();
				sz = stk1 -> size();
				cout << "\t\t栈中已有" << pz << "个数据，最多可存放" << sz <<"个数据\n";
				break;
			case 7:
				stk1 -> pop(em);
				cout << "\t\t出栈成功，栈尾元素是" << em << "\n";
				pz = stk1 -> howMany();
				cout << "\t\t栈中有" << pz <<"个数据，最少需存放0个数据\n";
				break;
			case 8:
				stk1 -> assign(*stk2);
				cout << "\t\t赋值成功\n";
				break;
			case 9:
				stk1 -> print();
				break;
			case 10:
				stk1 -> ~OOSTK();
				cout << "\t\t销毁成功\n";
				break;
			case 0:
				goto et;
		}
		getchar();
	}
et:
	return 0;	
}
