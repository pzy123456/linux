#include <stdio.h>

int main()
{
	int i = 5;
	int *p = &i;
	int **q = &p;
	int ***r = &q;

	//r = &p; error��Ϊ��r��int ***���ͣ�rֻ�ܴ��int **���ͱ�����ַ
	printf("i = %d\n",***r);
	return 0;
}          