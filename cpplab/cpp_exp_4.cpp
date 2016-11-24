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
//====================��2��STACK��ɵĶ���========================//
class QUE2S{
    STACK s1, s2;							//һ�����п�������ջ�ۺ϶���
public:
    QUE2S(int m);						//��ʼ�����У�ÿջ���m��Ԫ��
    QUE2S(const QUE2S &q);			//�ö���q���������¶���
    operator int ( ) const;					//���ض��е�ʵ��Ԫ�ظ���
    int size() const;                  //�������
    QUE2S& operator<<(int e); 			//��e����У������ص�ǰ����
    QUE2S& operator>>(int &e);			//�����е�e�������ص�ǰ����
    QUE2S& operator=(const QUE2S &q);//��q����ǰ���в����ظö���
    void print( ) const;						//��ӡ����
    ~QUE2S( );							//���ٶ���
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
        cout << "\t��ѡ����Ĳ�����";
        cin >> op; 	getchar();
        switch(op) {
        	case 1:
        		cout << "\t\t��������е�������";
        		cin >> sz;   getchar();
        		q1 = new QUE2S(sz);
                cout << "\t\t���г�ʼ���ɹ�\n";
                break;
            case 2:
                q1 = new QUE2S(*q2);
                cout << "\t\t���г�ʼ���ɹ�\n";
                break;
            case 3:
                pz = *q1;
                cout << "\t\t��������" << pz << "������\n";
                break;
            case 4:
                *q1 << temp;
                pz = *q1;
                sz = q1 -> size();
                cout << "�ѽ�����" << temp << "�����\n";
                cout << "��ǰ��" << pz << "�����ݣ����ɴ��" << sz << "������\n";
                break;
            case 5:
                *q1 >> em;
                cout << "�ѽ�����" << em << "������\n";
                cout << "��ǰ��" << pz << "�����ݣ���������0������\n";
                break;
            case 6:
                *q1 = *q2;
                cout << "���Ƴɹ�";
                break;
            case 7:
                cout <<"\t\t";
                q1 -> print();
                break;
            case 8:
                q1 -> ~QUE2S();
                cout << "���ٳɹ�\n";
                break;
            case 0:
                goto et;
        }
        getchar();
	}
et:
    return 0;
}