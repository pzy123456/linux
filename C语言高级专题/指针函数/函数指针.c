#include <stdio.h>
#include <stdlib.h>

int add(int x,int y)
{
	return (x + y);
}
int sub(int a,int b)
{
	return (a - b);
}

/*函数指针的地址fun*/
int (*fun)(int x,int y);
 
int main(void)
{
	fun = sub;
	printf("the (*fun)(2,3)is %d\n",(*fun)(2,3));
	printf("the (*fun)(4,3)is %d\n",(*fun)(4,3));
	return 0;	
}
 
