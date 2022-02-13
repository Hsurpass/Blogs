#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>

#define SERVERADDR "192.168.226.129"
#define SERVERPORT 8888

void sighandle(int sig)
{
    printf("signal = %d\n",sig);
}
int main()
{
    for (size_t i = 0; i < 32; i++)
    {
        signal(i,sighandle);    
    }
    
    char buf[64] = "helloworld";
    struct sockaddr_in serveraddr;
    __bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVERADDR, &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(SERVERPORT);

    socklen_t server_len = sizeof(serveraddr);
    int ret = 0;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    printf("connnect...\n");
    ret = connect(sockfd, (struct sockaddr *)&serveraddr, server_len);
    if (ret == -1)
    {
        perror("connect");
        exit(0);
    }
    printf("connect success\n");
    int i = 0;
    int count = 0;
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

    return 0;
}