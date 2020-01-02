#include <stdio.h>
#include <string.h>

struct student
{
	char name[20];
	int num;
	char sex;
};
void Inputstudent(struct student *);
void Outputstudent(struct student *);//传送内容还是传送地址好，是传送地址好，因为传送地址耗用内存少，且速度快，因为指向第一个字节的地址，造4个字节，内容的话要造28字节
int main()
{
	struct student stu;
	printf("%d\n",sizeof(stu));//28因为机器字节对齐
	Inputstudent(&stu);
	Outputstudent(&stu);
	return 0;
}
void Inputstudent(struct student *pstu)
{
	strcpy(pstu->name,"张三");
	pstu->num = 1;
	pstu->sex = 'M';
}
void Outputstudent(struct student *stu)
{
	printf("%s %d %c\n",stu->name,stu->num,stu->sex);
}