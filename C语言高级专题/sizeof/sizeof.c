#include <stdio.h>

int main(void)
{
	char *str = "hello";
	printf("%d\n",sizeof(str));/*Ҳ��һ��ָ��*/
	printf("%d\n",sizeof(*str));
	printf("%d\n",sizeof(char *));/*ָ��4���ֽ�*/
	printf("%c\n",*str);/*h*/
	printf("%s\n",str);/*hello*/
	return 0;
} 
