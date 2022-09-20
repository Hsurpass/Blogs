#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void* mythread(void* arg)
{
    for(int j = 0;j < 10;++j)
    {
        printf("my pthread id:%ld,j:%d\n",pthread_self(),j);
        sleep(1);
    }
    // pthread_join(pthread_self(),NULL);
}

int main()
{
    pthread_t tid;
    int ret = -1;

    ret = pthread_create(&tid,NULL,mythread,NULL);
    if(ret != 0)
    {
        printf("pthread_create fail,ret = %d\n",ret);
        exit(0);
    }   

    for(int i = 0;i < 5;++i)
    {
        printf("main pthread id:%ld,i:%d\n",pthread_self(),i);
        sleep(1);
    }
    
    // ret = pthread_join(pthread_self(),NULL);
    ret = pthread_join(tid,NULL);
    if(ret != 0)
    {
        printf("pthread_join fail,ret:%d\n",ret);
    }

    return 0;
}