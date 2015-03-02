#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#include<poll.h>
int main()
{
	int cd, sd, n, clilen,a,i,max,nready,sockfd;
	struct sockaddr_in servaddr, cliaddr;
	char data[100];
	struct pollfd client[10];
	

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(9500);
	sd=socket(AF_INET,SOCK_STREAM,0);
	bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	//bzero(data,sizeof(data));
	listen(sd,5);
	client[0].fd=sd;
	client[0].events=POLLIN;
	for(i=1;i<10;i++)
		client[i].fd=-1;
	max=0;
	for(;;)
	{
		nready=poll(client,max+1,-1);
		if(client[0].revents & POLLIN)
		{	
			clilen=sizeof(cliaddr);
			cd=accept(sd,(struct sockaddr*)&cliaddr,&clilen);
			for(i=1;i<10;i++)
			  if(client[i].fd<0)
			  {
			    client[i].fd=cd;
			    break;
			}
			client[i].events = POLLIN;
			if(i>max)
		  		max=i;
			if(--nready <=0)
		   		continue;
		}
	for(i=1;i<=max;i++)
	{
	  if((sockfd = client[i].fd)<0)
		continue;
	  if(client[i].revents & POLLIN)
	   {
		n=read(cd, data,sizeof(data));
		//a=strlen(data);
		//data[a]='\0';
		printf("Client: %s\n",data);
		write(cd,data,strlen(data));
		close(cd);
	   }
	}
} 
	close(sd);
	exit(0);

}
