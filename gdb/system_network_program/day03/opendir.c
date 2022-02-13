#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc,char **argv)
{
    if(argc < 2)
    {
        printf("usage: %s [directory]\n",argv[0]);
    }
    int count = 0;long offset=0;
    DIR *dir = opendir(argv[1]);
    if(NULL == dir)
    {
        perror("opendir");
    }
    struct dirent *ptr;
    while(ptr = readdir(dir))
    {
        if(++count == 3)
        {
            offset = telldir(dir);
        }
        printf("name:%8s,inode:%8ld,reclen=%8d,off=%8ld,telldir=%ld,",
        ptr->d_name,ptr->d_ino,ptr->d_reclen,ptr->d_off,telldir(dir));
        switch (ptr->d_type)
        {
        case DT_DIR:
            printf("dir\n");
            break;
        case DT_REG:
            printf("reg\n");
        default:
            break;
        }
    
    }
    printf("--------------------------------------\n");
    seekdir(dir,offset);
    while(ptr = readdir(dir))
    {
        printf("name:%8s,inode:%8ld,reclen=%8d,off=%8ld,telldir=%ld,",
        ptr->d_name,ptr->d_ino,ptr->d_reclen,ptr->d_off,telldir(dir));
        switch (ptr->d_type)
        {
        case DT_DIR:
            printf("dir\n");
            break;
        case DT_REG:
            printf("reg\n");
        default:
            break;
        }
    }
    // rewinddir(dir);
    // printf("--------------------------------------\n");
    //  while(ptr = readdir(dir))
    // {
    //     printf("name:%8s,inode:%8ld,reclen=%8d,off=%8ld,telldir=%ld,",
    //     ptr->d_name,ptr->d_ino,ptr->d_reclen,ptr->d_off,telldir(dir));
    //     switch (ptr->d_type)
    //     {
    //     case DT_DIR:
    //         printf("dir\n");
    //         break;
    //     case DT_REG:
    //         printf("reg\n");
    //     default:
    //         break;
    //     }
    // }
    closedir(dir);
    return 0;
}