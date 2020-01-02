#include <stdio.h>

int main()
{
	int i = 5;
	int *p = &i;
	int **q = &p;
	int ***r = &q;

	//r = &p; error因为是r是int ***类型，r只能存放int **类型变量地址
	printf("i = %d\n",***r);
	return 0;
}          