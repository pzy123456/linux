#include <stdio.h>
#include <malloc.h>

void f(int **q)
{
	*q = (int *)malloc(sizeof(int));//sizeof(int)��ͬ�Ļ���ռ��ͬ���ֽ�
	//��ͬ��p = (int *)malloc(sizeof(int));
	**q = 5;//*p = 5;
}
int main()
{
	int *p;
	f(&p);
	printf("%d\n",*p);
	return 0;
}
