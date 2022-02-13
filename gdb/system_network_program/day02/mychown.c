#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{   
    if(argc < 4)
    {
        printf("usage:%s [uid]:[gid] [filename]\n",argv[0]);
        exit(-1);
    }
    int uid = -1,gid = -1;
    sscanf(argv[1],"%d",&uid);
    sscanf(argv[2],"%d",&gid);

    int ret = chown(argv[3],uid,gid);
    if(-1 == ret)
    {
        perror("chown");
    }


    return 0;
}
