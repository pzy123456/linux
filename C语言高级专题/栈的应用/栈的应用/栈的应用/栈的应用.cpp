// 栈的应用.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//定义节点
typedef struct node
{
	int data;//数据域
	struct node *pNext;//指针域
}SNode,* PSNode;

//定义栈顶，栈底都是节点类型
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
	STACK S;//定义一个栈变量
	int val;
	init(&S);//初始化空栈并造出来
	push(&S , 1);//入栈
	push(&S , 2);//入栈
	push(&S , 3);//入栈
	push(&S , 4);//入栈
	push(&S , 5);//入栈

	pop(&S,&val);//出栈
	travelstack(&S);//遍历栈
	return 0;
}

void init(PSTACK PS)
{
	PS->pTop = (PSNode )malloc(sizeof(SNode));//栈顶分配节点
	if(PS->pTop == NULL)
	{
		printf("动态内存分配失败！！\n");
		exit(-1);
	}
	else
	{
		PS->pBottom =PS->pTop;//栈顶和栈顶同时指向头指针
		PS->pBottom->pNext = NULL;//头指针的地址为空
	}

}

void push(PSTACK PS,int val)
{
	//造出新节点
	PSNode pNew = (PSNode )malloc(sizeof(SNode));
	pNew->data = val;
	pNew->pNext = PS->pTop;
	PS->pTop = pNew;
	return ;

}
void travelstack(PSTACK PS)
{
	//造出新节点，方便判断有无元素
	PSNode P = PS->pTop; 
	while(P != PS->pBottom)//只要不等于栈底，说明就有元素
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

