#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>

void handle_child(int);
int main()
{
	int listenfd,cd, sd,d, n, clilen,i;
	struct sockaddr_in servaddr, cliaddr;
	char data[100];
	pid_t pid;

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(9500);
	signal(SIGCHLD,handle_child);
	sd=socket(AF_INET,SOCK_STREAM,0);
	bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	listenfd=listen(sd,5);
	for(;;)
	{
		clilen=sizeof(cliaddr);
		cd=accept(sd,(struct sockaddr*)&cliaddr,&clilen);
		
		if((pid = fork())==0)
		{
			close(listenfd);
			for(i=1;i<101;i++)
				data[i]='\0';
			i=strlen(data);
			data[i]='\0';
			printf("In Child Program\n");
			for(;;)
			{
				n=read(cd,data,sizeof(data));
				n=strlen(data);
				data[n]='\0';
				printf("Msg from client is:%s\n",data);
				write(cd,data,strlen(data));
			}
			close(cd);
			exit(0);
		}
		else
		{
			printf("In Server Program\n");
		}
	}
	close(sd);
	exit(0);
}

void handle_child(int signo)
{
	int pid,stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("Child %d exited\n",pid);
	return;
}
