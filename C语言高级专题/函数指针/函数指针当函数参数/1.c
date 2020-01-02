#include <stdio.h>


//fun_t是函数指针 
//该函数指针fun_t指向一个带两个int类型的形参，int类型的返回值的函数
//typedef对int (*)(int,int)进行重命名（封装）为fun_t 
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

//根据函数指针变量operation指向不同的运算函数
//可实现加法运算，减法运算，乘法运算，除法运算 
int calucate(int a,int b,fun_t operation)
{
	return operation(a,b);
} 

int main(void)
{
	int result;
	int a = 192,b = 48;
	
	/*两个数相加*/ 
	result = calucate(a,b,add);
	printf("%d+%d=%d\n",a,b,result);
	
	/*两个数相减*/ 
	result = calucate(a,b,sub);
	printf("%d-%d=%d\n",a,b,result);
		
	/*两个数相乘*/ 
	result = calucate(a,b,mul);
	printf("%d*%d=%d\n",a,b,result);
		
	/*两个数相除*/ 
	result = calucate(a,b,div); 
	printf("%d/%d=%d\n",a,b,result);
	return 0;
} 
