// 1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"


#include<stdio.h>
union sizeTest{
        int a;
        double b;
};
main(){
        union sizeTest unionA;
 
		printf("the initial address of unionA is %d\n",sizeof(unionA));

		return 0;
}
       



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

