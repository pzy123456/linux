#include <stdio.h>
#include <stdlib.h>

void f(int* p)
{
	//*q = 200����Ϊ�����ڲ�û�ж���*q
	//p = 200;	��Ϊ200�����ͳ����������͵�ַ
	*p = 200;	//��Ϊp�ǵ�ַ��*p��4���ֽڣ�Ȼ��200������4���ֽ�
	//free(p);//�ѿ���4���ֽڵ�ַ�ռ��ͷŵ�
}
int main()
{
	int* q = (int *)malloc(sizeof(int));
	*q = 10;
	printf("%d\n",*q);
	f(q);
	printf("%d\n",*q);//*p������ָ���4���ֽڣ������ͷŵ��ˣ���û�з���Ȩ����
	return 0;
}