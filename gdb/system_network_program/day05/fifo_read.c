#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const char*filename = "myfifo";
int main()
{
    int ret = 0;
    ret = mkfifo(filename,0640);
    if (ret == -1)
    {
        if (errno != EEXIST)
        {
            perror("mkfifo");        
            exit(0);
        }
    }
    printf("mkfifo success\n");
    int fd = open(filename,O_RDONLY);
    if (-1 == fd)
    {
        perror("read open");
        exit(0);
    }
    printf("open success\n");

    char buf[32];int i = 0;
    while (1)
    {
        ret = read(fd,buf,sizeof(buf)-1);
        if (ret == -1)
        {
            perror("read");
            exit(0);
        }
        buf[ret] = '\0';
        printf("read: buf = %s,ret = %d\n",buf,ret);
    }
        
    return 0;
}

