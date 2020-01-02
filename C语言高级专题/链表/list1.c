#include <stdio.h>
#include <stdlib.h>

/*
	实现的目的是显示一个链表 
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
		printf("创建链表失败\n");
		return -1;
	}
	p->data = 5;
	p->pNext = NULL;
	
	pHead = p;
	struct node *p1 = (struct node *)malloc(sizeof(struct node));
	if(NULL == p1)
	{
		printf("创建链表失败\n");
		return -1;
	}
	p1->data = 2;
	p1->pNext = NULL;
	
	p->pNext = p1;
	
	printf("%d\n",p->data);
	printf("%d\n",p->pNext->data);
	return 0;
} 
