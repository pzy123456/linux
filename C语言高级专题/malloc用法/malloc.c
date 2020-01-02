#include <stdio.h>
#include <stdlib.h>

void f(int* p)
{
	//*q = 200；因为函数内部没有定义*q
	//p = 200;	因为200是整型常数不是整型地址
	*p = 200;	//因为p是地址，*p是4个字节，然后将200存入这4个字节
	//free(p);//把开辟4个字节地址空间释放掉
}
int main()
{
	int* q = (int *)malloc(sizeof(int));
	*q = 10;
	printf("%d\n",*q);
	f(q);
	printf("%d\n",*q);//*p代表所指向的4个字节，现在释放掉了，就没有访问权限了
	return 0;
}