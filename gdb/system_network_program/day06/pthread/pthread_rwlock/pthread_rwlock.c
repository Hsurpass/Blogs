#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
int count = 0;
pthread_rwlock_t rwlock;
void *thread_write(void *arg)
{
    while (1)
    {
        pthread_rwlock_wrlock(&rwlock);
        printf("pthread id %lx getwrlock\n",pthread_self());
        count++;
        sleep(5);
        printf("pthread id %lx unwrlock,count:%d \n",pthread_self(),count);
        pthread_rwlock_unlock(&rwlock);
        sleep(3);
    }
    
}
void* thread_read(void* arg)
{
    while (1)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("pthread id %lx getrdlock\n",pthread_self());
        sleep(1);
        printf("pthread id %lx unrdlock,count:%d \n",pthread_self(),count);
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
    
}
int main()
{
    pthread_t thid[6];
    pthread_rwlock_init(&rwlock,NULL);

    for (size_t i = 0; i < 5; i++)
    {
        pthread_create(&thid[i],NULL,thread_read,(void *)0);
    }

    pthread_create(&thid[5],NULL,thread_write,(void *)1);

    for (size_t i = 0; i < 6; i++)
    {
        pthread_join(thid[i],NULL);
    }
    
    pthread_rwlock_destroy(&rwlock);
    return 0;
}