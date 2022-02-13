#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    __pid_t pid = fork();
    if (pid > 0)
    {
        printf("parent: pid = %d,pgid = %d\n",getpid(),getpgrp() );
        printf("parent: pid = %d,pgid = %d\n",getpid(),getpgid(0) );
        printf("parent: pid = %d,pgid = %d\n",getpid(),getpgid(getpid()) );
        sleep(2);
        setpgid(pid,0);
    }
    else if (pid == 0)
    {
        sleep(1);
        printf("child: pid = %d,pgid = %d\n",getpid(),getpgrp() );
        printf("child: pid = %d,pgid = %d\n",getpid(),getpgid(0) );
        printf("child: pid = %d,pgid = %d\n",getpid(),getpgid(getpid()) );
        sleep(2);
        // setpgid(0,0);
        printf("child: pid = %d,pgid = %d\n",getpid(),getpgrp() );
        printf("child: pid = %d,pgid = %d\n",getpid(),getpgid(0) );
        printf("child: pid = %d,pgid = %d\n",getpid(),getpgid(getpid()) );
    }
    else
    {
        perror("fork");
    }
    
    return 0;
}