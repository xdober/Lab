/*输入一串字符(字符数小于 70)和正整数 k,将其中的字母加密,并输出加密后的
字符串,其它字符保持不变。 加密思想:把每个小写字母替换成它之后的第 k 个
字母,即用它后面的第 k 个字母代替,例如,k 取 2 时,b 替换成 d,y 替换成 a,T
替换成 V。
要求:
输入: 第一行为正整数 N,表示输入 N 组数据。接下来每行分别输入一串字符和一个正整数。
输出:加密后的字符串, 并以换行符 (\n) 结束。
样例输入:
2
bN1cyz 3
year2014raey 1
样例输出:
eQ1fbc
zfbs2014sbfz
*/
#include<stdio.h>
int main()
{
	int i,j=0,n,k=0,m;
	char c[73];
	scanf("%d",&n);
	getchar();
	for(i=0;i<n;i++)
	{
		gets(c);
		for(j=0;j<72;j++)
		{
			if(c[j]=' ')
			{
				c[j]='\0';
				j++;
			}
		}
				for(m=j;c[m]>='0'&&c[m]<'9';)
				{
					m++;
				}
				while(1)
				{
					k+=c[m-1]-'0';
					if(j-1==m)break;
					k+=(c[m-2]-'0')*10;
					if(j-1==m-1)break;
					k+=(c[m-3]-'0')*100;
					if(j-1==m-2)break;
					k+=(c[m-4]-'0')*1000;
					if(j-1==m-3)break;
				}
		for(j=0;c[j]!='\0';j++)
		{
			if(c[j]>='0'&&c[j]<='9')
			;
			else if((c[j]>='a'&&c[j]<='z'-k)||(c[j]>='A'&&c[j]<='Z'-k))
			{
				c[j]+=k;
			}
			else c[j]=c[j]+k-26;
		}
		printf("%s\n",c);
	}
	return 0;
}
