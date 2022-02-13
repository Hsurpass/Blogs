#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
static int value = 0;

pthread_mutex_t mutex;
void* mythread(void *arg)
{
    int i = 0,tmp;
    pthread_mutex_lock(&mutex);
    for (size_t i = 0; i < 500000; i++)
    {
        // pthread_mutex_lock(&mutex);
        tmp = value;
        tmp++;
        value = tmp;
        // pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_unlock(&mutex);

    printf("thread ID: %lx, value = %d\n",pthread_self(),value);
    return (void*)111;
}

int main()
{
    pthread_t thid0,thid1;
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&thid0,NULL, mythread,(void*)0);
    pthread_create(&thid1,NULL, mythread,(void*)1);

    pthread_join(thid0,NULL);
    pthread_join(thid1,NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}