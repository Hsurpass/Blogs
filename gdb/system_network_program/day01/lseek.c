#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char **argv)
{
    if(argc < 2)
    {
        printf("usage: %s [filename] [string]\n",argv[0]);
    }

    int fd = open(argv[1],O_RDONLY,0764);
    if(-1 == fd)
    {
        perror("open");
    }
    else
    {
        puts("open success");
    }
    char buf[32];
    int ret = read(fd,buf,10);

    //off_t lsek = lseek(fd,-5,SEEK_SET);
    off_t lsek = lseek(fd,+5,SEEK_END);
    // off_t lsek = lseek(fd,0,SEEK_CUR);
    if(-1 == ret)
    {
        perror("read");
    }
    else
    {
        printf("buf=%s,ret=%d,lseek = %ld\n",buf,ret,lsek);
    }
    
    
    return 0;
}

