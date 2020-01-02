#include <stdio.h>
  
/*
	const在*的后面，p不能赋予另一个值
	const在*的前面,p可以赋予另一个值 
*/

int main(void)
{
	int a = 1;
	int b = 2;
	const int * p = &a;
	//int * const p = &a;
	p = &b;
	printf("%d\n",*p);
	return 0;
} 

