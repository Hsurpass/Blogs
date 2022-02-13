#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>   
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv)
{
    // if (argc < 2)
    // {
    //     /* code */
    //     printf("usage: %s [filename]\n",argv[0]);
    // }
    char buf[64];
    memset(buf,0x31,sizeof(buf));
    if(getcwd(buf,sizeof(buf)) != NULL)
    {
        printf("current working dirctory=%s\n",buf);
    }
    chdir("/home/hchy");    
    if(getcwd(buf,sizeof(buf)) != NULL)
    {
        printf("current working dirctory=%s\n",buf);
    }
    return 0;
}