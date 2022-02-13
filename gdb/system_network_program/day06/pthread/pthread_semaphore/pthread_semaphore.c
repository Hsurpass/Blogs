#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>

sem_t sem_a;
sem_t sem_b;
sem_t sem_c;
//a --> b --> c
void *mythread_a(void *arg)
{
    while (1)
    {
        sem_wait(&sem_a);
        puts(__FUNCTION__);
        sleep(5);
        sem_post(&sem_b);
    }

    pthread_exit((void *)0);
}

void *mythread_b(void *arg)
{
    while (1)
    {
        sem_wait(&sem_b);
        puts(__FUNCTION__);
        sleep(5);
        sem_post(&sem_c);
    }

    pthread_exit((void *)0);
}

void *mythread_c(void *arg)
{
    while (1)
    {
        sem_wait(&sem_c);
        puts(__FUNCTION__);
        sleep(5);
        sem_post(&sem_a);
    }

    pthread_exit((void *)0);
}
int main()
{
    sem_init(&sem_a, 0, 1);
    sem_init(&sem_b, 0, 0);
    sem_init(&sem_c, 0, 0);
    pthread_t thid_a;
    pthread_t thid_b;
    pthread_t thid_c;

    pthread_create(&thid_a, NULL, mythread_a, (void *)111);
    pthread_create(&thid_b, NULL, mythread_b, (void *)112);
    pthread_create(&thid_c, NULL, mythread_c, (void *)113);

    pthread_join(thid_a, NULL);
    pthread_join(thid_b, NULL);
    pthread_join(thid_c, NULL);

    sem_destroy(&sem_a);
    sem_destroy(&sem_b);
    sem_destroy(&sem_c);

    return 0;
}