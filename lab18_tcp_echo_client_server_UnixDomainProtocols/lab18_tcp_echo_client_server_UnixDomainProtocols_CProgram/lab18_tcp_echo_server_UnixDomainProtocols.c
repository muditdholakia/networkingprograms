#include<string.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/un.h>
#include<sys/socket.h>
#include<stdlib.h>
void sig_child(int signo)
{
	int pid,stat;
	while((pid=waitpid(-1,&stat, WNOHANG))>0)
		printf("Child %d exited\n",pid);
	return;
}
int main()
{
	int listenfd, connfd;
	pid_t pid;
	int data[100];
	socklen_t clilen;
	struct sockaddr_un cliaddr, servaddr;
	void sig_child(int);
	listenfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	unlink("/tmp/TCPUniDom");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path,"/tmp/TCPUniDom");
	bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
	listen(listenfd, 5);
	signal(SIGCHLD, sig_child);
	for(;;)
	{
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd,(struct sockaddr *) &cliaddr, &clilen);
		if((pid = fork())==0)
		{
			close(listenfd);
			printf("In child program\n");
			bzero(data,sizeof(data));
			read(connfd,data,sizeof(data));
			printf("Client message : %s\n",data);
			write(connfd,data,sizeof(data));
			close(connfd);
			exit(0);
		}
		else
		{
			printf("In parent program\n");
		}
	}
	close(listenfd);
	exit(0);
}
