#include <stdio.h>


/*
	a,&a,&a[0]������
	a,&a[0]����������Ԫ�ص��׵�ַ������������int * 
	&a������������׵�ַ,����������int (*)[5] 
	 
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
