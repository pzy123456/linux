#include <stdio.h>

int test(int x,int y)
{
	printf("x = %d,y = %d\n",x,y);
	return 0;
}
/*函数指针的声明*/
typedef int (*fun)(int ,int );
int main(void)
{
	/*函数指针的定义f1，指向test的地址*/
	fun f1 = test;
	f1(3,4);
	(*f1)(5,6);
	return 0;
} 
