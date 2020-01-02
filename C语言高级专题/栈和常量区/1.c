#include <stdio.h>

/*
	return 返回指向栈内存指针 
*/ 
char *GetStr(void)
{
	//char p[] = "hello world";/*保存在栈中,退出函数时，栈内存释放销毁，p指针指向未知值*/
	char *p = "hello world";/*p保存在栈中，hello world保存在常量区*/ 
	return p;
}
/*
	为什么一个是栈中，一个在静态区 
	因为指针变量是编译器开辟的空间，而并没有给hello world分配空间，所以在静态区
	因为字符数组是在栈开辟的空间，空间未知，编译器会开辟出足够大的栈空间存储，hello world内容填进去所以hello world是栈中 
*/
int main(void)
{
	char *p = NULL;
	p = GetStr();
	printf("%s",p); 
	return 0;
} 
