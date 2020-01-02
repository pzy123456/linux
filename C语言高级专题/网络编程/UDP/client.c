#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
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
    sendto
*/
#define SERVPORT 8888 
int main(int argc, char const *argv[])
{
    int iRet;
    int isocketclient;
    int isendlen;
    struct sockaddr_in iserveraddr;
    
    unsigned char sendbuff[1000];
    if(argc != 2)
    {
        printf("Usage:\r\n");
        printf("%s<server_ip>\r\n",argv[0]);
    }
    isocketclient = socket(AF_INET, SOCK_DGRAM, 0);
    if(-1 == isocketclient)
    {
        printf("socket error\r\n");
        return -1;
    }
    iserveraddr.sin_family=AF_INET;
    iserveraddr.sin_port=htons(SERVPORT);
    if(0 == inet_aton(argv[1] , &iserveraddr.sin_addr))
    {
        printf("<server_ip> invaild\r\n");
        return -1;
    }
    memset(iserveraddr.sin_zero,0,8);
    
    while (1)
    {
        if(fgets(sendbuff, 999, stdin))
        {

             /*客户端连服务器*/
            isendlen = sendto(isocketclient, sendbuff, strlen(sendbuff), 0,
                      (const struct sockaddr *)&iserveraddr.sin_addr, sizeof(struct sockaddr));       
            if (isendlen <= 0)
            {
                printf("sendto error\r\n");
                close(isocketclient);
                return -1;
            }
            
        }
       
    }
    
    return 0;
}
