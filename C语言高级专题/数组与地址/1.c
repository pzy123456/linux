#include <stdio.h>

/*
	���ɾ��ǿ�+1�����൱��ƫ��4���ֽ� 
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
