#include<sys/socket.h>
#include <sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>


int main(){


	int sd,cd,n,len,n1;
	char  buff[50],buff1[50];


	struct sockaddr_in server;
	struct sockaddr_in client;
	len = sizeof(struct sockaddr_in);

	sd = socket(AF_INET,SOCK_DGRAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(9500);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(sd==-1)
	{
		write(1,"Error\n",5);
		return 0;
	}
	while(1)
	{
	n=read(0,buff,sizeof(buff));
	sendto(sd,buff,n,0,(struct sockaddr*)&server,len);

	recvfrom(sd,buff1,sizeof(buff1),0,(struct sockaddr*)&server,&len);
	write(1,buff1,n);
	}
	close(sd);
	return 0;

}
