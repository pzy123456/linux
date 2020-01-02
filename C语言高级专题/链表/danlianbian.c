#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *pNext;
};
int main(void)
{
	/*创建头结点*/ 
	struct node *p = (struct node *)malloc(sizeof(struct node));
	if(NULL == p)
	{
		printf("创建失败\n");
		return -1;
	}
	p->data = 1;
	p->pNext = NULL;
	printf("%d\n",p->data);
	return 0;
}
