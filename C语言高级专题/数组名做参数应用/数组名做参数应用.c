#include <stdio.h>



void main()
{	
	void average(int b[10]);
	int score[10]={88,89,93,94,95,96,97,78,84,82};
	printf("%d\n",sizeof(score));
	average(score);
}
void average(int b[10])
{
	int aver,i,sum = 0;
	printf("%d\n",sizeof(b)); 
	for(i=0;i<10;i++)
	{
		printf("%3d",b[i]);
		sum += b[i];
	}
	aver = sum/10;
	printf("aver = %d\n",aver);
}
