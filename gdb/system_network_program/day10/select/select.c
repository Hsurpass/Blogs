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
#include "mysocket.h"

#define SERVERPORT 8888
#define MAXLINE 1024

int main()
{
    int sockfd;
    int ret = 0;
    int nready = 0;
    int maxfd = -1;
    int clientfd[FD_SETSIZE];
    int maxi = -1;
    char client_ip[INET_ADDRSTRLEN];
    char buf[MAXLINE];
    memset(buf, 0, sizeof(buf));
    fd_set rfdset, allfdset;
    FD_ZERO(&rfdset);
    FD_ZERO(&allfdset);

    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serveraddr, clientaddr;
    bzero(&serveraddr, sizeof(serveraddr));
    bzero(&clientaddr, sizeof(clientaddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t server_len = sizeof(serveraddr);
    Bind(listen_fd, (struct sockaddr *)&serveraddr, server_len);
    Listen(listen_fd, 20);

    maxfd = listen_fd;
    for (size_t i = 0; i < FD_SETSIZE; i++)
    {
        clientfd[i] = -1;
    }
    FD_SET(listen_fd, &allfdset);
    socklen_t client_len;
    int client_fd;
    int i = 0;
    while (1)
    {
        rfdset = allfdset;
        printf("select...\n");
        nready = select(maxfd + 1, &rfdset, NULL, NULL, NULL);
        if (nready < 0)
        {
            perr_exit("select");
        }
        printf("nready = %d\n", nready);
        if (FD_ISSET(listen_fd, &rfdset))
        {
            client_len = sizeof(clientaddr);
            client_fd = Accept(listen_fd, (struct sockaddr *)&clientaddr, &client_len);
            printf("server: client ip addr = %s,port = %d\n", inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, sizeof(client_ip)), ntohs(clientaddr.sin_port));
            printf("client_fd = %d\n", client_fd);
            for (i = 0; i < FD_SETSIZE; i++)
            {
                if (clientfd[i] < 0)
                {
                    clientfd[i] = client_fd;
                    break;
                }
            }
            printf("i = %d\n", i);
            if (i == FD_SETSIZE)
            {
                printf("too many client_fd...  > 1024\n");
                exit(1);
            }
            FD_SET(client_fd, &allfdset);
            if (maxfd < client_fd)
            {
                maxfd = client_fd;
            }
            printf("maxfd = %d\n", maxfd);
            if (i > maxi)
            {
                maxi = i;
            }
            printf("maxi = %d\n", maxi);
            if (--nready == 0)
            {
                continue;
            }
        }

        for (int k = 0; k <= maxi; k++)
        {
            if ((sockfd = clientfd[k]) < 0)
            {
                continue;
            }
            if (FD_ISSET(sockfd, &rfdset))
            {
                ret = Read(sockfd, buf, sizeof(buf));
                if (ret == 0)
                {
                    printf("client[%s:%d] close\n", inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, client_ip, sizeof(client_ip)), ntohs(clientaddr.sin_port));
                    Close(sockfd);
                    FD_CLR(sockfd, &allfdset);
                    clientfd[k] = -1;
                }
                else
                {
                    for (int j = 0; j < ret; j++)
                    {
                        buf[j] = toupper(buf[j]);
                    }
                    Write(sockfd, buf, ret);
                    printf("buf = %s\n", buf);
                }
                if (--nready == 0)      
                {
                    break;
                }
            }

            // if (--nready == 0)
            // {
            //     break;
            // }
        }
    }
    Close(listen_fd);
    return 0;
}