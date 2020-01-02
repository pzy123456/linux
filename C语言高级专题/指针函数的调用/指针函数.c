#include <stdio.h>
#include <stdlib.h>

/*先定义一个结构体*/ 
typedef struct Data{
	int a;
	int b;
}Data; 
/*指针函数*/
Data *fun(int a,int b)
{
	/*再定义一个结构体指针类型变量，动态申请内存*/
	Data *data = (Data *)malloc(sizeof(Data));
	/*为结构体变量进行赋值*/
	data->a = a; 
	data->b = b;
	/*指针函数返回的地址，这里返回的结构体指针变量的地址*/
	return data;
} 
int main(void)
{
	Data *mydata = fun(2,3);
	printf("mydata->a = %d,mydata->b = %d\n",mydata->a,mydata->b);
	return 0;
}
