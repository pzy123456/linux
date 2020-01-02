#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *pNext;
};

struct node *creat_node(int data)
{
	//����ͷ��� 
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
	//��һ�����½ڵ��nextָ��ԭ���ĵ�һ���ڵ�
	new->pNext = pH->pNext;
	//�ڶ�����ͷ����nextָ���½ڵ�ĵ�ַ
	pH->pNext = new;
	//ͷ�����������1
	pH->data += 1; 
}
void insert_tail(struct node *pH,struct node *new)
{
	int cnt = 0;
	struct node *p = pH;//���︳���ַ����Ϊ����Ĳ���ʼ�������Ұָ��
	while(NULL != p->pNext)//���������һ���ڵ� 
	{
		p = p->pNext;
		cnt++;
	}
	//��ԭβ���ָ���½ڵ� 
	p->pNext = new; 
	//ͷָ����������1 
	pH->data = cnt+1;
	
}
void travel_list(struct node *pH)
{
	//����֮������ôд��Ϊ�������ȥͷ��㣬ͷ��㲻����Ч�������� 
	struct node *p = pH->pNext; 
	while(NULL != p->pNext)
	{
		printf("%d\n",p->data);
		p = p->pNext; 
	} 
	printf("%d\n",p->data);
}

//������pH��ɾ���ڵ㣬��ɾ���Ľڵ������������������data
//����ֵ�����ҵ����ҳɹ�ɾ���˽ڵ��򷵻�0����δ�ҵ��ڵ�ʱ����-1 
int delete_node(struct node *pH,int data)
{
	//�ҵ������ɾ���Ľڵ㣬ͨ����������������
	struct node *p = pH;//ͷָ�븳���ַ������Ұָ����� 
	struct node *pPrev = NULL;//������ǰ�ڵ��ǰһ���ڵ�,��Ϊɾ���ڵ���Ҫ����ǰһ���ڵ㣬���Զඨ��һ���ڵ��ã�����ָ��ǰһ���ڵ� 
	//�ж��ǲ������һ���ڵ� 
	while(NULL != p->pNext)
	{
		pPrev = p;//��p������һ���ڵ�ǰҪ���䱣��
		p = p->pNext;//������һ���ڵ㣬Ҳ����ѭ������
		//�ж�����ڵ��ǲ�������Ҫ�ҵ��Ǹ��ڵ�
		if(p->data == data)
		{
			//�ҵ��˽ڵ㣬��������ڵ�
			//��Ϊ2�������һ�����ҵ�������ͨ�ڵ㣬��һ�����ҵ����ǽڵ�
			//ɾ���ڵ�����ѵ����ڣ�ͨ����������ı������η��ʸ����ڵ㣬�ҵ�����ڵ�
			//��pָ��������ڵ㣬����Ҫɾ������ڵ�ؼ�Ҫ����ǰһ���ڵ㣬�ҵ�����ڵ�
			//��pָ������ڵ㣬����Ҫɾ������ڵ�ؼ�Ҫ����ǰһ���ڵ㣬�������
			//ʱ���Ѿ�û��ָ��ָ��ǰһ���ڵ㣬����û�����������������������
			//һ��ָ��ָ��ǰ�ڵ��ǰһ���ڵ� 
			if(NULL == p->pNext)
			{
				//���ɾ������ڵ�������β���Ļ� 
				pPrev->pNext = NULL;//ԭ����β����ǰһ���ڵ�����β���
				free(p);            //�ͷ�ԭ����β�����ڴ� 
			} 
			else{
				//��ͨ�ڵ�
				pPrev->pNext = p->pNext; 
				//Ҫɾ���Ľڵ��ǰһ���ڵ�����ĺ�һ���ڵ������������Ͱ�Ҫɾ���Ľڵ��ժ���� 
				free(p); 
			} 
			//�������֮��Ҫ�˳����� 
			return 0;
		} 
		
	} 
	//�����������û�ҵ���˵��������û��������Ҫ�Ľڵ�
	printf("û���ҵ�����ڵ�\n");
	return -1; 	
}
int main(void)
{
	struct node *pHead = creat_node(0);
	insert_head(pHead,creat_node(11));
	insert_head(pHead,creat_node(12));
	insert_head(pHead,creat_node(13));
	//ͷ�ڵ����Ч������pHead->data������ôд��ǰ����ͷָ���ͷ�ڵ�������� 
	printf("node data��%d\n",pHead->data);//��������ڵ����Ч���� 
	travel_list(pHead);
	delete_node(pHead,12);
	printf("-----ɾ����----\n");
	travel_list(pHead); 
	return 0;
} 
