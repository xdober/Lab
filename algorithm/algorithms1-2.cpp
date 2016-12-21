#include <stdio.h>
#include <math.h>
#define r 5
double maxd = 2 * log(20.0)/log(2.0);
int max = (int)maxd;
int ary[21] = {150,30,60,70,40,90,80,20,10,00,50,110,130,120,140,160,170,190,180,100,1000};

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

void insertionsort(int *A,int m,int p)
{
	int j,item,i;
	for(j = m + 1;j <= p;j++)
	{
		item = A[j];
		i = j - 1;
		while((item < A[i]) && (i>= m))
		{
			A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = item;
	}
}

int select2(int *A,int m,int p,int k)
{
	int n,i,j;
	double nm;
	int num1,num2,num3;//num1: n/r向下取整的值,num2: r/2向下取整的值 ,num3: num2/2向上取整的值 
	if(p - m + 1 <= r)
	{
		insertionsort(A,m,p);
		return (m + k - 1);
	}
	while(1)
	{ 
		n = p - m + 1;
		nm = n*1.0/r;
		num1 = floor(nm);
		nm = r/2.0;
		num2 = floor(nm);
		nm = num2/2.0;
		num3 = ceil(nm); 
		for(i = 1;i < num1;i++)
		{
			insertionsort(A,m + (i - 1) * r,m + i * r -1);
			interchange(&A[m + i - 1],&A[m + (i - 1) * r + num2 - 1]);
		}
		j = select2(A,m,m + num2 - 1 ,num3);
		interchange(&A[m],&A[j]);
		j = p + 1;
		partition(m,&j);
		if((j - m + 1)== k) return j;
		else if((j - m + 1) > k) p = j - 1;
		else 
		{
			k = k - (j - m + 1);
			m = j + 1;
		}
	}
}
int main(){
	int num;
	printf("source values :\n");
	for (int i = 0; i < 20; ++i)
	{
		printf("%d ", ary[i]);
	}
	printf("\n");
	for (int i = 1; i < 21; ++i)
	{
		num = select2(ary,0,20,i); 
		printf("The %2dth small value:  %d\n", i,ary[num]);
	}
	return 0;
}