#include <stdio.h>

/*2 + 2 + 2 + 1 + 1 + 1 = 9 */ 
/*k到顺序点(&& , || , ;)之后才会生效*/ 
int main(void)
{
	int k = 2;
	k = ++k + ++k + ++k;
	printf("k = %d\n",k);
	return 0;
}

