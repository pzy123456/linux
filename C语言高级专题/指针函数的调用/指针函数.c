#include <stdio.h>
#include <stdlib.h>

/*�ȶ���һ���ṹ��*/ 
typedef struct Data{
	int a;
	int b;
}Data; 
/*ָ�뺯��*/
Data *fun(int a,int b)
{
	/*�ٶ���һ���ṹ��ָ�����ͱ�������̬�����ڴ�*/
	Data *data = (Data *)malloc(sizeof(Data));
	/*Ϊ�ṹ��������и�ֵ*/
	data->a = a; 
	data->b = b;
	/*ָ�뺯�����صĵ�ַ�����ﷵ�صĽṹ��ָ������ĵ�ַ*/
	return data;
} 
int main(void)
{
	Data *mydata = fun(2,3);
	printf("mydata->a = %d,mydata->b = %d\n",mydata->a,mydata->b);
	return 0;
}
