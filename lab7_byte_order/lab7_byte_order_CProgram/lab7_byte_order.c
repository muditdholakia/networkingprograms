#include<stdio.h>

int main()
{
	union
	{
		int i;
		char c[sizeof(int)];
	}a;
	a.i=1;
	printf("%d\n", sizeof(a.c));
	printf("%d\n",a.c[2]);
	if(a.c[0]==1)
		printf("Little Endian\n");
	else
		printf("Big Endian\n");
	return 0;
}
