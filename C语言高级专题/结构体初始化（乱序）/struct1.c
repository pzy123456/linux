
#include <stdio.h>

typedef int (*sum)(int a,int b);
typedef struct student{
	sum sum_fun;
	int a;
	int b;
}ST;
int add(int a,int b)
{
	return a+b;
}

ST std= {
		.a = 3,
		.b = 4,
		.sum_fun = &add,
		
	};

int main()
{
	printf("%d\n",std.sum_fun(std.a,std.b));
	return 0;
}

