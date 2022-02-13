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
#include <ctype.h>
#include <pthread.h>
#include "mysocket.h"

// void sigCHILD(int sig)
// {
//     pid_t childpid;
//     while ((childpid = waitpid(-1, NULL, WNOHANG)) > 0)
//     {
//         printf("server recycle child process id:%d, sig = %d\n", childpid, sig);
//     }
// }

void sighandle(int sig)
{
    printf("sig:%d\n", sig);
}

void *mythread(void *arg)
{
    pthread_detach(pthread_self());
    printf("server:child_pthread id = %lx\n",pthread_self());
    char buf[64];
    memset(buf, 0x31, sizeof(buf));
    int client_fd = (int)arg;
    int ret=0;
    while (1)
    {
        ret = Read(client_fd, buf, sizeof(buf));
        if (ret == 0)
        {
            printf("client close\n");
            break;
        }
        /*else
                {
                    buf[ret] = '\0';
                    printf("server childid[%d] read: buf = %s,ret = %d\n", getpid(),buf, ret);
                }*/
        else
        {
            for (size_t i = 0; i < ret; i++)
            {
                buf[i] = toupper(buf[i]);
            }
            Write(client_fd, buf, ret);
        }
        // sleep(1);
    }
    Close(client_fd);
    pthread_exit((void*)2);
}

int main()
{
    // signal(SIGCHLD, sigCHILD);

    struct sigaction act;
    act.sa_flags = 0;
    // act.sa_flags = SA_RESTART;
    act.sa_handler = sighandle;
    __sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, NULL);

    char buf[64];
    memset(buf, 0x31, sizeof(buf));
    char clientip[16];
    memset(clientip, 0x31, sizeof(clientip));
    int ret = 0;
    struct sockaddr_in server_addr, client_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8888);

    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    Listen(listen_fd, 128);

    socklen_t clientaddr_len;
    pthread_t thid;
    while (1)
    {
        clientaddr_len = sizeof(client_addr);
        printf("accept...\n");
        int client_fd = Accept(listen_fd, (struct sockaddr *)&client_addr, &clientaddr_len);
        printf("server:main_pthread id = %lx, client_fd = %d,client_ip = %s,client_port = %d\n",
           pthread_self(), client_fd, inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, clientip, sizeof(clientip)), ntohs(client_addr.sin_port));
        
        ret = pthread_create(&thid, NULL, mythread, (void*)client_fd);
        if (ret != 0)
        {
            printf("%s\n", strerror(ret));
            exit(ret);
        }

    }

    close(listen_fd);
    return 0;
}