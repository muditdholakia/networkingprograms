#include<sys/socket.h>
#include <sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<sys/un.h>
#include<stdio.h>
int main()
{
	int sd,n,len,n1;
	char  buff[50],buff1[50];
	struct sockaddr_un servaddr,cliaddr;

	sd = socket(AF_LOCAL,SOCK_DGRAM, 0);

	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sun_family = AF_LOCAL;
	strcpy(cliaddr.sun_path, tmpnam(NULL));
//	strcpy(cliaddr.sun_path,"/tmp/UDPReply");
	bind(sd, (struct sockaddr *)&cliaddr,sizeof(cliaddr));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family=AF_LOCAL;
	strcpy(servaddr.sun_path, "/tmp/UDPUnixDom");

	bzero(buff, sizeof(buff));
	bzero(buff1,sizeof(buff1));
	printf("Enter message:\n");
	read(0,buff,sizeof(buff));
	len=sizeof(cliaddr);
	sendto(sd,&buff,sizeof(buff),0,(struct sockaddr*)&servaddr,len);
	recvfrom(sd,&buff1,sizeof(buff1),0,(struct sockaddr*)&servaddr,&len);
	printf("Echo Message is: %s\n",buff1);

	close(sd);
	return 0;
}
