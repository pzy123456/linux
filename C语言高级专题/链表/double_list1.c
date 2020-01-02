#include <stdio.h>


/*
	双链表下创建尾结点 
*/
struct node{
	int data;
	struct node *pPrev;
	struct node *pNext;
};

struct node *creat_list(int data)
{
	/*创建头结点*/ 
	struct node *pH = (struct node *)malloc(sizeof(struct node));
	if(NULL == pH)
	{
		printf("创建失败\n");
		return -1;
	}
	pH->data = data;
	pH->pPrev = NULL;
	pH->pNext = NULL; 
	return pH;
}

void insert_tail(struct node *pH,struct node *new)
{
	/*头指针需要指针需要指向明确地址*/ 
	struct node *p = pH;
	/*将链表节点遍历*/ 
	while(NULL != p->pNext)
	{
		p = p->pNext;//第一次循环走过了头结点 
	} 
	 /*循环结束后p就指向了原来的最后一个节点*/
	 /*第二个：将新节点插入到原来的尾节点的后面*/ 
	 p->pNext = new;//后面的指针关联好了，新节点的地址和前节点的next
	 new->pPrev = p->pPrev;//前向指针关联好了。新节点的prev和前节点的地址
	 
	 //前节点的prev和新节点的next指针未变动 
}
int main(void)
{
	struct node *pHeader = creat_list(0);
	insert_tail(pHeader,creat_list(1)); 
	insert_tail(pHeader,creat_list(2)); 
	insert_tail(pHeader,creat_list(3));
	
	printf("node 1 data:%d\n",pHeader->data);
	printf("node 1 data:%d\n",pHeader->pNext->data);
	printf("node 2 data:%d\n",pHeader->pNext->pNext->data);
	printf("node 3 data:%d\n",pHeader->pNext->pNext->pNext->data);
	return 0;
} 
