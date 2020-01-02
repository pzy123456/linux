// ջ��Ӧ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//����ڵ�
typedef struct node
{
	int data;//������
	struct node *pNext;//ָ����
}SNode,* PSNode;

//����ջ����ջ�׶��ǽڵ�����
typedef struct stack
{
	PSNode pTop;
	PSNode pBottom;
}STACK,*PSTACK;

void init(PSTACK);
void push(PSTACK,int);
void travelstack(PSTACK S);
bool empty(PSTACK);
void pop(PSTACK,int*);
int main(void)
{
	STACK S;//����һ��ջ����
	int val;
	init(&S);//��ʼ����ջ�������
	push(&S , 1);//��ջ
	push(&S , 2);//��ջ
	push(&S , 3);//��ջ
	push(&S , 4);//��ջ
	push(&S , 5);//��ջ

	pop(&S,&val);//��ջ
	travelstack(&S);//����ջ
	return 0;
}

void init(PSTACK PS)
{
	PS->pTop = (PSNode )malloc(sizeof(SNode));//ջ������ڵ�
	if(PS->pTop == NULL)
	{
		printf("��̬�ڴ����ʧ�ܣ���\n");
		exit(-1);
	}
	else
	{
		PS->pBottom =PS->pTop;//ջ����ջ��ͬʱָ��ͷָ��
		PS->pBottom->pNext = NULL;//ͷָ��ĵ�ַΪ��
	}

}

void push(PSTACK PS,int val)
{
	//����½ڵ�
	PSNode pNew = (PSNode )malloc(sizeof(SNode));
	pNew->data = val;
	pNew->pNext = PS->pTop;
	PS->pTop = pNew;
	return ;

}
void travelstack(PSTACK PS)
{
	//����½ڵ㣬�����ж�����Ԫ��
	PSNode P = PS->pTop; 
	while(P != PS->pBottom)//ֻҪ������ջ�ף�˵������Ԫ��
	{
		printf("%d ",P->data);
		P = P->pNext;
	}
	printf("\n");
	return ;
}
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

