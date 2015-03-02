#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define N 1000
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
		x[a+1] = x[a] + 1000;
	}
	for(b=0;b<10;b++)
	{
		pthread_join(id[b],NULL);
	}
	exit(0);
}
void *func(void *c)
{
	int i;
	FILE *fp;
	fp = fopen("Div.txt","a+");
	int x =  *((int *)c);
	for(i=0;i<N;i++)
	{
		pthread_mutex_lock(&c_mutex);
		x = x+1;
		if((x%7)==0)
			fprintf(fp,"%d: %d\n", pthread_self(),x);
		pthread_mutex_unlock(&c_mutex);
	}
	fclose(fp);
	return(NULL);
}
