#include <stdio.h>

/*双链表的最小结构*/ 
struct node{
	int data;          //有效数据 
	struct node *pPrev;//前向指针，指向前一个节点
	struct node *pNext;//后面指针，指向后一个节点 
};

struct node *creat_node(int data)
{
	//头节点 
	struct node *p = (struct node *)malloc(sizeof(struct node));
	if(NULL == p)
	{
		printf("链表产生错误\n");
		return NULL; 
	} 
	p->data = data;
	p->pNext = NULL;
	p->pPrev = NULL;
	return p;
} 

int main(void)
{
	//头指针 
	struct node *pHeader = creat_node(0);
	return 0;
}
