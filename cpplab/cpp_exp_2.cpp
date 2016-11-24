#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#include <iostream.h>
//========================��������STACK=========================//
class OOSTK{
	int  *const  elems;		//�����ڴ����ڴ��ջ��Ԫ��
	const  int   max;			//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;					//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	OOSTK(int m);			//��ʼ��ջ�����m��Ԫ��
	OOSTK(const OOSTK &s);//��ջs������ʼ��ջ
	int  size ( ) const;			//����ջ�����Ԫ�ظ���max
	int  howMany ( ) const;	//����ջ��ʵ��Ԫ�ظ���pos
	int  getelem (int x) const;	//ȡ�±�x����ջԪ��
	OOSTK& push(int e); 		//��e��ջ�������ص�ǰջ
	OOSTK& pop(int &e); 	//��ջ��e�������ص�ǰջ
	OOSTK& assign(const OOSTK &s); 	//��s��ջ�������ر���ֵ�ĵ�ǰջ
	void print( ) const;						//��ӡջ
	~OOSTK( );							//����ջ
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
	if (max < s.max) {//���s��Ԫ����Ŀ��p�࣬��������һ��ϴ���ڴ���Ϊ������Ϊp������ռ�
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
    stk2 = new OOSTK(5);//Ԥ�ȳ�ʼ����ջ���������Թ��캯���͸�ֵ����
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
		printf("\t��ѡ����Ĳ���\n");
		scanf("%d",&op);getchar();
		switch(op) {
			case 1:
				cout << "��������Ҫ��ʼ����ջ��������\n\t\t";
				cin >>sz;
				getchar();
				stk1 = new OOSTK(sz);
				cout << "\t\t��ʼ���ɹ�\n";
				break;
			case 2:
				stk1 = new OOSTK(*stk2);
				cout << "\t\t��ʼ���ɹ�\n";
				break;
			case 3:
				sz = stk1 -> size();
				cout << "\t\tջ�Ĵ�С��" << sz;
				break;
			case 4:
				pz = stk1 -> howMany();
				cout << "\t\tջ����" << pz <<"������\n";
				break;
			case 5:
				cout << "��Ҫȡ���ڼ���Ԫ�أ�\n";
				cin >> n;
				getchar();
				em = stk1 -> getelem(n);
				cout << "\t\t��" << n << "��Ԫ����" << em << "\n";
				break;
			case 6:
				stk1 -> push(temp);
				cout << "\t\t�ѽ�����" << temp << "��ջ\n";
				pz = stk1 -> howMany();
				sz = stk1 -> size();
				cout << "\t\tջ������" << pz << "�����ݣ����ɴ��" << sz <<"������\n";
				break;
			case 7:
				stk1 -> pop(em);
				cout << "\t\t��ջ�ɹ���ջβԪ����" << em << "\n";
				pz = stk1 -> howMany();
				cout << "\t\tջ����" << pz <<"�����ݣ���������0������\n";
				break;
			case 8:
				stk1 -> assign(*stk2);
				cout << "\t\t��ֵ�ɹ�\n";
				break;
			case 9:
				stk1 -> print();
				break;
			case 10:
				stk1 -> ~OOSTK();
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
