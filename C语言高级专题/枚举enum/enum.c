#include <stdio.h>


//Ĭ�ϴ�0��ʼ������ָ����һ�����Ǽ�
enum Weekday
{
	Monday,Tuesday,Weddnesday,Thursday,Friday,Saturday,Sunday
};
						//�����ϸ���Ч���֣��﷨����ӶԳ�����
void f(enum Weekday i)//��������Ŀ��ֻ����������0~6�������޶���Χ�������enum������
{						//�����int��������0������������
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