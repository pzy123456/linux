#include <stdio.h>

void huhuan_1(int ,int );
void huhuan_2(int *,int *);
void huhuan_3(int *,int *);
int main()
{
	int a = 3;
	int b = 5;
	
	huhuan_1(a,b);
	printf("%d,%d\n",a,b);
	huhuan_2(&a,&b);
	printf("%d,%d\n",a,b);
	huhuan_3(&a,&b);
	printf("%d,%d\n",a,b);
	return 0;
}
//��Ϊ��һ�����������βκ�ʵ���в�һ�����ٵĵ�ַ��Ԫ���������βν������ᵼ��ʵ�α任
void huhuan_1(int a,int b)
{
	int t;
	t = a;
	a = b;
	b = t;

}
//��Ϊ�ڶ������������βκ�ʵ����һ�����ٵĵ�ַ��Ԫ����������p,q�ĵ�ַ������a,b��ֵ
void huhuan_2(int *p,int *q)
{
	int *t;
	t = p;
	p = q;
	q = t;

}
//��Ϊ���������������βκ�ʵ����һ�����ٵĵ�ַ��Ԫ����������*p,*q��ֵ�����ı�a,b��ֵ
void huhuan_3(int *p,int *q)
{
	int t;
	t = *p;
	*p = *q;
	*q = t;

}
