#include <stdio.h>


/*
	˫�����´���β��� 
*/
struct node{
	int data;
	struct node *pPrev;
	struct node *pNext;
};

struct node *creat_list(int data)
{
	/*����ͷ���*/ 
	struct node *pH = (struct node *)malloc(sizeof(struct node));
	if(NULL == pH)
	{
		printf("����ʧ��\n");
		return -1;
	}
	pH->data = data;
	pH->pPrev = NULL;
	pH->pNext = NULL; 
	return pH;
}

void insert_tail(struct node *pH,struct node *new)
{
	/*ͷָ����Ҫָ����Ҫָ����ȷ��ַ*/ 
	struct node *p = pH;
	/*������ڵ����*/ 
	while(NULL != p->pNext)
	{
		p = p->pNext;//��һ��ѭ���߹���ͷ��� 
	} 
	 /*ѭ��������p��ָ����ԭ�������һ���ڵ�*/
	 /*�ڶ��������½ڵ���뵽ԭ����β�ڵ�ĺ���*/ 
	 p->pNext = new;//�����ָ��������ˣ��½ڵ�ĵ�ַ��ǰ�ڵ��next
	 new->pPrev = p->pPrev;//ǰ��ָ��������ˡ��½ڵ��prev��ǰ�ڵ�ĵ�ַ
	 
	 //ǰ�ڵ��prev���½ڵ��nextָ��δ�䶯 
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
