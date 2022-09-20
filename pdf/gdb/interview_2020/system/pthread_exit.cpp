#include <iostream>

#include <pthread.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;
void func()
{
    for(int i = 0;i < 10;++i)
    {
        sleep(1);
        // cout << "func() id:" << pthread_self() << endl;
        printf("func() id:%ld,i:%d\n", pthread_self(),i);
        // if(i == 3)
        // {
        //     pthread_exit((void*)3);
        // }

    }
    pthread_exit((void*)5);
}
void* mythread(void *arg)
{
    // cout << "mythread() id:" << pthread_self() << endl;
    printf("mythread() id:%ld\n",pthread_self());

    func();

}
int main()
{
    pthread_t tid;
    int ret = -1;
    pthread_create(&tid,NULL,mythread,NULL);

    for(int i = 0;i < 10;++i)
    {
        // cout << "main thread() id:" << pthread_self() << endl;
        printf("main thread() id:%ld,i:%d\n",pthread_self(),i);
        // printf("gettid():%d\n",gettid());
        // cout << gettid() << endl;
        if(i == 5)
        {
            // pthread_exit(NULL);
            return 0;
        }

        sleep(1);
    }

    void* result;
    ret = pthread_join(tid,&result);
    if(ret != 0)
    {
        printf("pthread join fail\n");
    }
    printf("pthread join result:%ld\n",(long)result);
    // printf("pthread join result:%d\n",static_cast<int>(result));
    // printf("pthread join result:%ld\n",reinterpret_cast<long>(result));



    return 0;
}