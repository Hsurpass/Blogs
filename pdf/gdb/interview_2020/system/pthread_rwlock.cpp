#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_rwlock_t rwmutex;
static int count = 0;

void *readthread(void *arg)
{
    while (1)
    {
        pthread_rwlock_rdlock(&rwmutex);
        printf("readthread,tid:%ld, count:%d\n", pthread_self(),count);
        sleep(2);
        pthread_rwlock_unlock(&rwmutex);
        sleep(1);
    }
}

void *writethread(void *arg)
{
    while (1)
    {
        pthread_rwlock_wrlock(&rwmutex);
        ++count;
        printf("writethread,tid:%ld, count:%d\n", pthread_self(),count);
        sleep(1);
        pthread_rwlock_unlock(&rwmutex);
        sleep(1);
    }
}

int main()
{
    pthread_t tid[4];
    pthread_rwlock_init(&rwmutex, NULL);
    int ret;

    for (int i = 0; i < 3; ++i)
    {
        ret = pthread_create(&tid[i], NULL, readthread, NULL);
        if (ret != 0)
        {
            printf("pthread_create fail,ret:%d,i:%d\n", ret, i);
            exit(0);
        }
    }

    ret = pthread_create(&tid[3], NULL, writethread, NULL);
    if (ret != 0)
    {
        printf("pthread_create fail,ret:%d\n", ret);
        exit(0);
    }

    for (size_t i = 0; i < 4; i++)
    {
        ret = pthread_join(tid[i], NULL);
        if (ret != 0)
        {
            printf("pthread_join fail,ret:%d,message:%s\n", ret, strerror(ret));
        }
    }

    pthread_rwlock_destroy(&rwmutex);

    return 0;
}