#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc,char **argv)
{
    struct stat state;
    int ret = stat(argv[1],&state);
    if (ret == -1)
    {
        /* code */
        perror("stat");
    }
    if(S_ISLNK(state.st_mode)) //判断是否为符号连接
    {
        puts("is link file");
    }
    if(S_ISREG((state.st_mode & __S_IFMT) == __S_IFREG) ) //是否为一般文件
    {
        puts("is regular file");
    }
    if(S_ISDIR(state.st_mode)) //是否为目录
    {
        puts("is directory");
    }
    if(S_ISBLK (state.st_mode)) //是否是块设备
    {
        puts("is block device");
    }
    if(S_ISCHR((state.st_mode & S_IFMT) == S_IFCHR) ) //是否为字符设备文件
    {
        puts("is char device");
    }
    if(S_ISSOCK (state.st_mode)) //是否为socket
    {
        puts("is socket file");
    }

    printf("st_size:%ld",state.st_size);
    printf("accesstime:%ld, %s\n",state.st_atime,ctime(&state.st_atime) );
    printf("modifytime:%ld, %s\n",state.st_mtime,ctime(&state.st_mtime) );
    printf("changetime:%ld, %s\n",state.st_ctime,ctime(&state.st_ctime) );

    printf("blksize:%ld\n",state.st_blksize);
    printf("blkcnt:%ld\n",state.st_blocks);

    return 0;
}



