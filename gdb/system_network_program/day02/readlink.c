#include <utime.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>   
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv)
{
    if (argc < 2)
    {
        /* code */
        printf("usage: %s [filename]\n",argv[0]);
    }

    char buf[128];
    memset(buf,0x31,sizeof(buf));
    int ret = readlink(argv[1],buf,sizeof(buf) );
    if(ret != -1)
    {
        buf[ret] = '\0';
        printf("buf=%s,ret=%d\n",buf,ret);
    }

    return 0;
}