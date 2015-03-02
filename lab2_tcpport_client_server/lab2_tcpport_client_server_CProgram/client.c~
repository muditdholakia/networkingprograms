#include<stdio.h> 
#include<sys/socket.h> 
#include<unistd.h> 
#include<netinet/in.h> 
#include<string.h> 
#include<stdlib.h> 

int main() 
{ 
	int cd,sd,n,i; 
	struct sockaddr_in servaddr; 
	char data[100]; 
	bzero(data,100); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(9500); 

	sd = socket(AF_INET,SOCK_STREAM,0); 
	 
	connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr)); 

	printf("Connection is established\n"); 
	 
	n=read(sd,data,sizeof(data)); 

	printf("My Port is %s\n",data); 
	 
	 
	 
	close(sd); 
	 
	exit(0); 
}
