#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc,char **argv)
{
    char buf[32];
    int ret = 0;

    int flag = fcntl(STDIN_FILENO,F_GETFL);
    printf("before flag:%x\n",flag);
    flag |= O_NONBLOCK;
    printf("last flag:%x\n",flag);
    ret = fcntl(STDIN_FILENO,F_SETFL,flag);
    if(ret == -1)
    {
        perror("fcntl");
        return -1;
    }
  AGAIN:  
    ret = read(STDIN_FILENO,buf,sizeof(buf));
    if(ret == -1)
    {
        perror("read");
        if(errno == EAGAIN)
        {
            sleep(1);
            goto AGAIN;
        }
    }
    else
    {
        buf[ret] = '\0';
        printf("read success,buf=%s, ret = %d\n",buf,ret);
    }
    

    return 0;
}