#include<stdio.h> 
#include<sys/socket.h> 
#include<unistd.h> 
#include<netinet/in.h> 
#include<string.h> 
#include<stdlib.h> 
#define MAX 100 
int main() 
{ 
	int sd,n,flag=1; 
	struct sockaddr_in servaddr; 
	char data[MAX]; 
	char out[]="exit"; 
	 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(9500); 

	sd = socket(AF_INET,SOCK_STREAM,0); 
	 
	connect(sd,(struct sockaddr*)&servaddr,sizeof(servaddr)); 

	for(;;) { 
		data[0]='\0'; 
		n=read(0,data,sizeof(data)); 
		 
		flag = strncmp(data,out,4); 
		printf("Flag is %d:\n",flag); 
		if(!flag) { break; } 
		 
		write(sd,data,n); 
		
		data[0]='\0'; 

		n=read(sd,data,sizeof(data));

		write(1,data,n); 
	} 
	close(sd); 
	exit(0); 
}
