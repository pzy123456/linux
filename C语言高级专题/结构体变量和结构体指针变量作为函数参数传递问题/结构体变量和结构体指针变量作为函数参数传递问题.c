#include <stdio.h>
#include <string.h>

struct student
{
	char name[20];
	int num;
	char sex;
};
void Inputstudent(struct student *);
void Outputstudent(struct student *);//�������ݻ��Ǵ��͵�ַ�ã��Ǵ��͵�ַ�ã���Ϊ���͵�ַ�����ڴ��٣����ٶȿ죬��Ϊָ���һ���ֽڵĵ�ַ����4���ֽڣ����ݵĻ�Ҫ��28�ֽ�
int main()
{
	struct student stu;
	printf("%d\n",sizeof(stu));//28��Ϊ�����ֽڶ���
	Inputstudent(&stu);
	Outputstudent(&stu);
	return 0;
}
void Inputstudent(struct student *pstu)
{
	strcpy(pstu->name,"����");
	pstu->num = 1;
	pstu->sex = 'M';
}
void Outputstudent(struct student *stu)
{
	printf("%s %d %c\n",stu->name,stu->num,stu->sex);
}