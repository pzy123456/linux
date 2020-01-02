#include <stdio.h>

int main(void)
{
	char buf[100] = "1010pzy100";
	char num[100] = "pzy";
	int devid = 1010;
	int data = 100;
	//printf("%d\n",sscanf((char *)buf,"%d%s",&devid,num));
	printf("%d\n",sscanf((char *)buf,"%d%[a-z]%d",&devid,num,&data));
	printf("%s,%d\n",num,devid);

	return 0;
}
