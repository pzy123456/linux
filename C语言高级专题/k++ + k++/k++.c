#include <stdio.h>

/*2 + 2 + 2 + 1 + 1 + 1 = 9 */ 
/*k��˳���(&& , || , ;)֮��Ż���Ч*/ 
int main(void)
{
	int k = 2;
	k = ++k + ++k + ++k;
	printf("k = %d\n",k);
	return 0;
}

