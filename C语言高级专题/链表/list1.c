#include <stdio.h>
#include <stdlib.h>

/*
	ʵ�ֵ�Ŀ������ʾһ������ 
*/ 
struct node{
	struct node *pNext;
	int data;
};
int main(void)
{
	struct node *pHead = NULL;
	struct node *p = (struct node *)malloc(sizeof(struct node));
	
	if(NULL == p)
	{
		printf("��������ʧ��\n");
		return -1;
	}
	p->data = 5;
	p->pNext = NULL;
	
	pHead = p;
	struct node *p1 = (struct node *)malloc(sizeof(struct node));
	if(NULL == p1)
	{
		printf("��������ʧ��\n");
		return -1;
	}
	p1->data = 2;
	p1->pNext = NULL;
	
	p->pNext = p1;
	
	printf("%d\n",p->data);
	printf("%d\n",p->pNext->data);
	return 0;
} 
