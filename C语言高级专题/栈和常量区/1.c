#include <stdio.h>

/*
	return ����ָ��ջ�ڴ�ָ�� 
*/ 
char *GetStr(void)
{
	//char p[] = "hello world";/*������ջ��,�˳�����ʱ��ջ�ڴ��ͷ����٣�pָ��ָ��δֵ֪*/
	char *p = "hello world";/*p������ջ�У�hello world�����ڳ�����*/ 
	return p;
}
/*
	Ϊʲôһ����ջ�У�һ���ھ�̬�� 
	��Ϊָ������Ǳ��������ٵĿռ䣬����û�и�hello world����ռ䣬�����ھ�̬��
	��Ϊ�ַ���������ջ���ٵĿռ䣬�ռ�δ֪���������Ὺ�ٳ��㹻���ջ�ռ�洢��hello world�������ȥ����hello world��ջ�� 
*/
int main(void)
{
	char *p = NULL;
	p = GetStr();
	printf("%s",p); 
	return 0;
} 
