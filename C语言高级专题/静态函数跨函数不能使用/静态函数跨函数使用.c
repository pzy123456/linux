#include <stdio.h>

void f(int **q)
{
	int i = 5;
	*q = &i; //p = &i;
}
int main()
{
	int *p;
	f(&p);
	printf("%d\n",*p);//�﷨��Ȼû������f()ʹ����i��ֵ���ͷ�
	return 0;
}