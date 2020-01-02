#include <stdio.h>


/*
	a,&a,&a[0]的区别
	a,&a[0]都是数组首元素的首地址，所以类型是int * 
	&a是整个数组的首地址,所以类型是int (*)[5] 
	 
*/ 
int main(void)
{
	int a[5] = {1,2,3,4,5};
	printf("the address is 0x%x\n",a);
	printf("the address is 0x%x\n",&a[0]);
	printf("the address is 0x%x\n\n",&a);
	
	printf("the address is 0x%x\n",a+1);
	printf("the address is 0x%x\n",&a+1);
	printf("the address is 0x%x\n\n",&a[0]+1);
	
	printf("the address is 0x%x\n",a+2);
	printf("the address is 0x%x\n",&a+2);
	printf("the address is 0x%x\n",&a[0]+2);
	return 0;
} 
