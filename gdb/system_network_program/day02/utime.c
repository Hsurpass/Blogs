#include <utime.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>   
#include <time.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
    if (argc < 2)
    {
        /* code */
        printf("usage: %s [filename]\n",argv[0]);
    }
    time_t now;
    time(&now);

    struct utimbuf utbuf;
    utbuf.actime = now;
    utbuf.modtime = now;
    
    // int ret = utime(argv[1],&utbuf);
    int ret = utime(argv[1],NULL);
    if (-1 == ret)
    {
        /* code */
        perror("ret");
    }
    
    return 0;
}