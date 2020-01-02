#include <stdio.h>

/*
	技巧就是看+1就是相当于偏移4个字节 
*/ 

int main(void)
{
	int a[10];
	printf("0x%x\n",&a[1]);
	printf("0x%x\n",a+sizeof(int));
	printf("0x%x\n",a+1);
	printf("0x%x\n",&a[0]+1);
	printf("0x%x\n",(int *)&a+1);
	return 0;
} 
