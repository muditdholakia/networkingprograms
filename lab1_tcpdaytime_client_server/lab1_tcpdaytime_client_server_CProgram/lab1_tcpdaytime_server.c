#include<stdio.h> 
#include<sys/socket.h> 
#include<unistd.h> 
#include<netinet/in.h> 
#include<string.h> 
#include<stdlib.h> 
#include<time.h>
int main() 
{ 
	int cd,sd,n,clilen; 
	struct sockaddr_in servaddr,cliaddr; 
	char data[100]; 
	char buff[10]; 
	time_t ticks;
	 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(9501); 

	sd = socket(AF_INET,SOCK_STREAM,0); 
	bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr)); 

	listen(sd,5); 	
	for(; ;) 
	{ 
				
		clilen = sizeof(cliaddr); 
		cd = accept(sd,(struct sockaddr*)&cliaddr,&clilen); 
		printf("connection from client\n");

		ticks=time(NULL);
		snprintf(data,sizeof(data),"%.24s\r\n",ctime(&ticks)); 
		
		n=strlen(data); 
		data[n]='\0'; 

		write(cd,data,strlen(data)); 
		close(cd); 
	} 
	close(sd); 
	exit(0); 
}	 
