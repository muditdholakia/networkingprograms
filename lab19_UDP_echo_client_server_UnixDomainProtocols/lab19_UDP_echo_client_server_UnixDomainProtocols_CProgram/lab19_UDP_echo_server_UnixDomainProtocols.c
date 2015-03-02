#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<sys/un.h>

int main()
{
	int cd, sd, n, clilen,a;
	struct sockaddr_un servaddr, cliaddr;
	char data[100];
	sd=socket(AF_LOCAL,SOCK_DGRAM,0);
	unlink("/tmp/UDPUnixDom");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family=AF_LOCAL;
	strcpy(servaddr.sun_path, "/tmp/UDPUnixDom");
	bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	for(;;)
	{
		bzero(&data,sizeof(data));
		clilen=sizeof(cliaddr);
		n=recvfrom(sd, &data, sizeof(data),0,(struct sockaddr *)&cliaddr,&clilen);
		printf("Client: %s\n",data);
		sendto(sd,&data,sizeof(data),0,(struct sockaddr *)&cliaddr,clilen);
		close(cd);
	} 
	close(sd);
	exit(0);
}

