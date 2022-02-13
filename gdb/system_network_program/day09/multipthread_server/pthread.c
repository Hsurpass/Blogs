#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int count = 0;
void *mythread(void *arg)
{
    sleep(11);
    printf("child thread fd = %d\n",(int)arg);
    printf("child thid= %lx, count = %d\n",pthread_self(),count);
    pthread_exit((void *)1);
}
int main()
{
    int fd = open("log",O_CREAT|O_RDWR,0664);
    pthread_t thid;
    // static int count = 0;
    pthread_create(&thid, NULL, mythread, (void *)fd);

    while (count < 10)
    {
        count++;
        printf("main thread count:%d\n", count);
        sleep(1);
    }
    printf("main thread fd = %d,thid = %lx\n",fd,pthread_self());
    pthread_join(thid, NULL);

    return 0;
}
