#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;
void* mythread(void* arg)
{
    for(int i = 0;i < 5;++i)
    {
        printf("mythread tid:%ld,i:%d\n",pthread_self(),i);
        sleep(1);
    }
    pthread_exit((void*)10);
    // printf("mythread exit\n");
}

int main()
{
    pthread_t tid;
    int ret = -1;
    ret = pthread_create(&tid,NULL,mythread,NULL);
    if(ret != 0)
    {
        printf("pthread_create fail\n");
        exit(0);
    }
    pthread_detach(tid);

    for(int j = 0;j < 10;++j)
    {
        printf("main thread id:%ld,j:%d\n",pthread_self(),j);
        if(j == 3)
        {
            return 0;
        }
        sleep(1);
    }

    void *result;
    ret = pthread_join(tid,&result);
    if(ret != 0)
    {
        printf("pthread_join fail,ret=%d\n",ret);
    }

    return 0;
}










