#include <poll.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <errno.h>
#include <ctype.h>
#include <sys/epoll.h>
#include "mysocket.h"

#define SERVERPORT 8888
#define MAXLINE 1024
#define OPENMAX 1024

int main()
{
    int sockfd, connfd;
    struct epoll_event event, epev[10];
    int ret = -1;
    int nready = 0;
    char buf[MAXLINE];
    char client_ip[INET_ADDRSTRLEN];
    memset(buf, 0, sizeof(buf));
    struct sockaddr_in serveraddr, clientaddr;
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&clientaddr, sizeof(clientaddr));

    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    int flag = 1;
    int len = sizeof(flag);
    ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &flag, len);
    if (ret == -1)
    {
        perr_exit("setsockopt");
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(listen_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    Listen(listen_fd, 128);

    int epfd = epoll_create(10);
    if (-1 == epfd)
    {
        perr_exit("epoll_create");
        exit(errno);
    }
    event.events = EPOLLIN;
    event.data.fd = listen_fd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &event);
    if (-1 == ret)
    {
        perr_exit("epoll_ctl");
        exit(errno);
    }

    socklen_t client_len;
    while (1)
    {
        printf("epoll_wait...\n");
        nready = epoll_wait(epfd, epev, 10, -1);
        if (nready < 0)
        {
            perr_exit("epoll_wait");
            exit(errno);
        }
        printf("nready = %d\n", nready);
        for (size_t i = 0; i < nready; i++)
        {
            if (!(epev[i].events & EPOLLIN))
            {
                continue;
            }
            if (epev[i].data.fd == listen_fd)
            {
                client_len = sizeof(clientaddr);
                connfd = Accept(listen_fd, (struct sockaddr *)&clientaddr, &client_len);
                printf("server: client ip addr = %s,port = %d\n", inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, sizeof(client_ip)), ntohs(clientaddr.sin_port));
                printf("connfd = %d\n", connfd);
                event.events = EPOLLIN /*| EPOLLET*/;
                event.data.fd = connfd;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event);
                if (-1 == ret)
                {
                    perr_exit("epoll_ctl");
                }
            }
            else
            {
                sockfd = epev[i].data.fd;
                // ret = Read(sockfd,buf,sizeof(buf));
                while (1)
                {
                    ret = Read(sockfd, buf, 5);
                    if (ret == 0)
                    {
                        printf("client[fd:%d] close\n", epev[i].data.fd);
                        ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                        if (ret < 0)
                        {
                            perr_exit("epoll_ctl");
                        }
                        Close(sockfd);
                        printf("--------\n");
                        break;
                    }
                    else
                    {
                        // for (size_t j = 0; j < ret; j++)
                        // {
                        //     buf[j] = toupper(buf[j]);
                        // }
                        // Write(sockfd,buf,ret);
                        Write(STDOUT_FILENO, buf, ret);
                    }
                }
            }
        }
    }
    Close(epfd);
    Close(listen_fd);
    return 0;
}