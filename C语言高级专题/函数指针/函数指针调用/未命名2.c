#include <stdio.h>

int test(int x,int y)
{
	printf("x = %d,y = %d\n",x,y);
	return 0;
}
/*����ָ�������*/
typedef int (*fun)(int ,int );
int main(void)
{
	/*����ָ��Ķ���f1��ָ��test�ĵ�ַ*/
	fun f1 = test;
	f1(3,4);
	(*f1)(5,6);
	return 0;
} 
