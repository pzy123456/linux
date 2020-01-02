#include <stdio.h>
#include <malloc.h>

struct student
{
	char name[20];
	float sorce;
	int age;
};
int main()
{
	struct student t,*pstu;
	int len,i,j;
	printf("多少个成员：\n");
	printf("len = ");
	scanf("%d",&len);
	pstu = (struct student *)malloc(len * sizeof(struct student));

	//输入
	for(i=0;i<len;i++)
	{
		printf("第%d个学生\n",i+1);
		printf("学生名字：");
		scanf("%s",pstu[i].name);
		printf("\n");

		printf("学生年龄: ");
		scanf("%d",&pstu[i].age);
		printf("\n");

		printf("学生分数: ");
		scanf("%f",&pstu[i].sorce);
		printf("\n");
	}

	//冒泡排序
	for(i=0;i<len-1;i++)
	{
		for(j=1;j<len-i-1;j++)
		{
			if(pstu[j].sorce < pstu[j+1].sorce)
			{
				t = pstu[j];
				pstu[j] = pstu[j+1];
				pstu[j] = t;
			}
		}
	}

	//输出
	for(i=0;i<len;i++)
	{
		
		printf("%s\n",pstu[i].name);
		printf("%d\n",pstu[i].age);
		printf("%f\n",pstu[i].sorce);
	}
	return 0;
}