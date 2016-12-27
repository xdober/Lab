//#include <stdio.h>
#include <iostream>
#include <math.h>
#define N 4
using namespace std;
int a[100], count;
int check_2 (int a[ ],int n)
{
    for(int i=1;i<=n-1;i++)
    {
        if((abs(a[i]-a[n])==n-i)||(a[i]==a[n]))
            return 0;
    }
    return 1;
}
void backtrack(int k)
{
    if (k>N)//找到解
    {
        for(int i=1;i<=N;i++)
        {
            cout<<a[i]<<" ";
        }
        cout<<endl;
        count++;
    }
    else
    {
        for (int i = 1;i <=N; i++)
        {
            a[k] = i;
            if (check_2(a,k) == 1)
            {backtrack(k+1);}
        }
    }

}
int main()
{
    count=0;
    backtrack(1);
    cout<<count<<endl;
		return 0;
}
