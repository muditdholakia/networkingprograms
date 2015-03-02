#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int cd, sd, n, clilen,a;
	struct sockaddr_in servaddr, cliaddr;
	char data[100];

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(9500);
	sd=socket(AF_INET,SOCK_DGRAM,0);
	bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	listen(sd,5);
	for(;;)
	{
		bzero(&data,sizeof(data));
		clilen=sizeof(cliaddr);
		//cd=accept(sd,(struct sockaddr*)&cliaddr,&clilen);
		n=recvfrom(sd, &data, sizeof(data),0,(struct sockaddr *)&cliaddr,&clilen);
		printf("Client: %s\n",data);
		sendto(sd,&data,sizeof(data),0,(struct sockaddr *)&cliaddr,clilen);
		sleep(1000);
		close(cd);
	} 
	close(sd);
	exit(0);
}

