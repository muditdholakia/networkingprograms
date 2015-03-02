#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<sys/un.h>

int main()
{
	int sd, n, i,j,k;
	struct sockaddr_un servaddr;
	char buff[100];
	char data[100];

	sd=socket(AF_LOCAL,SOCK_STREAM,0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family=AF_LOCAL;
	strcpy(servaddr.sun_path,"/tmp/TCPUniDom");

	if((connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr)))==0)
	{
		bzero(buff,sizeof(buff));
		bzero(data,sizeof(data));
		//printf("%d \n",k);
		printf("Connection is established\n");
		printf("Enter Message:\n ");
		scanf("%s",&buff);
		write(sd,buff,strlen(buff));
		n = read(sd, data, sizeof(data));
		printf("Echo message is : %s\n",data);
	}
else
{
    printf("Connection is not established\n");
	exit(0);
}

	close(sd);
	exit(0);
}
