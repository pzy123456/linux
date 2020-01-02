#include <stdio.h>
#include <stdlib.h>

struct node{
	struct node *pNext;
	int data;
};
struct node* creat_node(int data)
{
	/*创建头结点*/ 
	struct node *pHead = (struct node *)malloc(sizeof(struct node));
	if(NULL == pHead)
	{
		printf("创建失败\n");
		return -1;
	}
	pHead->data = data;
	pHead->pNext = NULL;
	
	return pHead; 
}
void insert_node(struct node *pH,struct node* new)
{
	/*让pH有明确的地址*/ 
	struct node *p = pH;
	/*头结点遍历整个链表*/ 
	while( NULL != p->pNext)
	{
		p = p->pNext; 
	}
	/*插入新节点,赋予新节点的地址*/ 
	p->pNext = new;
	
}
int main(void)///
{
	struct node *pHead = creat_node(1);
	insert_node(pHead,creat_node(2));
	insert_node(pHead,creat_node(3));
	insert_node(pHead,creat_node(4));
	insert_node(pHead,creat_node(5));
	
	printf("%d\n",pHead->data);
	printf("%d\n",pHead->pNext->data);
	printf("%d\n",pHead->pNext->pNext->data);
	printf("%d\n",pHead->pNext->pNext->pNext->data);
	return 0;
} 
