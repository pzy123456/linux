#include <stdio.h>

/*
	����ָ����Ϊ�ṹ���Ա 
*/
typedef int (*fun_t)(int ,int ); 

struct Source
{
	int a;
	int b;
	fun_t operation;
};

int add(int a,int b)
{
	return a+b;
}

int sub(int a,int b)
{
	return a-b;
}

int mul(int a,int b)
{
	return a*b;
}

int div(int a,int b)
{
	return a/b;
}

int main(void)
{
	struct Source std;
	int result; 
	std.a = 100;
	std.b = 4;
	/*����ָ��Ľṹ���Ա�ĳ�ʼ��ָ�������*/ 
	std.operation = add; 
	result = std.operation(std.a,std.b);
	printf("%d+%d=%d\n",std.a,std.b,result);
	
	std.operation = sub; 
	result = std.operation(std.a,std.b);
	printf("%d-%d=%d\n",std.a,std.b,result);
	
	std.operation = mul; 
	result = std.operation(std.a,std.b);
	printf("%d*%d=%d\n",std.a,std.b,result);
	
	std.operation = div; 
	result = std.operation(std.a,std.b);
	printf("%d/%d=%d\n",std.a,std.b,result);
	return 0;
} 
