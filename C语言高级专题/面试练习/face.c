#include <stdio.h>

int main(void)
{
	int a[5] = {1,2,3,4,5};
	int *ptr1 = (int *)(&a+1); 
	//int *ptr2 = (int *)((int)a+1);/*����д������&a[0]+1*/ 
	int *ptr2 = (int *)(a+1);/*����д������&a[0]+sizeof(int)*/ 
	printf("%x,%x\n",ptr1[-1],*ptr2);
	return 0;
} 
