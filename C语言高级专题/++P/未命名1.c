#include <stdio.h>

int main(void)
{
	int a[5] = {555,444,333,222,111};
	int *p = a;
	//printf("%d,%d\n",*p++,*p);/*ох*p,p+=1;*p*/
	//printf("%d\n",*p);
	//printf("%d\n",*++p);
	//printf("%d\n",*p);
	//printf("%d\n",(*p)++);
	printf("%d\n",++(*p));
	printf("%d\n",*p);
	//printf("%d,%d\n",*(++p),*p); 
	return 0;
} 
