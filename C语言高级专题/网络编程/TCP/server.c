#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
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
    listen
    accept
    send/recv
*/
#define SERVPORT 8888
#define BACKLOG  10
int main(int argc, char const *argv[])
{
    int isocketserver;
    int isocketclient;
	struct sockaddr_in iserveraddr;
    struct sockaddr_in iclientaddr;
    int iRet;
    int iaddrlen;
    int clientnum = -1;
    int irecvlen;
    unsigned char recvbuff[1000];
    
	/*僵尸进程提前收尸*/
	signal(SIGCHLD,SIG_IGN);
    isocketserver = socket(AF_INET, SOCK_STREAM, 0);
    if (isocketserver == -1)
    {
        printf("socket error\r\n");
        
        return -1;
    }
        iserveraddr.sin_family=AF_INET;
        iserveraddr.sin_port = htons(SERVPORT);
        iserveraddr.sin_addr.s_addr = INADDR_ANY;
        memset(iserveraddr.sin_zero,0,8);
       iRet = bind(isocketserver, (const struct sockaddr *)&iserveraddr,
                sizeof(struct sockaddr));
    if (-1 == iRet)
    {
        printf("bind error\r\n");
        
        return -1;
    }

     iRet = listen(isocketserver, BACKLOG); 
     if (-1 == iRet)
     {
         printf("listen error\r\n");
        
        return -1;
     }
      while (1)
      {
          iaddrlen = sizeof(struct sockaddr);
          /*客户端主动连服务器*/
          isocketclient = accept(isocketserver, (struct sockaddr *)&iclientaddr, &iaddrlen);
          if(isocketclient != -1)
          {
              /*接收到客户端的连接，打印出客户端号码，和ip地址*/
              clientnum++;
              printf("Get connect from client %d:%s\r\n",clientnum,inet_ntoa((struct in_addr)iclientaddr.sin_addr));
             if(!fork())
             {
                 while (1)
                 {
                    /*子进程*/
                    irecvlen = recv(isocketclient, recvbuff, 999, 0);
                    if(irecvlen <= 0 )
                    {
                        printf("recv error\r\n");
                        close(isocketserver);
                        return -1;
                    }
                    else
                    {
                        recvbuff[irecvlen] = '\0';/*加上结束符*/
                        printf("Get Msg From client %d:%s\r\n",clientnum,recvbuff);

                    }
                 }   
             }
             else
             {
                 ;/* 父进程 */
             }
             
          }
      }
     close(isocketserver);     
    return 0;
}



