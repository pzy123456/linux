#include <stdio.h>
#include <string.h>

void getMemory(char *p)
{
	/*char *p = str*/
	p = (char *)malloc(100);
	strcpy(p,"hello world");
	printf("p:%s\n",p); 
}
int main(void)
{
	printf("Enter main...\n");
	char *str = "pzy";
	printf("str:%s\n",str);
	/*�����ݵ���str�ĸ�������������������˵��Ȼ������Ǹ�����
	��getmemory��������Ĵ��룬Ҳ���Ƕ�����������в����ݺ������ý���
	Ҳ��������*/ 
	getMemory(str);/*����ȡ��ַ������char* ��������ͨ����*/
					/*����ȡ��ַ������char** ����˼��ָ���ַ�ϵ�����*/ 
	printf("%s\n",str);
	if(NULL != str)
	{
		free(str);
	} 
	return 0;
} 
