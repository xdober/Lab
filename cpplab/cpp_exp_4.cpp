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
//====================由2个STACK组成的队列========================//
class QUE2S{
    STACK s1, s2;							//一个队列可由两个栈聚合而成
public:
    QUE2S(int m);						//初始化队列：每栈最多m个元素
    QUE2S(const QUE2S &q);			//用队列q拷贝构造新队列
    operator int ( ) const;					//返回队列的实际元素个数
    int size() const;                  //最大容量
    QUE2S& operator<<(int e); 			//将e入队列，并返回当前队列
    QUE2S& operator>>(int &e);			//出队列到e，并返回当前队列
    QUE2S& operator=(const QUE2S &q);//赋q给当前队列并返回该队列
    void print( ) const;						//打印队列
    ~QUE2S( );							//销毁队列
};
QUE2S::QUE2S(int m): s1(m>0?m:0), s2(m>0?m:0) {
}
QUE2S::QUE2S(const QUE2S &q): s1(q.s1), s2(q.s2) {
}
QUE2S::operator int ( ) const {
	return s1;
}
int QUE2S::size() const {
    return s1.size();
}
QUE2S& QUE2S::operator<<(int e) {
	s1 << e;
	return *this;
}
QUE2S& QUE2S::operator>>(int &e) {
	int num = s1, temp;
	for (int i = 0; i < num - 1; ++i) {
		s1 >> temp;
		s2 << temp;
	}
	s1 >> e;
	for (int i = 0; i < num - 1; ++i) {
		s2 >> temp;
		s1 << temp;
	}
	return *this;
}
QUE2S& QUE2S::operator=(const QUE2S &q) {
	s1 = q.s1;
	s2 = q.s2;
	return *this;
}
void QUE2S::print() const {
	s1.print();
	return;
}
QUE2S::~QUE2S() {
	s1.~STACK();
	s2.~STACK();
}
int main() {
	QUE2S *q1, *q2;
	int em, op = 1, sz, pz,temp = 0;
    q2 = new QUE2S(15);
    for (int i = 0; i < 15; ++i)
    {
        *q2 << i;
    }
	while(op) {
        temp++;
		system("cls");
        cout << "\n\n";
        cout << "\t\t\tMenu for QUE2S\n";
        cout << "\t\t--------------------------------------------\n";
        cout << "\t\t1.initQUE2S\t\t2.initQUE2S from a QUE2S\n";
        cout << "\t\t3.pos of QUE2S\t\t4.push\n";
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
        		q1 = new QUE2S(sz);
                cout << "\t\t队列初始化成功\n";
                break;
            case 2:
                q1 = new QUE2S(*q2);
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
                q1 -> ~QUE2S();
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