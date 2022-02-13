#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main02()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        /* code */
        printf("child process, pid = %d\n",getpid());
        int ret = execl("/bin/ls","ls","-l","-a",NULL);
        if (ret == -1)
        {
            perror("execv");
        }
        
        exit(1);
    }
    else if (pid > 0)
    {
        // sleep(1);   
        pid_t childpid = wait(NULL);
        printf("parent process, ppid = %d,childpid = %d\n",getpid(), childpid);
        exit(0);
    }
    printf("hello\n");
    return 0;
}

int main(int argc,char **argv,char **env)
{
    char *arg[10];
    arg[0]="ls";
    arg[1]="-l"; 
    arg[2]="-a";
    // arg[3]=NULL;

    // int ret = execv("/bin/ls",arg);
    // int ret = execvp("ls",arg);
    int ret = execve("/bin/ls",arg,env);

    if(-1 == ret)
    {
        perror("execl");
    }
    printf("hello\n");
    return 0;
}
