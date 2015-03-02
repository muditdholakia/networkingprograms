#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define N 100
int ans;
pthread_mutex_t c_mutex = PTHREAD_MUTEX_INITIALIZER;
void *func(void *);

int main()
{
	pthread_t id[10];
	int a,b,x[11];
	x[0] = 1;
	int *c[10];
	for(a = 0;a<10;a++)
	{
		c[a] = &x[a];
		pthread_create(&id[a], NULL, &func, c[a]);
		x[a+1] = x[a] +100;
	}
	for(b=0;b<10;b++)
	{
		pthread_join(id[b],NULL);
	}
	printf("Summation is : %d\n",ans);
	exit(0);
}
void *func(void *c)
{	
	int i;
	FILE *fp;
	fp = fopen("summatiion.txt","a+");
	int x =  *((int *)c);
	fprintf(fp,"Value of X is........................ : %d\n",x);
	for(i=0;i<N;i++)
	{
		pthread_mutex_lock(&c_mutex);
		ans = ans + x;
		x = x+1;
		fprintf(fp,"%d: %d\n", pthread_self(),ans);
		pthread_mutex_unlock(&c_mutex);
	}
fclose(fp);
return(NULL);
}
