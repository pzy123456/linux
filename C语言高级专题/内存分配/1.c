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
	printf("%d\n",*p);//�������ӡֵ��4��˵��ջ�ڴ�����ģ�Ҳ������ԭʼ��ֵ 
	printf("%p\n",p);
	//printf("%d\n",*p);//�������ӡֵ������ 
	return 0;
} 
