#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#include <iostream.h>
//===================运算符重载面向对象的STACK=====================//
class STACK{
    int  *const  elems;		//申请内存用于存放栈的元素
    const  int   max;			//栈能存放的最大元素个数
    int   pos;					//栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m);				//初始化栈：最多m个元素
    STACK(const STACK&s); 			//用栈s拷贝初始化栈
    virtual int  size ( ) const;				//返回栈的最大元素个数max
    virtual operator int ( ) const;			//返回栈的实际元素个数pos
    virtual int operator[ ] (int x) const;		//取下标x处的栈元素
    virtual STACK& operator<<(int e); 	//将e入栈，并返回当前栈
    virtual STACK& operator>>(int &e);	//出栈到e，并返回当前栈
    virtual STACK& operator=(const STACK&s); //赋s给当前栈并返回该栈
    virtual void print( ) const;				//打印栈
    virtual ~STACK( );						//销毁栈
};
STACK::STACK(int m): elems(m>0?new int[m]:new int [0]), max(m>0?m:0){
    pos = 0;
}
STACK::STACK(const STACK &s): elems(s.max>0?new int[s.max]: new int[0]),max(s.max>0?s.max:0){
    pos = s.pos;
    for (int i = 0; i < max; ++i) {
        elems[i] = s.elems[i];
    }
}
int STACK::size() const {
    return max;
}
STACK::operator int() const {
    return pos;
}
int  STACK::operator[] (int x) const {
    if (x < max) {
        return elems[x];
    } else {
        return 0;
    }
}
STACK& STACK::operator<<(int e) {
    if (pos == max) exit(-1);
    elems[pos++] = e;
    return *this;
}
STACK& STACK::operator>>(int &e) {
    if (!pos) exit(-1);
    e = elems[--pos];
    return *this;
}
STACK& STACK::operator=(const STACK &s) {
    if (max < s.max) {
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
void STACK::print() const {
    for (int i = 0; i < pos; ++i) {
        printf("%d ", elems[i]);
    } 
}
STACK::~STACK(){
    delete elems;
    pos = 0;
}
//======================从STACK继承的队列=========================//
class QUEIS:  public  STACK{		//STACK作为构成队列的第1个栈
    STACK  s;						//s作为构成队列的第2个栈
public:
    QUEIS(int m);						//初始化队列：每栈最多m个元素
    QUEIS(const QUEIS &q); 		//用队列q拷贝初始化队列
    virtual operator int ( ) const;		//返回队列的实际元素个数
    virtual int size() const;		//最大容量
    virtual QUEIS& operator<<(int e); 	//将e入队列，并返回当前队列
    virtual QUEIS& operator>>(int &e);//出队列到e，并返回当前队列
    virtual QUEIS& operator=(const QUEIS &q); //赋q给队列并返回该队列
    virtual void print( ) const;			//打印队列
    virtual ~QUEIS( );					//销毁队列
};
QUEIS::QUEIS(int m): s(m>0?m:0),STACK(m>0?m:0) {

}
QUEIS::QUEIS(const QUEIS &q): s(q.s), STACK(q.s.size()) {

}
QUEIS::operator int() const {
	return s;
}
int QUEIS::size() const {
	return s.size();
}
QUEIS& QUEIS::operator<<(int e) {
	if (s >= s.size()) exit(-1);
	s << e;
	return *this;
}
QUEIS& QUEIS::operator>>(int &e) {
	int num = s,temp;
	for (int i = 0; i < num-1; ++i)
	{
		s >> temp;
		STACK::operator<<(temp);
	}
	s >> e;
	for (int i = 0; i < num-1; ++i)
	{
		STACK::operator>>(temp);
		s << temp;
	}
	return *this;
}
QUEIS& QUEIS::operator=(const QUEIS &q) {
	s = q.s;
	int num = q.s,temp;
	STACK::operator=(q.s);
	for (int i = 0; i < num; ++i)
	{
		STACK::operator>>(temp);
	}
	return *this;
}
void QUEIS::print() const {
	s.print();
	return;
}
QUEIS::~QUEIS() {
	s.~STACK();
//	STACK::~STACK();
}
int main() {
	QUEIS *q1, *q2;
	int em, op = 1, sz, pz,temp = 0;
    q2 = new QUEIS(15);
    for (int i = 0; i < 15; ++i)
    {
        *q2 << i;
    }
	while(op) {
        temp++;
		system("cls");
        cout << "\n\n";
        cout << "\t\t\tMenu for QUEIS\n";
        cout << "\t\t--------------------------------------------\n";
        cout << "\t\t1.initQUEIS\t\t2.initQUEIS from a QUEIS\n";
        cout << "\t\t3.pos of QUEIS\t\t4.push\n";
        cout << "\t\t5.pop\t\t\t6.assign\n";
        cout << "\t\t7.print\t\t\t8.destroy\n";
        cout << "\t\t0.exit\n";
        cout << "\t\t--------------------------------------------\n";
        cout << "\t请选择你的操作：";
        cin >> op; 	getchar();
        switch(op) {
        	case 1:
        		cout << "\t\t请输入队列的容量：";
        		cin >> sz;   getchar();
        		q1 = new QUEIS(sz);
                cout << "\t\t队列初始化成功\n";
                break;
            case 2:
                q1 = new QUEIS(*q2);
                cout << "\t\t队列初始化成功\n";
                break;
            case 3:
                pz = *q1;
                cout << "\t\t队列中有" << pz << "个数据\n";
                break;
            case 4:
                *q1 << temp;
                pz = *q1;
                sz = q1 -> size();
                cout << "已将数字" << temp << "入队列\n";
                cout << "当前有" << pz << "个数据，最多可存放" << sz << "个数据\n";
                break;
            case 5:
                *q1 >> em;
                pz = *q1;
                cout << "已将数字" << em << "出队列\n";
                cout << "当前有" << pz << "个数据，最少需存放0个数据\n";
                break;
            case 6:
                *q1 = *q2;
                cout << "复制成功";
                break;
            case 7:
                cout <<"\t\t";
                q1 -> print();
                break;
            case 8:
                q1 -> ~QUEIS();
                cout << "销毁成功\n";
                break;
            case 0:
                goto et;
        }
        getchar();
	}
et:
    return 0;
}