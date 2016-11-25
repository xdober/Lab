/*
输入一个正整数 m(m<10000),输出组成该整数的各位数字和,例如输入 256,输出 13(即 2+5+6)
输入: 第一行为正整数 N,表示输入 N 组数据。接下来每组输入 1 个正整数。
输出:输出每组输入对应的一个计算结果。输出结果占 4 位,右对齐,并以换行符 (\n) 结束。
*/
#include<stdio.h>
int main()
{
	int a,i,n,x,sum=0;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&x);
		a=x/1000;
		sum+=a;
		a=(x%1000)/100;
		sum+=a;
		a=(x%100)/10;
		sum+=a;
		a=x%10;
		sum+=a;
		printf("%4d\n",sum);
		sum=0;
	}
	return 0;
}