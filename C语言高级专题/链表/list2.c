#include <stdio.h>
#include <stdlib.h>

struct node{
	struct node *pNext;
	int data;
};
struct node* creat_node(int data)
{
	/*����ͷ���*/ 
	struct node *pHead = (struct node *)malloc(sizeof(struct node));
	if(NULL == pHead)
	{
		printf("����ʧ��\n");
		return -1;
	}
	pHead->data = data;
	pHead->pNext = NULL;
	
	return pHead; 
}
void insert_node(struct node *pH,struct node* new)
{
	/*��pH����ȷ�ĵ�ַ*/ 
	struct node *p = pH;
	/*ͷ��������������*/ 
	while( NULL != p->pNext)
	{
		p = p->pNext; 
	}
	/*�����½ڵ�,�����½ڵ�ĵ�ַ*/ 
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
