#include <stdio.h>

int main(void)
{
	int a[10],i,j,k;
	for(i=0;i<10;i++)
	{
		scanf("%d",&a[i]);
	} 
	for(i=0;i<9;i++)/*һ��9��*/
	{
		for(j=0;j<9-i;j++)/*����һ����һ�ˣ�������һ��*/ 
		{
			if(a[j]>a[j+1])
			{
				k = a[j];
				a[j] = a[j+1];
				a[j+1] = k;
			}
		}
	}
	for(i=0;i<10;i++)
	{
		printf("%d\n",a[i]);
	}
	return 0;
} 
