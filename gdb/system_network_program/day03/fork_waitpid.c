#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main02()
{
    printf("pid = %d\n",getpid());
    printf("ppid = %d\n",getppid() );
    printf("uid = %d\n",getuid());
    printf("euid = %d\n",geteuid());
    printf("gid = %d\n",getgid());
    printf("egid = %d\n",getegid());
    return 0;
}

int main()
{
    pid_t pid = fork();
    printf("pid = %d\n",pid);
    if (pid > 0)
    {
        // for(int i = 0;i < 10;i++)
        // {
            // printf("parent process, parent pid = %d\n",getpid());
            // sleep(1);
        // }
        // sleep(10);
        int status;
        // pid_t childpid = wait(&status);  
        pid_t childpid;
        while(1)
        {
            childpid = waitpid(-1,&status,WNOHANG);
            if(childpid == 0)
            {
                printf("parent process, child pid = %d,status = %d\n",childpid,status);
                sleep(1);
            }
            else
            {
                break;
            }
        } 
        
        if (WIFEXITED(status))
        {
            printf("parent process,child pid = %d,exit = %d\n",childpid,WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status))
        {
            printf("parent process,child pid = %d,signal = %d\n",childpid,WTERMSIG(status));
        }

        exit(0);
    }
    else if(pid == 0)
    {
        for (size_t i = 0; i < 5; i++)
        {
            printf("chind process, ppid = %d,childid = %d\n",getppid(),getpid());
            sleep(1);
        }

        exit(2);
    }
    else
    {
        perror("fork");
    }
    

    return 0;
}
