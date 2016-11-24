#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
//=========================������̵�STACK========================//
struct POSTK{
	int  *elems;				//�����ڴ����ڴ��ջ��Ԫ��
	int   max;					//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;					//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
};
void initPOSTK(POSTK *const p, int m);		//��ʼ��pָ��ջ�����m��Ԫ��
void initPOSTK(POSTK *const p, const POSTK&s); //��ջs��ʼ��pָ��ջ
int  size (const POSTK *const p);				//����pָջ�����Ԫ�ظ���max
int  howMany (const POSTK *const p);		//����pָջ��ʵ��Ԫ�ظ���pos
int  getelem (const POSTK *const p, int x);	//ȡ�±�x����ջԪ��
POSTK *const push(POSTK *const p, int e); 	//��e��ջ��������pֵ
POSTK *const pop(POSTK *const p, int &e); 	//��ջ��e��������pֵ
POSTK *const assign(POSTK*const p, const POSTK&s); //��s��pָ��ջ����pֵ
void print(const POSTK*const p);				//��ӡpָ���ջ
void destroyPOSTK(POSTK*const p);			//����pָ���ջ

void initPOSTK(POSTK *const p, int m) {
	p->elems = (int *)malloc(m*sizeof(int));
	if (!p->elems) {
		//printf("����ʧ�ܣ�\n");
		return;
	};
	p->max = m;
	p->pos = 0;
	//printf("����ɹ���\n");
}
void initPOSTK(POSTK *const p, const POSTK&s) {
	p->elems = (int *)malloc((s.max)*sizeof(int));//����s������������p�Ŀռ�
	if (!p->elems) {
		printf("����ʧ�ܣ�\n");
		return;
	};
	memcpy(p->elems, s.elems, (s.pos)*sizeof(int));//��s�����ݸ��Ƶ�p
	p->max = s.max;
	p->pos = s.pos;
	printf("����ɹ���\n");
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
	if (p->max < s.max) {//�ռ䲻��������ռ�
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
		printf("\t��ѡ����Ĳ���\n");
		scanf("%d",&op);getchar();
		switch(op) {
			case 1:
				initPOSTK(stk1,10);
				printf("\t\t��ʼ���ɹ�\n");
				break;
			case 2:
				initPOSTK(stk1,*stk2);
				printf("��ʼ���ɹ�\n");
				break;
			case 3:
				sz = size(stk1);
				printf("\t\tջ�Ĵ�С��%d",sz);
				break;
			case 4:
				pz = howMany(stk1);
				printf("\t\tջ����%d������",pz);
				break;
			case 5:
				em = getelem(stk1,n);
				printf("\t\t��%d��Ԫ����%d", n+1,em);
				break;
			case 6:
				push(stk1, temp);
				printf("\t\t�ѽ�����%d��ջ\n", temp);
				pz = howMany(stk1);
				sz = size(stk1);
				printf("\t\tջ������%d�����ݣ����ɴ��%d������", pz, sz);
				break;
			case 7:
				pop(stk1, em);
				printf("\t\t��ջ�ɹ���ջβԪ����%d\n", em);
				pz = howMany(stk1);
				printf("\t\tջ����%d�����ݣ���������0������", pz);
				break;
			case 8:
				assign(stk1, *stk2);
				printf("���Ƴɹ�\n");
				break;
			case 9:
				print(stk1);
				break;
			case 10:
				destroyPOSTK(stk1);
				printf("\t\t���ٳɹ�\n");
				break;
			case 0:
				goto et;
		}
		getchar();
	}
et:
	return 0;
}




