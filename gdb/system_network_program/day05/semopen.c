#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>


int main()
{
    int ret = 0;
    sem_t *sem = sem_open("/mysem",O_CREAT,0664,1);
    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        _exit(0);
    }
    printf("create sem success\n");

    sem_close(sem);
    sem_unlink("/mysem");
    printf("unlink sem success\n");
    return 0;
}