#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	int sd, n, i,j,k,c,slen;
	struct sockaddr_in servaddr;
	char buff[100];
	char data[100];
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(9500);
	
	sd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&data,sizeof(data));
	bzero(&buff,sizeof(buff));
	if((connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr)))==0)
	{
		printf("Connection is established\n");
		printf("Enter Message:\n ");
		fgets(buff,sizeof(buff),stdin);
		write(sd, &buff,sizeof(buff));
		slen = sizeof(servaddr);
		n = read(sd, &data, sizeof(data));
		printf("Echo message is : %s\n",data);
		close(sd);
		exit(0);
    	}
	else
	{
	    printf("Connection is not established\n");
		exit(0);
	}	
}
