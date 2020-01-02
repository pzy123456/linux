#include <stdio.h>

void f(int* p,int* q)
{
	*p = 1;
	*q = 2;
}
int main()
{
	int a = 3,b = 5;
	f(&a,&b);
	printf("%d,%d\n",a,b);
	return 0;
}
