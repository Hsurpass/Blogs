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
#include "mysocket.h"

void sigCHILD(int sig)
{
    pid_t childpid;
    while((childpid = waitpid(-1,NULL,WNOHANG)) > 0)
    {
        printf("server recycle child process id:%d, sig = %d\n",childpid,sig);
    }
}

void sighandle(int sig)
{
    printf("sig:%d\n", sig);
}
int main()
{
    signal(SIGCHLD, sigCHILD);

    struct sigaction act;
    act.sa_flags = 0;
    // act.sa_flags = SA_RESTART;
    act.sa_handler = sighandle;
    __sigemptyset(&act.sa_mask);
    sigaction(SIGINT,&act,NULL);


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
    while (1)
    {
        clientaddr_len = sizeof(client_addr);
        printf("server:parent pid = %d\n",getpid());
        printf("accept...\n");
        int client_fd = Accept(listen_fd, (struct sockaddr *)&client_addr, &clientaddr_len);
        
        pid_t pid = fork();                
        
        if(pid == 0)
        {
            close(listen_fd);
            printf("server:child_process id = %d, client_fd = %d,client_ip = %s,client_port = %d\n",
               getpid(),client_fd, inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, clientip, sizeof(clientip)), ntohs(client_addr.sin_port));
            // while (1)
            // {
                {
                    dup2(client_fd,STDIN_FILENO);
                    dup2(client_fd,STDOUT_FILENO);
                    dup2(client_fd,STDERR_FILENO);
                    execlp("./myshell","myshell",NULL);
                    close(client_fd);
                    exit(0);
                }
            // sleep(1);
            // }
            // Close(client_fd);
            // exit(0);
        }
        else if(pid > 0)
        {
            printf("server:parent pid = %d\n",getpid());
            close(client_fd);            
        }
        else
        {
            perr_exit("fork");
        }
    }

    close(listen_fd);
    return 0;
}