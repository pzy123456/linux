#include <stdio.h>

void f(int **q)
{
	int i = 5;
	*q = &i; //p = &i;
}
int main()
{
	int *p;
	f(&p);
	printf("%d\n",*p);//语法虽然没错，但是f()使用完i的值被释放
	return 0;
}