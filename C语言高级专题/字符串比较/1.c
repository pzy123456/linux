#include <stdio.h>

int main(void)
{
	char a[] = "hello";
	char b[] = "hello";
	printf("0x%x\n",a);
	printf("%c\n",a[0]); 
	printf("0x%x\n",b);
	printf("%c\n",b[0]); 
	/*����ȣ���Ϊջ�Ӹ���͵�ַ����*/ 
	if(a == b)
	{
		printf("yes\n");
	}
	else{
		printf("no\n");
	}
	return 0;
} 
