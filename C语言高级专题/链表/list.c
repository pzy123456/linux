#include <stdio.h>
#include <stdlib.h>
struct node{
	struct node *pNext;//ָ����
	int data;//������ 
};

int main(void)
{
	struct node *pHead = NULL;/*ͷָ��*/
	/*�����ڵ�*/ 
	struct node *p1 = (struct node *)malloc(sizeof(struct node));
	if(NULL == p1)
	{
		printf("�����ڴ�ʧ��\n");
		exit(-1);
	}
	p1->data = 1;
	p1->pNext = NULL;
	/*��Ͻڵ��ͷ����������*/
	pHead = p1;
	
	/*�����ڵ�*/ 
	struct node *p2 = (struct node *)malloc(sizeof(struct node));
	if(NULL == p2)
	{
		printf("�����ڴ�ʧ��\n");
		exit(-1);
	}
	p2->data = 2;
	p2->pNext = NULL;
	/*��ϵڶ��ڵ�͵�һ�ڵ�*/
	p1->pNext = p2; 
	
	/*�����ڵ�*/ 
	struct node *p3 = (struct node *)malloc(sizeof(struct node));
	if(NULL == p3)
	{
		printf("�����ڴ�ʧ��\n");
		exit(-1);
	}
	p3->data = 3;
	p3->pNext = NULL;
	/*��ϵ������ڵ�͵ڶ������*/
	p2 = p3;
	
	printf("node1 data:%d\n",pHead->data); 
	printf("node1 data:%d\n",pHead->data);
	printf("node1 data:%d\n",pHead->data);
	printf("node1 data:%d\n",pHead->data);
	printf("node1 data:%d\n",pHead->data);
	
	return 0;
} 
