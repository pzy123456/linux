#include <stdio.h>
#include <malloc.h>

int main()
{
	int a[5];
	int *pArr;
	int len;
	int i;
	printf("����������Ҫ��ŵĸ�����");
	scanf("%d",&len);
	pArr = (int *)malloc(4*len);//��ͬ��int pArr[len]
	//��һά������в��������һά������и�ֵ
	for(i=0;i<len;i++)
	{
		scanf("%d",&pArr[i]);	
	}
	//��һά����������
	for(i=0;i<len;i++)
	{
		printf("%d\n",pArr[i]);
	}
	free(pArr);
	return 0;
}