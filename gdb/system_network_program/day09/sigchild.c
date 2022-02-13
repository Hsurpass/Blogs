#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sigchild(int sig)
{
    pid_t childpid;
    while ((childpid = waitpid(-1,NULL, WNOHANG)) != -1)
    {
        printf("waitpid: childpid = %d,sig = %d\n",childpid,sig);
    }
    
}
int main()
{
    signal(SIGCHLD,sigchild);

    int i = 0;
    __pid_t pid;
    for(i = 0;i < 10;i++)
    {
        pid = fork();
        if (pid == 0)
        {   
            sleep(3);
            printf("child process id = %d\n",getpid());
            // break;
            exit(1);
        }
        else if(pid > 0)
        {
            
            printf("parent process id = %d\n",getpid());
            // exit(0);
        }
        else
        {
            perror("fork");
        }
        
    }

    while (1)
    {
        sleep(1);
    }
    
    return 0;
}