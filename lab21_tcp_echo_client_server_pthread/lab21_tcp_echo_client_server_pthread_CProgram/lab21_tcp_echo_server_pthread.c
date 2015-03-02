#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
static void *procThread(void *);
int main()
{
	int *cd, sd, n, clilen,a;
	struct sockaddr_in servaddr, cliaddr;
	pthread_t tid;

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(9900);
	sd=socket(AF_INET,SOCK_STREAM,0);
	bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	listen(sd,5);
	for(;;)
	{
		clilen=sizeof(cliaddr);
		cd = malloc(sizeof(int));
		*cd=accept(sd,(struct sockaddr*)&cliaddr,&clilen);
		pthread_create(&tid, NULL, &procThread,cd);
	} 
	close(sd);
	exit(0);
}
static void *procThread(void *cd)
{
	int n,c;
	c = *((int *) cd);
	free(cd);
	char data[100];
	FILE *fp;
	fp = fopen("test.txt","a+"); 
	bzero(data,sizeof(data));
	pthread_detach(pthread_self());
	n=read((int)c, data,sizeof(data));
	fprintf(fp,"Client message: %s\n ",data);
	write((int)c,data,strlen(data));
	fclose(fp);
	close((int)c);
	return(NULL);
}

