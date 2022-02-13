#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();
    if (pid > 0)
    {
        while (1)
        {
            printf("parent id = %d\n",getpid());
            sleep(1);
        }
        
    }
    else if(pid == 0)
    {
        for (size_t i = 0; i < 5; i++)
        {
            printf("parent id = %d, child id = %d\n",getppid(),getpid());
        }

        exit(1);
    }
    else
    {
        perror("fork");
    }
    

    return 0;
}