#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc,char **argv)
{
    if (argc < 2)
    {
        /* code */
        printf("usage: %s [mode] [filename]\n",argv[0]);
    }
    mode_t mode;
    sscanf(argv[1],"%o",&mode);
    int ret = chmod(argv[2],mode);
    if (ret == -1)
    {
        perror("chmod");
    }
    

    return 0;
}