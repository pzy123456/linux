
#include <stdio.h>

int main()
{
	int arg[] = {4,5,6,7,8};
	int *ptr = arg;
	*(arg++) += 123;
	printf("%d\n",arg);
	return 0;
}

