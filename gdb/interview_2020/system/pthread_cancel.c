#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void* mythread(void* arg)
{
    int i=0;
    while(1)
    {
        i++;
        pthread_testcancel();
        printf("mythread i:%d\n",i);
        if(i == 10)
        {
            break;
        }

    }
    // pthread_exit((void*)i);
    exit(3);
}

int main()
{
    pthread_t tid;int ret = -1;
    pthread_create(&tid,NULL,mythread,NULL);

    // pthread_detach(tid);
    sleep(3);
    // pthread_cancel(tid);

    for (int j = 0;j < 10;++j)
    {
        printf("main thread id:%lx,j:%d\n",pthread_self(),j);
        sleep(1);
    }
    void *result;
    ret = pthread_join(tid,&result);
    if(ret != 0)
    {
        printf("pthread join error code:%d,%s\n",ret,strerror(ret));
    }
    printf("pthread join result:%d\n",(int)result);

    return 0;
}