#include <stdio.h>
#include <stdlib.h>
 
/*
	�������ݲ���һ��Ԫ�� 
*/
struct node{
	int data;
	struct node *pPrev;
	struct node *pNext;
};

struct node *creat_list(int data)
{
	/*����ͷ�ڵ�*/ 
	struct node *pH = (struct node *)malloc(sizeof(struct node));
	if(NULL == pH)
	{
		printf("malloc error\n");
		return -1;
	} 
	p->data = data;
	p->pPrev = NULL;
	p->pNext = NULL;
	return pH;
}

void insert_head(struct node *pHead,struct node *new)
{
	
}
int main(void)
{
	struct node *pHeader = creat_list(0);
	insert_head(pHeader,creat_list(1));
	insert_head(pHeader,creat_list(2));
	insert_head(pHeader,creat_list(3));
	return 0;
}
 
