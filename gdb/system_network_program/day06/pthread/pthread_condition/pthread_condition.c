#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

static int condition = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void* mythread(void* arg)
{
    static int value = 0;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("pthread id %lx get lock,arg = %ld\n",pthread_self(),(long)arg);
        while (condition <= 0)
        {
            printf("wait condition thid %lx\n",pthread_self());
            pthread_cond_wait(&cond,&mutex);
        }
        
        sleep(3);
        condition--;
        printf("pthread id %lx unlock,***** value = %d ***,condition = %d\n",pthread_self(),++value,condition);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    
    pthread_exit((void* )111);
}
int main()
{
    pthread_t thid_a,thid_b;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);

    pthread_create(&thid_a,NULL,mythread,(void *)0);
    pthread_create(&thid_b,NULL,mythread,(void *)1);

    while(1)
    {
        sleep(5);
        pthread_mutex_lock(&mutex);
        condition++;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
        // pthread_cond_broadcast(&cond);
    }
    
    pthread_join(thid_a,NULL);
    pthread_join(thid_b,NULL);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    return 0;
}