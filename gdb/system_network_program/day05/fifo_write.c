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

void sighandle(int sig)
{
    printf("write broken\n");
}
const char*filename = "myfifo";
int main()
{
    signal(SIGPIPE,sighandle);
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
    int fd = open(filename,O_WRONLY);
    if (-1 == fd)
    {
        perror("write open");
        exit(0);
    }
    printf("open success\n");

    char buf[32];int i = 0;
    while (1)
    {
        sprintf(buf,"DATA%d",++i);
        ret = write(fd,buf,strlen(buf));
        if (ret == -1)
        {
            perror("write");
            exit(0);
        }
        printf("write: buf = %s,ret = %d\n",buf,ret);
        sleep(1);
    }
        
    return 0;
}

