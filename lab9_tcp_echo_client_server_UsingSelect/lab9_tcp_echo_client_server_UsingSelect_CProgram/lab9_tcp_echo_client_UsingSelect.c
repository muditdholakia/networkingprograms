#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/select.h>

int main()
{
	int sd, n, i,j,k;
	struct sockaddr_in servaddr;
	char buff[100];
	char data[100];
//	bzero(&data,sizeof(data));
//	bzero(&buff,sizeof(buff));
	fd_set fs;
	FD_ZERO(&fs);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(9500);
	sd=socket(AF_INET,SOCK_STREAM,0);
	FD_SET(0, &fs);
	FD_SET(sd,&fs);
	if((connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr)))==0)
	{
	printf("Connection is established\n");
	select(sd+1,&fs,NULL,NULL,NULL);
	if(FD_ISSET(0,&fs))
	{
	//close(sd);
	bzero(&buff,sizeof(buff));
	n = read(0,buff,sizeof(buff));
	write(1,buff,strlen(buff));
	}
	if(FD_ISSET(sd,&fs))
	{
	bzero(&data,sizeof(data));
	n = read(sd, data, sizeof(data));
	printf("Message from server is : %s\n",data);
	}
	close(sd);
	exit(0);
}
else
{
    printf("Connection is not established\n");
	exit(0);
}
}

//Client program that selects between stdin and server and whichever is ready,accepts data fromit and prints on it stdio console.
