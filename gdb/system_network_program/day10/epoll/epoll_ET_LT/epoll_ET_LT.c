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

#define MAXLINE 10

int main()
{
    char buf[1024] = {0};
    char ch = 'a';
    int fd[2];
    int ret = 0;
    int nready = 0;
    ret = pipe(fd);
    if (ret == -1)
    {
        perror("pipe");
        exit(errno);
    }

    int i = 0;
    pid_t pid = fork();
    if (pid == 0) //child process write
    {
        close(fd[0]);
        while (1)
        {
            for (i = 0; i < MAXLINE / 2; i++)
            {
                buf[i] = ch;
            }
            buf[i - 1] = '\n'; //aaaa\n
            ch++;
            for (; i < MAXLINE; i++)
            {
                buf[i] = ch;
            }
            buf[i - 1] = '\n';
            ch++;
            // printf("buf:%s", buf);
            write(fd[1], buf, strlen(buf));
            sleep(5);
        }
        close(fd[1]);
    }
    else if (pid > 0) //  parent process read
    {
        close(fd[1]);
        struct epoll_event event, reevent[10];

        int epfd = epoll_create(10);
        if (ret == -1)
        {
            perror("epoll_create");
            exit(0);
        }
        event.data.fd = fd[0];
        // event.events = EPOLLIN;
        event.events = EPOLLIN | EPOLLET;
        ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd[0], &event);
        if (ret == -1)
        {
            perror("epoll_ctl");
        }

        while (1)
        {
            nready = epoll_wait(epfd, reevent, 10, -1);
            printf("nready:%d\n", nready);
            while/*if*/ (reevent[0].data.fd == fd[0])
            {
                ret = read(fd[0], buf, MAXLINE / 2);
                if (ret == 0)
                {
                    printf("ret == 0\n");
                    break;
                }

                write(STDOUT_FILENO, buf, ret);
            }
        }
        close(fd[0]);
        close(epfd);
    }
    else
    {
        perror("fork");
        exit(errno);
    }

    return 0;
}