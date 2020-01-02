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
//因为第一个互换程序，形参和实参有不一样开辟的地址单元，所以呢形参交换不会导致实参变换
void huhuan_1(int a,int b)
{
	int t;
	t = a;
	a = b;
	b = t;

}
//因为第二个互换程序，形参和实参有一样开辟的地址单元，交换的是p,q的地址并不是a,b的值
void huhuan_2(int *p,int *q)
{
	int *t;
	t = p;
	p = q;
	q = t;

}
//因为第三个互换程序，形参和实参有一样开辟的地址单元，交换的是*p,*q的值进而改变a,b的值
void huhuan_3(int *p,int *q)
{
	int t;
	t = *p;
	*p = *q;
	*q = t;

}
