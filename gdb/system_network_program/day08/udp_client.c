#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <signal.h>
#define SERVERPORT 8000
#define SERVERADDR "192.168.226.129"

int main()
{
    //printf("%d,%d\n",INET_ADDRSTRLEN,INET6_ADDRSTRLEN);16,46
    struct sockaddr_in serveraddr;
    __bzero(&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    inet_pton(AF_INET, SERVERADDR, &serveraddr.sin_addr.s_addr);

    socklen_t serverlen = sizeof(serveraddr);
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    int ret = 0;
    int i = 0;
    char buf[32];
    memset(buf, 0x31, sizeof(buf));

    printf("sendto...\n");
    while (1)
    {
        sprintf(buf, "DATA%d", ++i);
        ret = sendto(client_fd, buf, strlen(buf), 0, (struct sockaddr *)&serveraddr, serverlen);
        if (ret == -1)
        {
            perror("sendto");
            exit(errno);
        }
        else
        {
            printf("client sendto: buf = %s,ret = %d\n", buf, ret);
        }
        sleep(1);
    }

    close(client_fd);
    return 0;
}