#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>

sem_t sem_repository;
sem_t sem_product;

static int value[5];
void* thread_consumer(void *arg)
{
    static int index = 0;
    while (1)
    {
        // sleep(5);
        sem_wait(&sem_product);
        printf("thread_consumer: consume value[index] = %d\n",value[index]);
        index = (index + 1) % (sizeof(value)/sizeof(value[0]));
        sem_post(&sem_repository);
        sleep(1);
    }
    pthread_exit((void*)1);
}
void* thread_producer(void* arg)
{
    static int index = 0;
    static int i = 0;
    while (1)
    {
        sem_wait(&sem_repository);
        value[index] = i++;
        printf("thread_producer: produce value[index] = %d\n",value[index]);
        index = (index + 1) % (sizeof(value)/sizeof(value[0]));
        sem_post(&sem_product);
        sleep(2);
    }
    pthread_exit((void*)0);
}
int main()
{
    sem_init(&sem_repository,0,5);
    sem_init(&sem_product,0,0);

    pthread_t pth_consumer;
    pthread_t pth_producer;
    pthread_create(&pth_consumer,NULL,thread_consumer,(void*)111);
    pthread_create(&pth_producer,NULL,thread_producer,(void*)112);

    pthread_join(pth_consumer,NULL);
    pthread_join(pth_producer,NULL);

    sem_destroy(&sem_repository);
    sem_destroy(&sem_product);
    return 0;
}