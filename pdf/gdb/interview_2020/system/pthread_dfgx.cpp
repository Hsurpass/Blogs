#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int gvalue;
void* add(void *arg)
{
    int count = 5000000;
    int *val = reinterpret_cast<int*>(arg);
    while (count--)
    {
        ++gvalue;
        ++(*val);
        // sleep(1);
        // printf("add val:%d,gvalue:%d\n",*val,gvalue);
    }
    
}
void* sub(void* arg)
{
    int count = 5000000;
    int *val = reinterpret_cast<int*>(arg);
    while (count--)
    {
        gvalue--;
        --(*val);
        // sleep(1);
        // printf("sub val:%d,gvalue:%d\n",*val,gvalue);
    }
    
}
int main()
{
    pthread_t tid1,tid2;
    // pthread_attr_t attr;
    int ret = -1;
    int x = 0;
    // pthread_attr_init(&attr);
    // pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

    ret = pthread_create(&tid1,NULL,add,&x);
    if(ret != 0)
    {
        printf("pthread_create tid1 fail,ret:%d\n",ret);
        exit(0);
    }
    ret = pthread_create(&tid2,NULL,sub,&x);
    // ret = pthread_create(&tid2,&attr,sub,&x);
    if(ret != 0)
    {
        printf("pthread_create tid2 fail,ret:%d\n",ret);
        exit(0);
    }
    // pthread_attr_destroy(&attr);
    // pthread_detach(tid2);


    printf("begin x:%d,gavalue:%d\n",x,gvalue);
    ret = pthread_join(tid1,NULL);
    if(ret != 0)
    {
        printf("pthread_join fail, ret:%d\n",ret);
    }
    ret = pthread_join(tid2,NULL);
    if(ret != 0)
    {
        printf("pthread_join fail, ret:%d\n",ret);
    }
    printf("end x:%d,gvalue:%d\n",x,gvalue);


    return 0;
}