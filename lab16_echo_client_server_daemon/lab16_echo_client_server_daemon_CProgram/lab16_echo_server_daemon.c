#include<stdio.h>
#include<syslog.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<error.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdarg.h>
#include<sys/klog.h>

int daemon_proc;

void daemon_inetd(const char *pname, int facility)
{
	daemon_proc = 1;
	openlog(pname, LOG_PID, facility);
}

int main(int argc,char **argv)
{
    socklen_t len;
    struct sockaddr_in cliaddr;
    char buff[100],data[2000],d[100];
    time_t ticks;
    
    len = sizeof(struct sockaddr_storage);
    getpeername(0,(struct sockaddr *)&cliaddr, &len);
    snprintf(data, sizeof(data),"Connection from %s",inet_ntop(AF_INET,&cliaddr.sin_addr,d,sizeof(d)));
    daemon_inetd(argv[0],0);
    syslog(4,data,sizeof(data));
    bzero(buff,sizeof(buff));
    bzero(data,sizeof(data));	
    read(0,buff,sizeof(buff));
    write(0, buff, strlen(buff));

    exit(0);
}

