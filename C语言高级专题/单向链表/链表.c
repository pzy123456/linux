#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
struct Node
{
	int data;//数据域
	struct Node *Next;//指针域
};

struct Node *Creatlist();
void travel_list(struct Node *pHead);
int isEmpty_list(struct Node *pHead);
void sort_list(struct Node *pHead);
int length_list(struct Node *pHead);

int main()
{
	struct Node *pHead = NULL;
	pHead = Creatlist();//创造链表，将头指针返回给头结点
	travel_list(pHead);//遍历链表，输出链表
	return 0;
}

struct Node *Creatlist()
{
	int len;
	int i;
	int val;//用来临时存放用户输入节点的值
	//分配了一个不是有效数据的头结点
	struct Node *pHead = (struct Node *)malloc(sizeof(struct Node));
	struct Node *pTail = pHead;
	pTail->Next = pHead;
	if(pHead == NULL)
	{
		printf("分配失败，程序终止");
		exit(-1);//程序终止，需要用stdlib头文件
	}
	
	pTail ->Next = NULL;
	printf("请您输入需要节点的数量节点的个数：len = ");
	scanf_s("%d",&len);
	for(i=0;i<len;i++)
	{
		printf("请您输入第%d个节点个数",i+1);
		scanf_s("%d",&val);
		struct Node *pNew = (struct Node *)malloc(sizeof(struct Node));
		if(pNew == NULL)
		{
			printf("分配失败，程序终止");
			exit(-1);	
		}
		pNew->data = val;
		pTail->Next = pNew;//将pNew挂在pTail也就是头结点
		pNew->Next = NULL;//pNew的指针域是空
		pTail = pNew;//pNew往后移
	}
	return pHead;
}

void travel_list(struct Node *pHead)
{
	struct Node *p = pHead->Next;
	while(p != NULL)
	{
		printf("%d\n",p->data);
		p = p->Next;
	}
}

int isEmpty_list(struct Node *pHead)
{
	struct Node *p = pHead->Next;
	if( p != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int length_list(struct Node *pHead)
{
	int len = 0;
	struct Node *p = pHead->Next;
	if( p != NULL)
	{
		len++;
		p = p->Next;
	}
	return len;
}
//从小到大排序
void sort_list(struct Node *pHead)
{
	int i,j,t;
	struct Node *p,*q;
	int len = length_list(pHead);
	for(i=0,p = pHead->Next;i<len;i++,p = p->Next)
	{
		for(j=i+1,q = p->Next;j<len;j++,q = q->Next)
		{
			if( p->data > q->data)//( a[i] > a[j])
			{
				t = p->data;//t = a[i];
				p->data = q->data;//a[i] = a[j];
				q->data = t;//a[j] = t;
			}
		}
	}
	return;
}