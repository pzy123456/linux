#include <stdio.h>

int main(void)
{
	int a[5] = {1,2,3,4,5};
	int *p = (int *)(&a+2);
	//printf("%d,%d",*(a+1),*(p-1));
    printf("p address is 0x%x\n",p);
    printf("the array a address is 0x%x\n",a);
    printf("the array a address is 0x%x\n",&a);
    printf("the array a address is 0x%x\n",&a[0]);
    printf("the array a address is 0x%x\n",&a[1]);
    printf("the array a address is 0x%x\n",&a[2]);    
    printf("the array a address is 0x%x\n",&a[3]);
    printf("the array a address is 0x%x\n",&a[4]);
    printf("the array a address is 0x%x\n",&a[5]);
    return 0;
} 
