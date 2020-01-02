#include <stdio.h>

int main(void)
{
	char *a = "hello1";
	char *b = "52341";
	*a = *b;
	printf("%s",a);
	return 0;
} 
