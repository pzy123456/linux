#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

// ����һ������Ľڵ�
struct node
{
	int data;				// ��Ч����
	struct node *pNext;		// ָ����һ���ڵ��ָ��
};

// ���ã�����һ������ڵ�
// ����ֵ��ָ�룬ָ��ָ�����Ǳ������´�����һ���ڵ���׵�ַ
struct node * create_node(int data)
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	if (NULL == p)
	{
		printf("malloc error.\n");
		return NULL;
	}

	// ���ڵ�
	p->data = data;
	p->pNext = NULL;	
	
	return p;
}
// ˼·����ͷָ����������ֱ���ߵ�ԭ�������һ���ڵ㡣ԭ�����һ���ڵ������pNext��NULL����������ֻҪ�����ĳ�new�Ϳ����ˡ������֮���½ڵ�ͱ�������һ����
void insert_tail(struct node *pH, struct node *new)
{
	// ����������ɲ���
	// ��һ�������ҵ����������һ���ڵ�
	struct node *p = pH;/*ͷָ�� = ͷָ�룬Ҫ��ֵ��Ϊͷָ��û�е�ַָ��*/
	while (NULL != p->pNext)/*ͷ�ڵ��ָ����*/
	{
		p = p->pNext;				// ������һ���ڵ�
	}
	
	// �ڶ��������½ڵ���뵽���һ���ڵ�β��
	p->pNext = new;
}
int main(void)
{
	// ����ͷָ��
	//struct node *pHeader = NULL;			// ����ֱ��insert_tail��δ���
	
	struct node *pHeader = create_node(1);/*ͷָ�� = ����һ��ͷ��㲢����ֵΪ1*/
	
	insert_tail(pHeader, create_node(2));/*����β�ڵ㣨ͷָ�룬һ��ͷ�ڵ����һ���ڵ㣩*/
	insert_tail(pHeader, create_node(3));/*����β�ڵ㣨ͷָ�룬һ��ͷ�ڵ���������ڵ㣩*/
	insert_tail(pHeader, create_node(4));/*����β�ڵ㣨ͷָ�룬һ��ͷ�ڵ���������ڵ㣩*/
/*
	pHeader = create_node(1);	
	// �����ڵ����ǰ���ͷָ���������					

	pHeader->pNext = create_node(432);		
	// �����ڵ����ǰ���ͷָ���������					

	pHeader->pNext->pNext = create_node(123);				
	// ����Ҫָ����һ���ڵ���׵�ַ

	// ���˴�����һ����1��ͷָ��+3�������ڵ������
*/
	// ���������еĸ����ڵ����Ч���ݣ�������ʱ���ע�ⲻ��ʹ��p��p1��p2����ֻ��
	// ʹ��pHeader��
	
	// ���������1���ڵ����Ч����
	printf("node1 data: %d.\n", pHeader->data);	
	//printf("p->data: %d.\n", p->data);			// pHeader->data��ͬ��p->data
	
	// ���������2���ڵ����Ч����
	printf("node2 data: %d.\n", pHeader->pNext->data);	
	//printf("p1->data: %d.\n", p1->data);	
	// pHeader->pNext->data��ͬ��p1->data
	
	// ���������3���ڵ����Ч����
	printf("node3 data: %d.\n", pHeader->pNext->pNext->data);	
	//printf("p2->data: %d.\n", p2->data);			
	// pHeader->pNext->pNext->data��ͬ��p2->data
	
	// ���������4���ڵ����Ч����
	printf("node4 data: %d.\n", pHeader->pNext->pNext->pNext->data);
	
	return 0;
}







































