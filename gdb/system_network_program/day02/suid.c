#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("log",O_WRONLY,0777);
    if (-1 == fd)
    {
        perror("open");
    }    
    
    

    return 0;
}