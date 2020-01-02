#include <stdio.h>

//第一题：用宏定义将32位数x的第n位（右边起算，也就是bit0算第1位）置位 
#define SET_BIT(x,n) (x|(1<<(n-1)))
//第二题：用宏定义将32位数x的第n位（右边起算，也就是bit0算第1位）清零 
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
