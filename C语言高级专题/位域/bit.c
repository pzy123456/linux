#include <stdio.h>

struct pack
{
	unsigned a:2;//ȡֵ��ΧΪ0~3 
	unsigned b:4;//ȡֵ��ΧΪ0~15
	unsigned c:6;//ȡֵ��ΧΪ0~63 
	unsigned d:8;//����λ���������ռ� 
}; 
int main(void)
{
	struct pack p1;
	struct pack p2;
	p1.a = 3;
	p1.b = 10;
	p1.c = 60;
	printf("p1.a = %d,p1.b = %d,p1.c = %d\n",p1.a,p1.b,p1.c);
	/*��С��unsignedΪ��λ4�ֽڶ���*/ 
	printf("%d\n",sizeof(struct pack));
	p2.a = 4;//Խ�� 
	p2.b = 16;//Խ�� 
	p2.c = 64;//Խ�� 
	printf("p1.a = %d,p1.b = %d,p1.c = %d\n",p2.a,p2.b,p2.c);
	return 0;
} 
