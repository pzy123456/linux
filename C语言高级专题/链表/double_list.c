#include <stdio.h>

/*˫�������С�ṹ*/ 
struct node{
	int data;          //��Ч���� 
	struct node *pPrev;//ǰ��ָ�룬ָ��ǰһ���ڵ�
	struct node *pNext;//����ָ�룬ָ���һ���ڵ� 
};

struct node *creat_node(int data)
{
	//ͷ�ڵ� 
	struct node *p = (struct node *)malloc(sizeof(struct node));
	if(NULL == p)
	{
		printf("�����������\n");
		return NULL; 
	} 
	p->data = data;
	p->pNext = NULL;
	p->pPrev = NULL;
	return p;
} 

int main(void)
{
	//ͷָ�� 
	struct node *pHeader = creat_node(0);
	return 0;
}
