#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char **argv)
{
    if(argc < 2)
    {
        printf("usage: %s [filename] \n",argv[0]);
    }

    int fd = open(argv[1],O_WRONLY | O_CREAT,0777);
    if(-1 == fd)
    {
        perror("open");
    }
    else
    {
        puts("open success");
    }   
    

    off_t lsek = lseek(fd,1024*1024-1,SEEK_SET);
    // int ret = write(fd,"\0",1024*1024);
    int ret = write(fd,"\0",1);
    if(-1 == ret)
    {
        perror("write");
    }
    else
    {
        printf("ret=%d,lseek = %ld\n",ret,lsek);
    }
    
    
    return 0;
}

