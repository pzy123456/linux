#include <stdio.h>

//��һ�⣺�ú궨�彫32λ��x�ĵ�nλ���ұ����㣬Ҳ����bit0���1λ����λ 
#define SET_BIT(x,n) (x|(1<<(n-1)))
//�ڶ��⣺�ú궨�彫32λ��x�ĵ�nλ���ұ����㣬Ҳ����bit0���1λ������ 
#define CLEAR_BIT(x,n) (x&~(1<<(n-1)))

//int main(void)
//{
//	unsigned int a = 0;
//	unsigned int b = 0;
//	b = SET_BIT(a,4);
//	printf("b = 0x%x\n",b);
//	return 0;
//} 

int main(void)
{
	unsigned int a = 0xFFFFFFFF;
	unsigned int b = 0;
	b = CLEAR_BIT(a,4);
	printf("b = 0x%x\n",b);
	return 0;
} 
