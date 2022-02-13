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
    char buf[32];
    char *ptr;
    memset(buf,0x31,sizeof(buf));
    if(ptr = strtok(argv[1],"/"))
    {
        strcpy(buf,ptr);
    }

    // while (ptr != NULL)
    // {
    //     int ret = mkdir(buf,0777);
    //     if(-1 == ret)
    //     {
    //         if (errno != EEXIST)
    //         {
    //             perror("mkdir");
    //             return -1;
    //         }
    //     }
    //     if(ptr = strtok(NULL,"/"))
    //     {
    //         strcat(buf,"/");
    //         strcat(buf,ptr);
    //     }
    // }

    while (ptr != NULL)
    {
        if(access(buf,F_OK) != F_OK)
        {
            int ret = mkdir(buf,0777);
            if(-1 == ret)
            {
                    perror("mkdir");
                    return -1;
            }
        }
        if(ptr = strtok(NULL,"/"))
        {
            strcat(buf,"/");
            strcat(buf,ptr);
        }
    }
    
    return 0;
}




