#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#if 0 
struct sockaddr_in {
　　 short int sin_family; /* 地址族 */
　　 unsigned short int sin_port; /* 端口号 */
　　 struct in_addr sin_addr; /* IP地址 */
　　 unsigned char sin_zero[8]; /* 填充0 以保持与struct sockaddr同样大小 */
　　 };
#endif
/*
    socket
    bind
    sendto/recvfrom
*/
#define SERVPORT 8888
int main(int argc, char const *argv[])
{
    int isocketserver;
    int iRet;
    int iaddrlen;
    int irecvlen;
    unsigned char recvbuff[1000];
    struct sockaddr_in iserveraddr;
    struct sockaddr_in iclientaddr;

    /*僵尸进程收尸*/
    signal(SIGCHLD, SIG_IGN);
    isocketserver = socket(AF_INET, SOCK_DGRAM, 0);
    if (isocketserver == -1)
    {
        printf("socket error\r\n");
        return -1;
    }
    iserveraddr.sin_family=AF_INET;
    iserveraddr.sin_port=htons(SERVPORT);
    iserveraddr.sin_addr.s_addr = INADDR_ANY;
    memset(iserveraddr.sin_zero,0,8);
    /*bind服务器ip，port*/
    iRet = bind(isocketserver, (const struct sockaddr *)&iserveraddr,
                sizeof(struct sockaddr));
    if(-1 == iRet)
    {
        printf("bind error\r\n");
        return -1;
    }
    while (1)
    {
        iaddrlen = sizeof(struct sockaddr);
        /*服务器接收客户端发来的消息*/
        irecvlen = recvfrom(isocketserver, recvbuff, 999, 0,
                        (struct sockaddr *)&iclientaddr.sin_addr, &iaddrlen);
        if (irecvlen <= 0)
        {
            printf("recvfrom error\r\n");
            close(isocketserver);
            return -1;
        }
        else
        {
            printf("Get Msg From %s : %s \r\n",inet_ntoa(iclientaddr.sin_addr),recvbuff);
        }
        
    }
    
    return 0;
}
