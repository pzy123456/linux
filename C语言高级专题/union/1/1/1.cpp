// 1.cpp : 定义控制台应用程序的入口点。
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

