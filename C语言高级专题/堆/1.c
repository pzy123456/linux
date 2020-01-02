#include <stdio.h>

int main(void)
{
	int *p = (int *)malloc(20);
	if(NULL == p)
	{
		printf("malloc error\n");
		return -1; 
	} 
	*(p+0) = 1;
	*(p+1) = 2;
	printf("*(p+0) = %d\n",*(p+0));
	printf("*(p+1) = %d\n",*(p+1));
	
	free(p);
	//p = NULL;
	*(p+222) = 133;
	*(p+223) = 222;
	printf("*(p+222) = %d\n",*(p+222));
	printf("*(p+223) = %d\n",*(p+223));
	return 0;
} 
