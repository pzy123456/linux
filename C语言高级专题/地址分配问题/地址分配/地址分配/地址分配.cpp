// 地址分配.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>

int main()
{
	int a = 0x123456;
	int b = 0x99991199;

	int* q = &b;
	int* p = &a;
	
	printf("%x\n",q[1]);
	//printf("%x\n",*(p-1));	
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

