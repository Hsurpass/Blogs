#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include "mysocket.h"

#define SERVERADDR "192.168.226.129"
#define SERVERPORT 8888

void sigpipe(int sig)
{
    printf("sig=%d\n", sig);
}
void sighandle(int sig)
{
    printf("signal = %d\n", sig);
}
// void sigchild(int arg)
// {
//     pid_t childpid,ppid; 
//     ppid = getppid();
//     printf("ppid = %d\n",ppid);   
//     while ((childpid = waitpid(-1, NULL, WNOHANG)) > 0)
//     {
//         printf("client child exit: child id = %d\n", childpid);
//     }
//     kill(ppid,SIGKILL);
// }
int main()
{
    // signal(SIGCHLD, sigchild);
    // for (size_t i = 0; i < 32; i++)
    // {
    //     signal(i,sighandle);
    // }
    signal(SIGINT, sighandle);
    signal(SIGPIPE, sigpipe);

    // struct sigaction act;
    // act.sa_flags = 0;
    // // act.sa_flags = SA_RESTART;
    // act.sa_handler = sighandle;
    // __sigemptyset(&act.sa_mask);
    // sigaction(SIGINT,&act,NULL);

    char buf[1024] = "helloworld";
    struct sockaddr_in serveraddr;
    __bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVERADDR, &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(SERVERPORT);

    socklen_t server_len = sizeof(serveraddr);
    int ret = 0;
    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    printf("connnect...\n");
    Connect(sockfd, (struct sockaddr *)&serveraddr, server_len);
    printf("connect success\n");
    int i = 0;
    int count = 0;
    /* 
    while (1)
    {
        sprintf(buf,"DATA%d",++i);
        ret = write(sockfd, buf, strlen(buf));
        if (ret == -1)
        {
            perror("write");
            close(sockfd);
            exit(errno);
        }
        else
        {
            count += ret;
            printf("client write: buf = %s, ret = %d,count = %d\n",buf,ret,count);
        }
        sleep(1);
    }
    */
    pid_t pid = fork();
    if (pid == 0)
    {
        while (1)
        {
            ret = Read(sockfd, buf, sizeof(buf));
            if (ret <= 0)
            {
                break;
            }
            write(STDOUT_FILENO, buf, ret);
        }
        Close(sockfd);
        exit(0);
    }
    else if (pid > 0)
    {
        pid_t childpid;
        while (1)
        {
            if ((childpid = waitpid(-1,NULL,WNOHANG)) > 0)
            {
                printf("client child exit: child id = %d\n",childpid);
                break;
            }
            printf("ppid = %d\n",getppid());
            if (fgets(buf, sizeof(buf), stdin) != NULL)
            {
                Write(sockfd, buf, strlen(buf));
            }
        }
        exit(1);
    }
    else
    {
        perr_exit("fork");
    }

    return 0;
}