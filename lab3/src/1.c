int b;
int main()
{
	int n;
	int a=0;
	b=3;
	if (n > 0) a = 1;
	else if (n < 0) a = 2 * b;
		else a = b + 3;
	if(a==b || b!=n)
		b = 5;
	else
		b = b + 2;
	return 0;
}
