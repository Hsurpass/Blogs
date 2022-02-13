#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* shm_name = "/myshm";
int main()
{
    int fd = shm_open(shm_name,O_CREAT | O_RDWR,0664);
    if (-1 == fd)
    {
        perror("shm_open");
        exit(0);
    }
    printf("shm create success\n");
    int ret = 0;
    long pageszie = sysconf(_SC_PAGE_SIZE);
    printf("pagesize = %ld\n",pageszie);
    ret = ftruncate(fd,pageszie * 2);
    if (-1 == ret)
    {
        perror("ftruncate");
        exit(0);
    }
    printf("ftruncate success\n");

    
    return 0;
}