#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

void sighandle(int sig)
{
    printf("sighandle:%d\n",sig);
    alarm(5);
}
int main()
{
    signal(SIGALRM,sighandle);
    alarm(5);
    while (1)
    {   
        printf("hello world\n");
        sleep(1);
    }
    
    return 0;
}