#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>


int main()
{
	int cd, sd, n, i;
	struct sockaddr_in servaddr;
	char data[100],buff[100];
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(9500);
	bzero(data,sizeof(data));
	bzero(buff,sizeof(buff));	
	sd=socket(AF_INET,SOCK_STREAM,0);
	
       	if((n=connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr)))==0)
	{
	printf("n is %d\n",n);
	printf("Enter Message:\n");
	fgets(data,sizeof(data),stdin);
	n=strlen(data);
	data[n]='\0';
	write(sd,data,strlen(data));
	n=read(sd,buff,sizeof(buff));
	i=strlen(buff);
	buff[i]='\0';
	printf("Echo msg is:%s\n",buff);
	}
	else
	{
		printf("Connection refused\n");
		exit(1);
	}
	close(sd);
	exit(0);
}
