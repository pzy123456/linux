#include <stdio.h>

int test(int x,int y)
{
//	printf("x = %d,y = %d\n",x,y);
	return 0;
}
typedef int (*fun)(int ,int);
 
int main(void)
{
	fun f1 = test;
	fun f2 = &test;
	printf("%p\n",f1);
	printf("%p\n",f2);
	return 0;
}

