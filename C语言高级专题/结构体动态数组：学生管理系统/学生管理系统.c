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
	printf("���ٸ���Ա��\n");
	printf("len = ");
	scanf("%d",&len);
	pstu = (struct student *)malloc(len * sizeof(struct student));

	//����
	for(i=0;i<len;i++)
	{
		printf("��%d��ѧ��\n",i+1);
		printf("ѧ�����֣�");
		scanf("%s",pstu[i].name);
		printf("\n");

		printf("ѧ������: ");
		scanf("%d",&pstu[i].age);
		printf("\n");

		printf("ѧ������: ");
		scanf("%f",&pstu[i].sorce);
		printf("\n");
	}

	//ð������
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

	//���
	for(i=0;i<len;i++)
	{
		
		printf("%s\n",pstu[i].name);
		printf("%d\n",pstu[i].age);
		printf("%f\n",pstu[i].sorce);
	}
	return 0;
}