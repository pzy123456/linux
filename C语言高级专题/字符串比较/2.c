#include <stdio.h>

int main(void)
{
	/*因为都指向常量区的同一个字符串*/ 
	/*和栈没关系*/
	char *a = "hello"; 
	char *b = "hello"; 
	printf("0x%x\n",a);
	printf("0x%x\n",b);
	printf("%c\n",*a);
	printf("%c\n",*b);
	if(a == b)
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}
	return 0;
} 
