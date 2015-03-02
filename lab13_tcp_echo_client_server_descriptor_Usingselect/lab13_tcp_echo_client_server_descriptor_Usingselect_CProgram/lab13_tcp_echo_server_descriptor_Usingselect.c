#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
int main()
{
	int FD_SETSIZE1;
	FD_SETSIZE1 = 3;
	int i,max,maxfd,sockfd,cd,sd,nready,client[FD_SETSIZE1],clilen;
	ssize_t n;
	struct sockaddr_in servaddr, cliaddr;
	char data[100];
	fd_set rset,allset;
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(9500);
	sd=socket(AF_INET,SOCK_STREAM,0);
	bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	bzero(data,sizeof(data));
	listen(sd,5);
	maxfd=sd;
	max=-1;
	for(i=0;i<FD_SETSIZE1;i++)
		client[i]=-1;
	FD_ZERO(&allset);
	FD_SET(sd,&allset);
	for(;;)
	{
		rset=allset;
		nready=select(maxfd+1,&rset,NULL,NULL,NULL);
		if(FD_ISSET(sd,&rset))
		{	
			clilen=sizeof(cliaddr);
			cd=accept(sd,(struct sockaddr*)&cliaddr,&clilen);
			for(i=0;i<FD_SETSIZE1;i++)
		 	if(client[i]<0)
			{
				client[i]=cd;
			    	break;
			}
			if(i==FD_SETSIZE1)
				perror("too many clients\n");
			FD_SET(cd,&allset);
			if(cd>maxfd)
				maxfd=cd;
			if(i>max)
		  		max=i;
			if(--nready <=0)
		   		continue;
		}
		for(i=0;i<=max;i++)
		{
	  		bzero(data,sizeof(data));
	  		if((sockfd = client[i])<0)
				continue;
	  		if(FD_ISSET(sockfd,&rset))
	   		{
				if(n=read(sockfd,data,sizeof(data))==0)
				{
					close(sockfd);
					FD_CLR(sockfd,&allset);
					client[i]=-1;
				}
				else
				{
					printf("Client is: %s\n",data);
					write(sockfd,data,sizeof(data));
				}
				if(--nready<=0)
					break;
	   		}
		}
	}
	close(sd);
	exit(0);
}
