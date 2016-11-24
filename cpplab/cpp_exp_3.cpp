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
//---------------------------------------------------------------------------
int main(){
    STACK *stk1, *stk2;
    int em, sz, n, pz;
    int op = 1, temp =0;
    stk2 = new STACK(5);//预先初始化的栈，用来测试构造函数和赋值函数
    *stk2 << 1; 
    *stk2 << 2; 
    *stk2 << 3; 
    *stk2 << 4; 
    *stk2 << 5; 

    while(op) {
        temp++;
        system("cls");
        cout << "\n\n";
        cout << "\t\t\tMenu for STACK\n";
        cout << "\t\t--------------------------------------------\n";
        cout << "\t\t1.initStack\t\t2.initStack from a stack\n";
        cout << "\t\t3.size of stack\t\t4.pos of stack\n";
        cout << "\t\t5.get one elem\t\t6.push\n";
        cout << "\t\t7.pop\t\t\t8.assign\n";
        cout << "\t\t9.print\t\t\t10.destroy\n";
        cout << "\t\t0.exit\n";
        cout << "\t\t--------------------------------------------\n";
        cout << "\t请选择你的操作：";
        scanf("%d",&op);getchar();
        switch(op) {
            case 1:
                cout << "\t\t请输入需要初始化的栈的容量：";
				cin >>sz;     getchar();
                stk1 = new STACK(sz);
                cout << "\t\t初始化成功\n";
                break;
            case 2:
                stk1 = new STACK(*stk2);
                cout << "\t\t初始化成功\n";
                break;
            case 3:
                sz = stk1 -> size();
                cout << "\t\t栈的大小是" << sz;
                break;
            case 4:
                pz = *stk1;
                cout << "\t\t栈中有" << pz <<"个数据\n";
                break;
            case 5:
                cout << "你要取出第几个元素？\t";
                cin >> n;
                getchar();
                cout << "\t\t第" << n << "个元素是" << (*stk1)[n] << "\n";
                break;
            case 6:
                *stk1 << temp;
                cout << "\t\t已将数字" << temp << "入栈\n";
                pz = *stk1;
                sz = stk1 -> size();
                cout << "\t\t栈中已有" << pz << "个数据，最多可存放" << sz <<"个数据\n";
                break;
            case 7:
                *stk1 >> em;
                cout << "\t\t出栈成功，栈尾元素是" << em << "\n";
                pz = *stk1;
                cout << "\t\t栈中有" << pz <<"个数据，最少需存放0个数据\n";
                break;
            case 8:
                *stk1 = *stk2;
                cout << "复制成功\n";
                break;
            case 9:
                cout << "\t\t";
                stk1 -> print();
                break;
            case 10:
                stk1 -> ~STACK();
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



