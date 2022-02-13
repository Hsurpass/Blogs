#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* mythread(void *arg)
{
    int i = 0;int *pa = (int *)malloc(4);
    *pa = 111;
    while (++i <= 10)
    {
        printf("mythread: thid = %lx,arg = %ld\n",pthread_self(),(long)arg);
        sleep(1);
    }
    // return (void*)111;
    // return (void*)pa;
    pthread_exit((void*)111);
}

int main()
{
    pthread_t thid;
    int ret = 0;
    ret = pthread_create(&thid,NULL,&mythread,(void*)10);
    if (ret != 0)
    {
        printf("pthread_create error:%s\n",strerror(ret));
        exit(0);
    }
    pthread_detach(thid);

    // void *result;
    // ret = pthread_join(thid,&result);
    // if (ret != 0)
    // {
    //     printf("pthread_join error:%s\n",strerror(ret));       
    //     exit(1);
    // }
    // printf("result:%ld\n",(long)(result) );
    while (1)
    {
        printf("main pthread: thread id = %lx\n",pthread_self() );
        sleep(1);
    }
    


    return 0;
}