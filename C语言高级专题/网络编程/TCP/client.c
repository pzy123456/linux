#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
 #include <unistd.h>
#include <arpa/inet.h>
/*
    socket
    connect
    send/recv
*/
#define SERVPORT 8888
int main(int argc, char const *argv[])
{
    int isocketclient;
    int iRet;
    int isendlen;
    struct sockaddr_in iserveraddr;
    unsigned char sendbuff[1000];
    if (argc != 2)
	{
		printf("Usage:\n");
		printf("%s <server_ip>\n", argv[0]);/*提示ip打印出来*/
		return -1;
	}
    isocketclient = socket(AF_INET, SOCK_STREAM, 0);
    
    iserveraddr.sin_family=AF_INET;
    iserveraddr.sin_port = htons(SERVPORT);
    if(0 == inet_aton(argv[1],&iserveraddr.sin_addr ))
    {
        printf("invalid server_ip\r\n");
        return -1;
    }

    memset(iserveraddr.sin_zero,0,8);
    /*客户端连服务器,服务器提供ip,port地址信息*/
      iRet = connect(isocketclient, (const struct sockaddr *)&iserveraddr,
                   sizeof(struct sockaddr));
        if (-1 == iRet)
        {
            printf("connect error\r\n");
            close(isocketclient);
            return -1;
        }
        
    while (1)
    {
        if(fgets(sendbuff, 999, stdin))
        {
            /*strlen长度不一定是999，因为遇到换行就会停止返回*/
            isendlen = send(isocketclient, sendbuff, strlen(sendbuff), 0);
            if(isendlen <= 0)
            {
                printf("send error\r\n");
				close(isocketclient);
                return -1;
            }
        }
                   
    }
    
    return 0;
}
