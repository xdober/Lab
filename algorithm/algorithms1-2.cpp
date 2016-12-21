#include <stdio.h>
#include <math.h>
#define r 3
double maxd = 2 * log(20.0)/log(2.0);
int max = (int)maxd;
int ary[20] = {150,30,60,70,40,90,80,20,10,00,50,110,130,120,140,160,170,190,180,100};

void interchange(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
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

void insertionsort(int *A, int m, int p) {
	int tmp = p-m+1, j, item, i=0;
	for(j = 1;j < tmp;j++) {
		item = A[m+j];
		i = j-1;
		while(item<A[m+i]){
			A[m+i+1] = A[m+i];
			i = i - 1;
		}
		A[i+1] = item;
	}
}

int  select2(int *A, int m, int p, int k) {
	int n, i, j;
	if(p-m+1 <= r) {
		insertionsort(A,m,p);
		return m+k-1;
	}
	while(1){
		n = p-m+1;
		int tmp=floor(n/r);
		for(i=1;i<tmp;i++) {
			insertionsort(A,m+(i-1)*r,m+i*r-1);
			interchange(&A[m+i-1],&A[(int)(m+(i-1)*r+floor(r/2)-1)]);
		}
		j = select2(A,m,m+floor(n/r)-1,ceil(floor(n/r)/2));
		interchange(&A[m],&A[p]);
		j = p+1;
		partition(m,&j);
		if(j-m+1 == k){
			return j;
		}
		else if(j-m+1>k){
			p = j-1;
		}
		else{
			k = k-(j-m+1);
			m = j+1;
		}
	}
}

int main(){
	int val;
/*	insertionsort(ary,0,19);
	for (int i = 0; i < 20; ++i)
	{
		printf("%d ",ary[i] );
	}*/
	val = select2(ary,0,19,7); printf("%d\n", ary[val]);
		for (int i = 0; i < 20; ++i)
		{
			printf("%d ",ary[i] );
		}
	return 0;
}
