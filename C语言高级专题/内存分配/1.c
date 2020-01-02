#include <stdio.h>

void *test(void)
{
	int a = 4;
	printf("&a = %p\n",&a);
	return &a;
} 

int main(void)
{
	int *p = NULL;
	p = test();
	printf("%d\n",*p);//在这里打印值是4，说明栈内存是脏的，也就是最原始的值 
	printf("%p\n",p);
	//printf("%d\n",*p);//在这里打印值是乱码 
	return 0;
} 
