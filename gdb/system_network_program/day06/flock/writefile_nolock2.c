#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: %s [filename]\n", argv[0]);
        exit(0);
    }

    int fd = open(argv[1], O_WRONLY);
    if (-1 == fd)
    {
        perror("open");
        exit(-1);
    }
    char buf[32] = "helloworld";
    int ret = 0;
    // memset(buf, 0x31, sizeof(buf));
    // flock(fd, LOCK_EX);
    // printf("get file lock __EX\n");
    // ret = read(fd, buf, sizeof(buf));
    sleep(2);
    ret = write(fd,buf,strlen(buf));
    if (ret == -1)
    {
        perror("write");
    }
    printf("buf = %s\n", buf);
    // printf("flock unlock __EX\n");
    // flock(fd, LOCK_UN);

    close(fd);
    return 0;
}