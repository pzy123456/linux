#include <stdio.h>
#include <stdlib.h>

/*
	实现目的是插入节点,并且遍历 
*/
struct node{
	struct node *pNext;
	int data;
}; 

struct node *creat_node(int data)
{
	/*头结点*/ 
	struct node *pH = (struct node *)malloc(sizeof(struct node));
	if(NULL == pH)
	{
		printf("创建失败\n");
		return -1;
	}
	pH->data = data;
	pH->pNext = NULL;
	return pH;
}

void insert_tail(struct node *pH,struct node *new)
{
	int cnt = 0;
	struct node *p = pH;
	while(NULL != p->pNext)
	{
		p = p->pNext;
		cnt++; 
	}
	p->pNext = new;
	pH->data = cnt+1; 
} 
void insert_head(struct node *pH,struct node *new)
{
	/*新节点指向头结点的下一个指针*/ 
	new->pNext = pH->pNext;
	/*头指针的指针域指向新节点*/ 
	pH->pNext = new;
	/*头指针记录节点个数加1*/
	pH->data += 1; 
}
void travel_list(struct node *pH)
{
	//struct node *p = pH;之所以不这样遍历是因为头结点的数据域不算链表元素 
	struct node *p = pH->pNext; 
	/*遍历链表，确认链表指针域是不是为空,头结点不算*/ 
	while(NULL != p->pNext)
	{
		printf("%d\n",p->data);
		p = p->pNext;
	}
	printf("%d\n",p->data); 
}
int main(void)
{
	struct node *pHead = creat_node(0);
	insert_head(pHead,creat_node(1));
	insert_head(pHead,creat_node(2));
	insert_head(pHead,creat_node(3));
	
	travel_list(pHead); 
	//printf("head node data : %d\n",pHead->data);
	//printf(" node1 data : %d\n",pHead->pNext->data);
	//printf("node2 data : %d\n",pHead->pNext->pNext->data);
	 //printf("node3 data : %d\n",pHead->pNext->pNext->pNext->data);
	//return 0;
}
