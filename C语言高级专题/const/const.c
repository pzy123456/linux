#include <stdio.h>
  
/*
	const��*�ĺ��棬p���ܸ�����һ��ֵ
	const��*��ǰ��,p���Ը�����һ��ֵ 
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

