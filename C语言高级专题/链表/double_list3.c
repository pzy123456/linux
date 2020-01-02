#include <stdio.h>
#include <stdlib.h>
struct node{
	int data;
	struct node *pPrev;//前向指针，指向前一个节点 
	struct node *pNext;//后向指针，指向后一个节点 
};

struct node *creat_list(int data)
{
	struct node *pH = (struct node *)malloc(sizeof(struct node *));//创建头节点
	if(NULL == pH)
	{
		printf("malloc error\n");
		return -1;
	} 
	pH->data = data;
	pH->pNext = NULL;
	pH->pPrev = NULL;
	return pH;
}

void insert_head(struct node *pH,struct node *new)
{
	/*给新节点的next指针指向原来的第一个有效节点*/
	new->pNext = pH->pNext;
	/*原来第一个有效节点的prev指向new节点的prev*/
	pH->pNext->pPrev = new->pPrev; 
	/*将头节点赋值给new的地址*/
	pH->pNext = new; 
	/*新节点的prev指针指向头结点的地址*/ 
	new->pPrev = pH;	
}

void insert_tail(struct node *pH,struct node *new)
{
	/*给头指针一个确切的地址，避免野指针出现*/ 
	struct node *p = pH;
	/*遍历到最后一个节点*/ 
	while(NULL != p->pNext)
	{
		p = p->pNext;
	} 
	p->pNext = new;//后向指针关联好了，新节点的地址和前节点的next 
	new->pPrev = p->pPrev;//后向指针关联好了，新节点的prev和前节点的地址 
	
} 

void travel_list(struct node *pH)
{
	/*遍历链表数据，头节点不算*/ 
	struct node *p = pH->pNext;
	while(NULL != p->pNext)
	{
		printf("%d\n",p->data);
		p = p->pNext; 
	}	
	printf("%d\n",p->data);
}

int main(void)
{
	struct node *pHeader = creat_list(0);//头指针 
	
	insert_head(pHeader,creat_list(0));
	insert_head(pHeader,creat_list(1));
	insert_head(pHeader,creat_list(2));
	
	travel_list(pHeader);		
	return 0;
} 
