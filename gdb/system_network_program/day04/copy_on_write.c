#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int a = 2;
    pid_t pid = fork(   );
    if (pid == 0)
    {
        a = 4;
        printf("child process, a = %d,pid = %d\n",a,getpid() );
        exit(0);
    }
    else if (pid > 0)
    {
        sleep(3);
        printf("parent process, a = %d,pid = %d\n",a,getpid() );
        exit(1);
    }
    else
    {
        perror("fork");
    }

    
    
    return 0;
}