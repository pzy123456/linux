#include <stdio.h>


//fun_t�Ǻ���ָ�� 
//�ú���ָ��fun_tָ��һ��������int���͵��βΣ�int���͵ķ���ֵ�ĺ���
//typedef��int (*)(int,int)��������������װ��Ϊfun_t 
typedef  int (*fun_t)(int ,int );

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

//���ݺ���ָ�����operationָ��ͬ�����㺯��
//��ʵ�ּӷ����㣬�������㣬�˷����㣬�������� 
int calucate(int a,int b,fun_t operation)
{
	return operation(a,b);
} 

int main(void)
{
	int result;
	int a = 192,b = 48;
	
	/*���������*/ 
	result = calucate(a,b,add);
	printf("%d+%d=%d\n",a,b,result);
	
	/*���������*/ 
	result = calucate(a,b,sub);
	printf("%d-%d=%d\n",a,b,result);
		
	/*���������*/ 
	result = calucate(a,b,mul);
	printf("%d*%d=%d\n",a,b,result);
		
	/*���������*/ 
	result = calucate(a,b,div); 
	printf("%d/%d=%d\n",a,b,result);
	return 0;
} 
