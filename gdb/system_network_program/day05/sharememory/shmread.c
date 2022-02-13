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
    int fd = shm_open(shm_name,O_CREAT | O_RDWR ,0664);
    if (-1 == fd)
    {
        perror("shm_open");
        exit(0);
    }
    printf("shm create success\n");
    int ret = 0;
    long pageszie = sysconf(_SC_PAGE_SIZE);
    // printf("pagesize = %ld\n",pageszie);
    ret = ftruncate(fd,pageszie * 2);
    if (-1 == ret)
    {
        perror("ftruncate");
        exit(0);
    }
    printf("ftruncate success\n");
    void *pread = mmap(0,pageszie * 2,PROT_READ,MAP_SHARED,fd,0);
    if (pwrite == MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }
    printf("strlen(pread) = %ld\n",strlen(pread));
    int count = 0;
    while (count++ < 10)
    {
        printf("read share memory: %s\n",(char *)pread);
        sleep(1);   
    }

    munmap(pread,pageszie * 2);
    shm_unlink(shm_name);
    // char* ptmp = (char *)pread;
    // while (1)
    // {
    //     printf("read share memory: %s\n",(char *)ptmp);
    //     ptmp += (strlen(ptmp)+1);
    //     sleep(1);   
    // }
    

    
    return 0;
}