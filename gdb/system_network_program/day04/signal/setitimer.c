#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

void sig_handle(int sig)
{
    static int i = 0;
    printf("alarm[%d],sig=%d\n",i++,sig);

}

int main()
{
    signal(SIGALRM,sig_handle);
    struct itimerval timer;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;
    
    int ret = setitimer(ITIMER_REAL,&timer,NULL);
    if (ret == -1)
    {
        perror("setitimer");
    }
    while (1)
    {
        printf("helloworld\n");
        sleep(1);
    }
    
    // pause();
    return 0;
}