#include <stdio.h>
#include <stdlib.h>

/*
	ʵ��Ŀ���ǲ���ڵ�,���ұ��� 
*/
struct node{
	struct node *pNext;
	int data;
}; 

struct node *creat_node(int data)
{
	/*ͷ���*/ 
	struct node *pH = (struct node *)malloc(sizeof(struct node));
	if(NULL == pH)
	{
		printf("����ʧ��\n");
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
	/*�½ڵ�ָ��ͷ������һ��ָ��*/ 
	new->pNext = pH->pNext;
	/*ͷָ���ָ����ָ���½ڵ�*/ 
	pH->pNext = new;
	/*ͷָ���¼�ڵ������1*/
	pH->data += 1; 
}
void travel_list(struct node *pH)
{
	//struct node *p = pH;֮���Բ�������������Ϊͷ����������������Ԫ�� 
	struct node *p = pH->pNext; 
	/*��������ȷ������ָ�����ǲ���Ϊ��,ͷ��㲻��*/ 
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
