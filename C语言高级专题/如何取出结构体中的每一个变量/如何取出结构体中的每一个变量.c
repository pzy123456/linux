#include <stdio.h>

struct student
{
	int age;
	float score;
	char sex;
};
//st1->age在计算机内部是（*st1）.age
//所以（*st1）.age == st.age
int main()
{
	struct student st = {20,69,'M'};

	struct student *st1 = &st;
	st1->age = 21;
	st1->score = 98;
	st1->sex = 'W';
	printf("%d %f %c\n",st.age,st.score,st.sex);
	printf("%d %f %c\n",st1->age,st1->score,st1->sex);
	return 0;
}