#include <stdio.h>

int main()
{
	char *str[] = {0};
	/*
	sscanf("zhoue3456 ", "%4s", str); //ȡָ�����ȵ��ַ���       
    printf("str=%s\n", str);   //str="zhou";
	*/

	/*
	sscanf("zhou456 hedf", "%[^ ]", str); //ȡ��ָ���ַ�Ϊֹ���ַ���,ȡ�����ո�Ϊֹ�ַ���    
    printf("str=%s\n", str);  //str=zhou456;	
	*/

	/*
	sscanf("654321abcdedfABCDEF", "%[1-9a-z]", str); //ȡ������ָ���ַ������ַ���
    printf("str=%s\n", str);  //str=654321abcded��ֻȡ���ֺ�Сд�ַ�
	*/
	
	/*
	sscanf("BCDEF123456abcdedf", "%[^a-z]", str); //ȡ��ָ���ַ���Ϊֹ���ַ���       
    printf("str=%s\n", str);  //  str=BCDEF123456, ȡ������д��ĸΪֹ���ַ���
	*/

	/*
	int a,b,c;
    sscanf("2015.04.05", "%d.%d.%d", &a,&b,&c); //ȡ��Ҫ���ַ���   
    printf("a=%d,b=%d,c=%d\n",a,b,c);  //  a=2015,b=4,c=5
	*/
	
	return 0;
}