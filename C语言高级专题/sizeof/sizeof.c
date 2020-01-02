#include <stdio.h>

int main(void)
{
	char *str = "hello";
	printf("%d\n",sizeof(str));/*也是一个指针*/
	printf("%d\n",sizeof(*str));
	printf("%d\n",sizeof(char *));/*指针4个字节*/
	printf("%c\n",*str);/*h*/
	printf("%s\n",str);/*hello*/
	return 0;
} 
