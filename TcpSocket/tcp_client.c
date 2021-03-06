#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
/*  服务器程序监听的端口号*/
#define PORT 4000
/*  我们一次所能够接收的最大字节数*/
#define MAXDATASIZE 100
int
main(int argc, char *argv[])
{
/*  套接字描述符*/
int sockfd, numbytes;
char buf[MAXDATASIZE];
struct hostent *he;
/*  连接者的主机信息*/
struct sockaddr_in their_addr;
/*  检查参数信息*/
if (argc != 2)
{
/*  如果没有参数，则给出使用方法后退出*/
fprintf(stderr,“ usage: client hostname\n” );
exit(1);
}
/*  取得主机信息*/
if ((he=gethostbyname(argv[1])) == NULL)
/*  如果 gethostbyname()发生错误，则显示错误信息并退出*/
herror(“ gethostbyname” );
exit(1);
}
if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
/*  如果 socket()调用出现错误则显示错误信息并退出*/
perror(“ socket” );
exit(1);
}
/*  主机字节顺序*/
their_addr.sin_family = AF_INET;
/*  网络字节顺序，短整型*/
their_addr.sin_port = htons(PORT);
their_addr.sin_addr = *((struct in_addr *)he->h_addr);
/*  将结构剩下的部分清零*/
bzero(&(their_addr.sin_zero), 8);
if（connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1）
{
/*  如果 connect() 建立连接错误，则显示出错误信息，退出*/
perror(“ connect” );
exit(1);
}
if（(numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1）
{
/*  如果接收数据错误，则显示错误信息并退出*/
perror(“ recv” );
exit(1);
}
buf[numbytes] = ‘ \0’;
printf(“ Received: %s” ,buf);
close(sockfd);
return 0;
}