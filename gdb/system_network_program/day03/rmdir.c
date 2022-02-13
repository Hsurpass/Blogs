#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main(int argc,char **argv)
{
    if(argc < 2)
    {
        printf("usage: %s [directory]\n",argv[0]);
    }
    int ret = rmdir(argv[1]);
    if(ret == -1)
    {
        perror("rmdir");
    }

    return 0;
}