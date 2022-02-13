#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    __pid_t pid = fork();
    if (pid > 0)
    {
        printf("parent: pid = %d,pgid = %d,sid = %d\n",getpid(),getpgrp(), getsid(0) );
        // sleep(15);
        exit(0);
    }
    else if (pid == 0)
    {
        sleep(1);
        printf("child: pid = %d,pgid = %d,sid = %d\n",getpid(),getpgrp(),getsid(0) );
        setsid();
        sleep(5);
        printf("child: pid = %d,pgid = %d,sid = %d\n",getpid(),getpgrp(),getsid(0) );
        while (1)
        {
            sleep(1);
        }
        
    }
    else
    {
        perror("fork");
    }
    
    return 0;
}