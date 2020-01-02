#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *pNext;
};

struct node *creat_node(int data)
{
	//创建头结点 
	struct node *pH = (struct node *)malloc(sizeof(struct node));
	if(NULL == pH)
	{
		printf("malloc error\n");
		return -1;
	}
	pH->data = data;
	pH->pNext = NULL; 
	return pH;
}
void insert_head(struct node *pH,struct node *new)
{
	//第一步：新节点的next指向原来的第一个节点
	new->pNext = pH->pNext;
	//第二步：头结点的next指向新节点的地址
	pH->pNext = new;
	//头结点的数据域加1
	pH->data += 1; 
}
void insert_tail(struct node *pH,struct node *new)
{
	int cnt = 0;
	struct node *p = pH;//这里赋予地址，因为传入的不初始化会产生野指针
	while(NULL != p->pNext)//遍历到最后一个节点 
	{
		p = p->pNext;
		cnt++;
	}
	//将原尾结点指向新节点 
	p->pNext = new; 
	//头指针的数据域加1 
	pH->data = cnt+1;
	
}
void travel_list(struct node *pH)
{
	//这里之所以这么写因为数据域除去头结点，头结点不是有效的数据域 
	struct node *p = pH->pNext; 
	while(NULL != p->pNext)
	{
		printf("%d\n",p->data);
		p = p->pNext; 
	} 
	printf("%d\n",p->data);
}

//从链表pH中删除节点，待删除的节点的特征是数据区等于data
//返回值：当找到并且成功删除了节点则返回0，当未找到节点时返回-1 
int delete_node(struct node *pH,int data)
{
	//找到这个待删除的节点，通过遍历链表来查找
	struct node *p = pH;//头指针赋予地址，避免野指针出现 
	struct node *pPrev = NULL;//用来当前节点的前一个节点,因为删除节点是要操作前一个节点，所以多定义一个节点用，用来指向前一个节点 
	//判断是不是最后一个节点 
	while(NULL != p->pNext)
	{
		pPrev = p;//在p走向下一个节点前要将其保存
		p = p->pNext;//走向下一个节点，也就是循环增量
		//判断这个节点是不是我们要找的那个节点
		if(p->data == data)
		{
			//找到了节点，处理这个节点
			//分为2种情况，一个是找到的是普通节点，另一个是找到的是节点
			//删除节点的困难点在于：通过链表链表的遍历依次访问各个节点，找到这个节点
			//后p指向了这个节点，但是要删除这个节点关键要操作前一个节点，找到这个节点
			//后p指向这个节点，但是要删除这个节点关键要操作前一个节点，但是这个
			//时候已经没有指针指向前一个节点，所以没法操作。解决方案就是增加
			//一个指针指向当前节点的前一个节点 
			if(NULL == p->pNext)
			{
				//如果删除这个节点的情况是尾结点的话 
				pPrev->pNext = NULL;//原来的尾结点的前一个节点变成新尾结点
				free(p);            //释放原来的尾结点的内存 
			} 
			else{
				//普通节点
				pPrev->pNext = p->pNext; 
				//要删除的节点的前一个节点和它的后一个节点相连，这样就把要删除的节点给摘出来 
				free(p); 
			} 
			//处理完成之后要退出程序 
			return 0;
		} 
		
	} 
	//到这里如果还没找到，说明链表中没有我们想要的节点
	printf("没有找到这个节点\n");
	return -1; 	
}
int main(void)
{
	struct node *pHead = creat_node(0);
	insert_head(pHead,creat_node(11));
	insert_head(pHead,creat_node(12));
	insert_head(pHead,creat_node(13));
	//头节点的有效数据是pHead->data，能这么写的前提是头指针和头节点关联起来 
	printf("node data：%d\n",pHead->data);//访问链表节点的有效数据 
	travel_list(pHead);
	delete_node(pHead,12);
	printf("-----删除后----\n");
	travel_list(pHead); 
	return 0;
} 
