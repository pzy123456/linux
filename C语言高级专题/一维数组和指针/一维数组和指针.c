#include <stdio.h>

int main()
{
	int a[5];
	int b[5];
	//a = b;//��Ϊһά��������ָ�볣�����ܸı�
	printf("%#x\n",&a[0]);
	printf("%#x\n",&b[0]);
	printf("%#x\n",a);
	printf("%#x\n",b);
	return 0;
}
/*
0x18ff34
0x18ff34
Press any key to continue
*/