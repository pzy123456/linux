#include <stdio.h>
#include <string.h>

void getMemory(char *p)
{
	/*char *p = str*/
	p = (char *)malloc(100);
	strcpy(p,"hello world");
	printf("p:%s\n",p); 
}
int main(void)
{
	printf("Enter main...\n");
	char *str = "pzy";
	printf("str:%s\n",str);
	/*它传递的是str的副本，不是它本身，所以说既然传入的是副本，
	在getmemory里面操作的代码，也就是对这个副本进行操作幂函数调用结束
	也就销毁了*/ 
	getMemory(str);/*不加取地址代表传入char* 看做是普通变量*/
					/*加入取地址代表传入char** 的意思是指向地址上的内容*/ 
	printf("%s\n",str);
	if(NULL != str)
	{
		free(str);
	} 
	return 0;
} 
