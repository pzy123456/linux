#include <stdio.h>
#include <malloc.h>

int main()
{
	int a[5];
	int *pArr;
	int len;
	int i;
	printf("请你输入你要存放的个数：");
	scanf("%d",&len);
	pArr = (int *)malloc(4*len);//等同于int pArr[len]
	//对一维数组进行操作，如对一维数组进行赋值
	for(i=0;i<len;i++)
	{
		scanf("%d",&pArr[i]);	
	}
	//对一维数组进行输出
	for(i=0;i<len;i++)
	{
		printf("%d\n",pArr[i]);
	}
	free(pArr);
	return 0;
}