#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void* mythread(void *arg)
{

}

int main()
{
    pthread_t tid;
    pthread_attr_t attr;
    int ret = -1;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    int count = 0;

    while (1)
    {
        ret = pthread_create(&tid,&attr,mythread,NULL);
        if(ret != 0)
        {
            printf("pthread_create fail,ret:%d,message:%s\n",ret,strerror(ret));
            exit(1);
        }    
        else
        {
            ++count;
            printf("thread id:%ld,count:%d\n",tid,count);
        }
        
    }
    
    pthread_attr_destroy(&attr);

    return 0;
}