#include <stdio.h>


//默认从0开始，除非指定第一个数是几
enum Weekday
{
	Monday,Tuesday,Weddnesday,Thursday,Friday,Saturday,Sunday
};
						//更加严格，有效数字，语法会更加对程序检测
void f(enum Weekday i)//本函数的目的只是期望接受0~6的数，限定范围，这就是enum的作用
{						//如果是int，负数，0，正数都可以
	switch(i)
	{
		case 0: printf("Monday!\n");
			break;
		case 1: printf("Tuesday!\n");
			break;
		case 2: printf("Weddnesday!\n");
			break;
		case 3: printf("Thursday!\n");
			break;
		case 4: printf("Friday!\n");
			break;
		case 5: printf("Saturday!\n");
			break;
		case 6: printf("Sunday!\n");
			break;
	}
}
int main()
{
	f(Friday);
	return 0;
}