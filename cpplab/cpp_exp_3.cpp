#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#include <iostream.h>
//===================�����������������STACK=====================//
class STACK{
    int  *const  elems;		//�����ڴ����ڴ��ջ��Ԫ��
    const  int   max;			//ջ�ܴ�ŵ����Ԫ�ظ���
    int   pos;					//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
    STACK(int m);				//��ʼ��ջ�����m��Ԫ��
    STACK(const STACK&s); 			//��ջs������ʼ��ջ
    virtual int  size ( ) const;				//����ջ�����Ԫ�ظ���max
    virtual operator int ( ) const;			//����ջ��ʵ��Ԫ�ظ���pos
    virtual int operator[ ] (int x) const;		//ȡ�±�x����ջԪ��
    virtual STACK& operator<<(int e); 	//��e��ջ�������ص�ǰջ
    virtual STACK& operator>>(int &e);	//��ջ��e�������ص�ǰջ
    virtual STACK& operator=(const STACK&s); //��s����ǰջ�����ظ�ջ
    virtual void print( ) const;				//��ӡջ
    virtual ~STACK( );						//����ջ
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
    stk2 = new STACK(5);//Ԥ�ȳ�ʼ����ջ���������Թ��캯���͸�ֵ����
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
        cout << "\t��ѡ����Ĳ�����";
        scanf("%d",&op);getchar();
        switch(op) {
            case 1:
                cout << "\t\t��������Ҫ��ʼ����ջ��������";
				cin >>sz;     getchar();
                stk1 = new STACK(sz);
                cout << "\t\t��ʼ���ɹ�\n";
                break;
            case 2:
                stk1 = new STACK(*stk2);
                cout << "\t\t��ʼ���ɹ�\n";
                break;
            case 3:
                sz = stk1 -> size();
                cout << "\t\tջ�Ĵ�С��" << sz;
                break;
            case 4:
                pz = *stk1;
                cout << "\t\tջ����" << pz <<"������\n";
                break;
            case 5:
                cout << "��Ҫȡ���ڼ���Ԫ�أ�\t";
                cin >> n;
                getchar();
                cout << "\t\t��" << n << "��Ԫ����" << (*stk1)[n] << "\n";
                break;
            case 6:
                *stk1 << temp;
                cout << "\t\t�ѽ�����" << temp << "��ջ\n";
                pz = *stk1;
                sz = stk1 -> size();
                cout << "\t\tջ������" << pz << "�����ݣ����ɴ��" << sz <<"������\n";
                break;
            case 7:
                *stk1 >> em;
                cout << "\t\t��ջ�ɹ���ջβԪ����" << em << "\n";
                pz = *stk1;
                cout << "\t\tջ����" << pz <<"�����ݣ���������0������\n";
                break;
            case 8:
                *stk1 = *stk2;
                cout << "���Ƴɹ�\n";
                break;
            case 9:
                cout << "\t\t";
                stk1 -> print();
                break;
            case 10:
                stk1 -> ~STACK();
                cout << "\t\t���ٳɹ�\n";
                break;
            case 0:
                goto et;
        }
        getchar();
    }
et:
    return 0;   
}



