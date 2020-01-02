#include <stdio.h>
#include <stdlib.h>
struct node{
	int data;
	struct node *pPrev;//ǰ��ָ�룬ָ��ǰһ���ڵ� 
	struct node *pNext;//����ָ�룬ָ���һ���ڵ� 
};

struct node *creat_list(int data)
{
	struct node *pH = (struct node *)malloc(sizeof(struct node *));//����ͷ�ڵ�
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
	/*���½ڵ��nextָ��ָ��ԭ���ĵ�һ����Ч�ڵ�*/
	new->pNext = pH->pNext;
	/*ԭ����һ����Ч�ڵ��prevָ��new�ڵ��prev*/
	pH->pNext->pPrev = new->pPrev; 
	/*��ͷ�ڵ㸳ֵ��new�ĵ�ַ*/
	pH->pNext = new; 
	/*�½ڵ��prevָ��ָ��ͷ���ĵ�ַ*/ 
	new->pPrev = pH;	
}

void insert_tail(struct node *pH,struct node *new)
{
	/*��ͷָ��һ��ȷ�еĵ�ַ������Ұָ�����*/ 
	struct node *p = pH;
	/*���������һ���ڵ�*/ 
	while(NULL != p->pNext)
	{
		p = p->pNext;
	} 
	p->pNext = new;//����ָ��������ˣ��½ڵ�ĵ�ַ��ǰ�ڵ��next 
	new->pPrev = p->pPrev;//����ָ��������ˣ��½ڵ��prev��ǰ�ڵ�ĵ�ַ 
	
} 

void travel_list(struct node *pH)
{
	/*�����������ݣ�ͷ�ڵ㲻��*/ 
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
	struct node *pHeader = creat_list(0);//ͷָ�� 
	
	insert_head(pHeader,creat_list(0));
	insert_head(pHeader,creat_list(1));
	insert_head(pHeader,creat_list(2));
	
	travel_list(pHeader);		
	return 0;
} 
