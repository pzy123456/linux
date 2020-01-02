#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
struct Node
{
	int data;//������
	struct Node *Next;//ָ����
};

struct Node *Creatlist();
void travel_list(struct Node *pHead);
int isEmpty_list(struct Node *pHead);
void sort_list(struct Node *pHead);
int length_list(struct Node *pHead);

int main()
{
	struct Node *pHead = NULL;
	pHead = Creatlist();//����������ͷָ�뷵�ظ�ͷ���
	travel_list(pHead);//���������������
	return 0;
}

struct Node *Creatlist()
{
	int len;
	int i;
	int val;//������ʱ����û�����ڵ��ֵ
	//������һ��������Ч���ݵ�ͷ���
	struct Node *pHead = (struct Node *)malloc(sizeof(struct Node));
	struct Node *pTail = pHead;
	pTail->Next = pHead;
	if(pHead == NULL)
	{
		printf("����ʧ�ܣ�������ֹ");
		exit(-1);//������ֹ����Ҫ��stdlibͷ�ļ�
	}
	
	pTail ->Next = NULL;
	printf("����������Ҫ�ڵ�������ڵ�ĸ�����len = ");
	scanf_s("%d",&len);
	for(i=0;i<len;i++)
	{
		printf("���������%d���ڵ����",i+1);
		scanf_s("%d",&val);
		struct Node *pNew = (struct Node *)malloc(sizeof(struct Node));
		if(pNew == NULL)
		{
			printf("����ʧ�ܣ�������ֹ");
			exit(-1);	
		}
		pNew->data = val;
		pTail->Next = pNew;//��pNew����pTailҲ����ͷ���
		pNew->Next = NULL;//pNew��ָ�����ǿ�
		pTail = pNew;//pNew������
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
//��С��������
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