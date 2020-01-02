#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

// 构建一个链表的节点
struct node
{
	int data;				// 有效数据
	struct node *pNext;		// 指向下一个节点的指针
};

// 作用：创建一个链表节点
// 返回值：指针，指针指向我们本函数新创建的一个节点的首地址
struct node * create_node(int data)
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	if (NULL == p)
	{
		printf("malloc error.\n");
		return NULL;
	}

	// 填充节点
	p->data = data;
	p->pNext = NULL;	
	
	return p;
}
// 思路：由头指针向后遍历，直到走到原来的最后一个节点。原来最后一个节点里面的pNext是NULL，现在我们只要将它改成new就可以了。添加了之后新节点就变成了最后一个。
void insert_tail(struct node *pH, struct node *new)
{
	// 分两步来完成插入
	// 第一步，先找到链表中最后一个节点
	struct node *p = pH;/*头指针 = 头指针，要赋值因为头指针没有地址指向*/
	while (NULL != p->pNext)/*头节点的指针域*/
	{
		p = p->pNext;				// 往后走一个节点
	}
	
	// 第二步，将新节点插入到最后一个节点尾部
	p->pNext = new;
}
int main(void)
{
	// 定义头指针
	//struct node *pHeader = NULL;			// 这样直接insert_tail会段错误。
	
	struct node *pHeader = create_node(1);/*头指针 = 创造一个头结点并赋予值为1*/
	
	insert_tail(pHeader, create_node(2));/*插入尾节点（头指针，一个头节点和下一个节点）*/
	insert_tail(pHeader, create_node(3));/*插入尾节点（头指针，一个头节点和下两个节点）*/
	insert_tail(pHeader, create_node(4));/*插入尾节点（头指针，一个头节点和下三个节点）*/
/*
	pHeader = create_node(1);	
	// 将本节点和它前面的头指针关联起来					

	pHeader->pNext = create_node(432);		
	// 将本节点和它前面的头指针关联起来					

	pHeader->pNext->pNext = create_node(123);				
	// 将来要指向下一个节点的首地址

	// 至此创建了一个有1个头指针+3个完整节点的链表。
*/
	// 访问链表中的各个节点的有效数据，这个访问必须注意不能使用p、p1、p2，而只能
	// 使用pHeader。
	
	// 访问链表第1个节点的有效数据
	printf("node1 data: %d.\n", pHeader->data);	
	//printf("p->data: %d.\n", p->data);			// pHeader->data等同于p->data
	
	// 访问链表第2个节点的有效数据
	printf("node2 data: %d.\n", pHeader->pNext->data);	
	//printf("p1->data: %d.\n", p1->data);	
	// pHeader->pNext->data等同于p1->data
	
	// 访问链表第3个节点的有效数据
	printf("node3 data: %d.\n", pHeader->pNext->pNext->data);	
	//printf("p2->data: %d.\n", p2->data);			
	// pHeader->pNext->pNext->data等同于p2->data
	
	// 访问链表第4个节点的有效数据
	printf("node4 data: %d.\n", pHeader->pNext->pNext->pNext->data);
	
	return 0;
}







































