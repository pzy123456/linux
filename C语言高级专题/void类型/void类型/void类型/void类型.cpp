// void����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"

void add(void *p1,void *p2)
{
	printf("%f\n",(*p1+*p2));
}
int main()
{
	add(&4.5,&5.5);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

