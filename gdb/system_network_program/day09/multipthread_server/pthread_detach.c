#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *my_thread(void *arg)
{
    int i = 3;
    while (i--)
    {
        printf("thread count %d\n", i);
        sleep(1);
    }
    return(void *) 1;
}
int main(void)
{
    pthread_t tid;
    void *tret;
    int err;
    pthread_create(&tid, NULL, my_thread, NULL);
    /*第一次运行时注释掉下面这行，第二次再打开，分析两次结果*/
    // pthread_detach(tid);
    err = pthread_join(tid, &tret);
    if (err != 0)
        printf("thread %s\n", strerror(err));
    else
        printf("thread exit code %ld\n", (long)tret);
    sleep(1);
    return 0;
}

