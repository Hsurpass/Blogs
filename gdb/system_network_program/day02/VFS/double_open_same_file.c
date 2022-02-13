#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>   
#include <time.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    int fd0 = open("./log",O_RDONLY);
    if(-1 ==fd0)
    {
        perror("open");
    }

    int fd1 = open("./log",O_RDONLY);
    if(-1 ==fd1)
    {
        perror("open");
    }

    off_t off_fd0 = lseek(fd0,0,SEEK_END);
    off_t off_fd1 = lseek(fd1,0,SEEK_CUR);
    printf("off_fd0 = %ld\n",off_fd0);
    printf("off_fd1 = %ld\n",off_fd1);

    return 0;
}