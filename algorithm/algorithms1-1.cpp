#include <stdio.h>
#include <math.h>
#define NUM 20
void interchange(int *a, int *b);
void partition(int ,int *);
void quicksort2(int , int );
void quicksort(int *val, int num);
double maxd = 2 * log(NUM)/log(2.0);
int max = (int)maxd;
int ary[NUM] = {150,30,60,70,40,90,80,20,10,00,50,110,130,120,140,160,170,190,180,200};
int main(){
	int a = 0,b = 19;
	quicksort2(a,b);
	for (int i = 0; i < NUM; ++i)
	{
		printf("%d ",ary[i] );
	}
	return 0;	
}
void quicksort2(int p, int q) {
	int stack[max];
	int top = 0, j;
	do{
		while(p < q){
			j = (q)+1;
			partition(p,&j);
			if(j-p<q-j){
				stack[top+1] = j+1;
				stack[top+2] = q;
				q = j-1;
			}
			else {
				stack[top+1] = p;
				stack[top+2] = j-1;
				p = j+1;
			}
			top = top+2;
		}
		if(!top) return;
		q = stack[top];
		p = stack[top-1];
		top = top-2;
	}while(1);
}
void partition(int m, int *p) {
	int i, v;
	v = ary[m];
	i = m;
	do {
		do {i = i + 1;} while(ary[i] < v);
		do {*p = *p - 1;} while (ary[*p] > v);
		if(i < *p) {
			interchange(&ary[i], &ary[*p]);
		}
		else break;
	} while(1);
	ary[m]=ary[*p];
	ary[*p] = v;
}
void interchange(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}