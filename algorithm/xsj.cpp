#include<stdio.h>
#include<math.h>
#define NUM 11
int A[NUM] = {10,20,5,2,55,40,50,30,60,100,80};
int r;
void PARTITION(int m,int *p)
{
	int i,v;
	int temp;
	v = A[m];
	i = m;
	while(1)
	{
		do{
			i = i + 1;
		}
		while(A[i] < v);
		do{
			*p = *p - 1;
		}
		while(A[*p] > v);
		if(i < *p)
		{
			temp = A[*p];
			A[*p] = A[i];
			A[i] = temp;
		}
		else break;
	}
	A[m] = A[*p];
	A[*p] = v;
}
void INSERTIONSORT(int A[],int m,int p)
{
	int j,item,i;
	for(j = m + 1;j <= p;j++)
	{
		item = A[j];
		i = j - 1;
		while((item < A[i]) && (i>= m)) //i减小但必须大于m
		{
			A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = item;
	}
}
int SELECT2(int A[],int m,int p,int k)
{
	int n,i,j;
	double nm;
	int num1,num2,num3;//num1保存n/r向下取整的值,num2保存r/2向下取整的值 ,num3保存num2/2向上取整的值
	int temp;//中间变量
	if(p - m + 1 <= r)
	{
		INSERTIONSORT(A,m,p);
		return (m + k - 1);
	}
	while(1)
	{
		n = p - m + 1;
		nm = n/r;
		num1 = floor(nm);
		nm = r/2;
		num2 = floor(nm);
		nm = num2/2;
		num3 = ceil(num3);
		for(i = 1;i < num1;i++)
		{
			INSERTIONSORT(A,m + (i - 1) * r,m + i * r -1);
			temp = A[m + i - 1];
			A[m + i - 1] = A[m + (i - 1) * r + num2 - 1];
			A[m + (i - 1) * r + num2 - 1] = temp;
		}
		j = SELECT2(A,m,m + num2 -1,num3);
		temp = A[m];
		A[m] = A[p];
		A[p] = temp;
		j = p + 1;
		PARTITION(m,&j);
		if((j - m + 1)== k) return j;
		else if((j - m + 1) > k) p = j - 1;
		else
		{
			k = k - (j - m + 1);
			m = j + 1;
		}
	}
}
int main()
{
	int i,k,m,p;
/*	printf("请输入第几小元素k的值：\n");
	scanf("%d",&k);*/
	printf("请输入分成的每个组的大小r的值：\n");
	scanf("%d",&r);
	/*printf("请输入区间m和p的值：\n");
	scanf("%d %d",&m,&p);*/
	i = SELECT2(A,1,9,2);
	printf("%d  \n",A[i]);
	return 0;
}
