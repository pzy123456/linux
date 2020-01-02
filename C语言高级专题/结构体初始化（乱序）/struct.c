
#include <stdio.h>

typedef int (*sum)(int a,int b);
typedef struct student{
 	char name[10];
	int  age;
	long namber;
	sum sum_fun;
	int a;
	int b;
}ST;
int add(int a,int b)
{
	return a+b;
}

ST std= {
		.age  = 22,
		.name = "pzy",
		.namber = 1603032026,
		.a = 3,
		.b = 4,
		.sum_fun = &add,
	};

int main()
{
	printf("%d\n",std.age);
	printf("%s\n",std.name);
	printf("%ld\n",std.namber);
	printf("%d\n",std.sum_fun(std.a,std.b));
	return 0;
}

