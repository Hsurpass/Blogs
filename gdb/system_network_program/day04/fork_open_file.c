#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // int fd = open("log",O_RDONLY);
    char buf[32];
    memset(buf,0x31,sizeof(buf));

    pid_t pid = fork();
    int fd = open("log",O_RDONLY);

    if (pid == 0)
    {
        int ret = read(fd,buf,10);    
        if (-1 == ret)
        {
            perror("read");
        }
        buf[ret] = '\0';
        printf("child process, buf = %s,pid = %d\n",buf,getpid());
        exit(0);
    }
    else if (pid > 0)
    {
        sleep(3);
        int ret = read(fd,buf,10);    
        if (-1 == ret)
        {
            perror("read");
        }
        buf[ret] = '\0';
        printf("parent process, buf = %s,pid = %d\n",buf,getpid());
        exit(1);
    }
    else
    {
        perror("fork");
    }

    
    
    return 0;
}