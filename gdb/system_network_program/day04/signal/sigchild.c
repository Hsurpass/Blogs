#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void child_process()
{
    printf("child process: pid = %d\n", getpid());
    sleep(50);
    exit(1);
}
void sig_handle(int sig)
{
    pid_t childpid;
    int status;
    childpid = wait(&status);
    printf("recycle child process: sig = %d,childpid = %d\n", sig, childpid);
    // childpid = waitpid(-1,&status,WNOHANG);
    // while((childpid = waitpid(-1,&status,WNOHANG)) > 0)
    // {
    // printf("recycle child process: sig = %d,childpid = %d\n", sig, childpid);
    // }
}
int main()
{
    signal(SIGCHLD, sig_handle);
    __pid_t pid = fork();
    if (pid == 0)
    {
        child_process();
    }
    else if (pid == -1)
    {
        perror("fork");
    }
/* 
    int i = 0;
    for (size_t i = 0; i < 10; i++)
    {
        __pid_t pid = fork();
        if (pid == 0)
        {
            child_process();
        }
        else if (pid == -1)
        {
            perror("fork");
        }
    }
*/
    while (1)
    {
        printf("parent process: pid = %d\n", getpid());
        sleep(2);
    }

    return 0;
}