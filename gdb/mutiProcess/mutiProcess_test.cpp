#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void testMutiProcess()
{
    printf("current pid = %d\n", getpid());

    pid_t pid = fork();
    if(pid > 0)
    {
        printf("parent process. child pid = %d, parent pid = %d, ppid= %d\n", pid, getpid(), getppid());
        for (int i = 0; i < 10; i++)
        {
            printf("i=%d\n", i);
            sleep(1);
        }
    }
    else
    {
        printf("child process. child pid = %d, child pid = %d, ppid= %d\n", pid, getpid(), getppid());
        for (int j = 0; j < 10; j++)
        {
            printf("j=%d\n", j);
            sleep(1);
        }
        
    }

    waitpid();
}

int main()
{
    printf("current pid = %d\n", getpid());
    testMutiProcess();

    return 0;
}