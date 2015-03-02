#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>


int main()
{
	int sd, n, i,j,k;
	struct sockaddr_in servaddr;
	char buff[100];
	char data[100];
	bzero(data,100);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(9500);
	
	sd=socket(AF_INET,SOCK_STREAM,0);

	if((connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr)))==0)
	{
	
	printf("Enter Message:\n ");
	scanf("%s",&buff);
	j = strlen(buff);
	buff[j]='\0';
	write(sd,buff,strlen(buff));
	n = read(sd, data, sizeof(data));
	j=sizeof(data);
	data[j]='\0';
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

