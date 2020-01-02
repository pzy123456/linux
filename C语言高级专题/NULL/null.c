#include <stdio.h>
#include <malloc.h>
int main()
{
	int *p = (int *)malloc(sizeof(int));
	
	free(p);
	//p = NULL;
	*p = 5;
	printf("%d\n",*p);
}