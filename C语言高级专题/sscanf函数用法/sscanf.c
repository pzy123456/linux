#include <stdio.h>

int main()
{
	char *str[] = {0};
	/*
	sscanf("zhoue3456 ", "%4s", str); //取指定长度的字符串       
    printf("str=%s\n", str);   //str="zhou";
	*/

	/*
	sscanf("zhou456 hedf", "%[^ ]", str); //取到指定字符为止的字符串,取遇到空格为止字符串    
    printf("str=%s\n", str);  //str=zhou456;	
	*/

	/*
	sscanf("654321abcdedfABCDEF", "%[1-9a-z]", str); //取仅包含指定字符集的字符串
    printf("str=%s\n", str);  //str=654321abcded，只取数字和小写字符
	*/
	
	/*
	sscanf("BCDEF123456abcdedf", "%[^a-z]", str); //取到指定字符集为止的字符串       
    printf("str=%s\n", str);  //  str=BCDEF123456, 取遇到大写字母为止的字符串
	*/

	/*
	int a,b,c;
    sscanf("2015.04.05", "%d.%d.%d", &a,&b,&c); //取需要的字符串   
    printf("a=%d,b=%d,c=%d\n",a,b,c);  //  a=2015,b=4,c=5
	*/
	
	return 0;
}