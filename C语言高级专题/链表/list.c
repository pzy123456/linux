#include <stdio.h>
#include <stdlib.h>
struct node{
	struct node *pNext;//指针域
	int data;//数据域 
};

int main(void)
{
	struct node *pHead = NULL;/*头指针*/
	/*创建节点*/ 
	struct node *p1 = (struct node *)malloc(sizeof(struct node));
	if(NULL == p1)
	{
		printf("分配内存失败\n");
		exit(-1);
	}
	p1->data = 1;
	p1->pNext = NULL;
	/*结合节点和头结点关联起来*/
	pHead = p1;
	
	/*创建节点*/ 
	struct node *p2 = (struct node *)malloc(sizeof(struct node));
	if(NULL == p2)
	{
		printf("分配内存失败\n");
		exit(-1);
	}
	p2->data = 2;
	p2->pNext = NULL;
	/*结合第二节点和第一节点*/
	p1->pNext = p2; 
	
	/*创建节点*/ 
	struct node *p3 = (struct node *)malloc(sizeof(struct node));
	if(NULL == p3)
	{
		printf("分配内存失败\n");
		exit(-1);
	}
	p3->data = 3;
	p3->pNext = NULL;
	/*结合第三个节点和第二个结点*/
	p2 = p3;
	
	printf("node1 data:%d\n",pHead->data); 
	printf("node1 data:%d\n",pHead->data);
	printf("node1 data:%d\n",pHead->data);
	printf("node1 data:%d\n",pHead->data);
	printf("node1 data:%d\n",pHead->data);
	
	return 0;
} 
