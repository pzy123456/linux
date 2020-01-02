#include <stdio.h>

struct pack
{
	unsigned a:2;//取值范围为0~3 
	unsigned b:4;//取值范围为0~15
	unsigned c:6;//取值范围为0~63 
	unsigned d:8;//无名位域用来填充空间 
}; 
int main(void)
{
	struct pack p1;
	struct pack p2;
	p1.a = 3;
	p1.b = 10;
	p1.c = 60;
	printf("p1.a = %d,p1.b = %d,p1.c = %d\n",p1.a,p1.b,p1.c);
	/*大小以unsigned为单位4字节对齐*/ 
	printf("%d\n",sizeof(struct pack));
	p2.a = 4;//越界 
	p2.b = 16;//越界 
	p2.c = 64;//越界 
	printf("p1.a = %d,p1.b = %d,p1.c = %d\n",p2.a,p2.b,p2.c);
	return 0;
} 
