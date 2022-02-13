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
    int fd = open("log",O_WRONLY);
    if(-1 == fd)
    {
        perror("open");
    }

    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);
    close(fd);  
    //close(STDOUT_FILENO);
    close(STDERR_FILENO);

    puts("hello");
    printf("world\n");
    perror("dup2");

    // close(fd);
    return 0;
}