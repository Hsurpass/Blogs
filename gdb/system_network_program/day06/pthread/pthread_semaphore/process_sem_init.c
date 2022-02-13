#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>

sem_t sem;

// void *mythread_b(void *arg)
// {
//     while (1)
//     {
//         sem_wait(&sem);
//         printf("%s get sem\n",__FUNCTION__);
//         sleep(5);
//         printf("%s post sem\n",__FUNCTION__);
//         sem_post(&sem);
//         sleep(1);
//     }

//     pthread_exit((void *)0);
// }


int main()
{
    sem_init(&sem,10,1);//????

    while (1)
    {
        sem_wait(&sem);
        printf("%s get sem\n",__FUNCTION__);
        sleep(5);
        printf("%s post sem\n",__FUNCTION__);
        sem_post(&sem);
        sleep(1);
    }

    sem_destroy(&sem);
   

    return 0;
}